import math
import sys
from sys import argv
from ROOT import TH1, TH1F, TH2F, TFile, TCanvas, TPad, TLegend, TLatex, TColor, TMath, TVectorD, TGraph, TUnfold, Double, TSpline, TSpline3, TUnfoldDensity, TUnfoldSys, TAttLine, TStyle
from ROOT import *
from array import array
import string


class Background :
    def __init__(self, name, hist):
        self.name = name
        self.hist = hist
        if(name == 'wjets'): 
	        self.norm = 1.
       	        self.err  = 0.25
        if(name == 'dy'):
                self.norm = 1.
                self.err  = 0.30
        if(name == 'qcd'):
                self.norm = 1.
                self.err  = 0.30
        if(name == 'st'):
                self.norm = 1.
                self.err  = 0.5

class Systematic :
    def __init__(self, name, response):
        self.name = name
        self.response = response


gStyle.SetOptStat(0)
gROOT.SetBatch(True)
unfolding_input_data = TFile("dd_inputs.root")
measurement = unfolding_input_data.Get("Data")
expectation = unfolding_input_data.Get("Var_gen")
ttbar = unfolding_input_data.Get("TTbar")
wjets = unfolding_input_data.Get("WJets")
dy = unfolding_input_data.Get("DY")
qcd = unfolding_input_data.Get("QCD")
st = unfolding_input_data.Get("ST")
response = unfolding_input_data.Get("Migration_Matrix")


#syst
backgrounds = {}
backgrounds["wjets"] = Background("wjets",wjets)
backgrounds["dy"] = Background("dy",dy)
backgrounds["qcd"] = Background("qcd",qcd)
backgrounds["st"] = Background("st",st)

 
systematics2 = {}
#for name in ["pu","cferr1","cferr2","hf","hfstats1","hfstats2","jes","lf","lfstats1","lfstats2"]:
for name in ["pu","MuonID","Trigger"]:
    systematics2[name+"_up"] = Systematic(name,unfolding_input_data.Get("ttbar_"+name+"_up"))
    systematics2[name+"_down"] = Systematic(name,unfolding_input_data.Get("ttbar_"+name+"_down"))

unfold = TUnfoldDensity(response,TUnfold.kHistMapOutputVert, TUnfold.kRegModeCurvature, TUnfold.kEConstraintArea, TUnfoldDensity.kDensityModeBinWidth)
unfold.SetInput(measurement)


for name, background in backgrounds.iteritems():
    unfold.SubtractBackground(background.hist,background.name,background.norm,background.err)


# Do unfolding using ScanTau to determine regularization strength
cc = TCanvas("cc", "cc", 700, 700)
cc.cd()
bestTau = TGraph(1)
scanResult = TSpline3()
iBest = unfold.ScanTau(100,0.0001,0.1,scanResult,TUnfoldDensity.kEScanTauRhoAvgSys)
Tau = Double(0)
rho = Double(0)
scanResult.GetKnot(iBest,Tau,rho)
bestTau.SetPoint(1,Tau,rho)
bestTau.SetMarkerColor(2)
scanResult.Draw("P")
bestTau.Draw("*")
tl2 = TLatex()
tl2.SetNDC()
tl2.SetTextFont(42)
legend = "log(#tau) = %.3e" % Tau
tl2.DrawLatex(0.55,0.8,legend)
cc.Draw()
cc.Print(argv[1]+"_rho_Min.pdf")

tau = pow(10,Tau)
print(tau)

unfold.DoUnfold(tau)

result = unfold.GetOutput("result")
result.Sumw2()

mCovInput = unfold.GetEmatrixInput("mCovInput")

# Response matrix statistical uncertainty
mCovMatrix = unfold.GetEmatrixSysUncorr("mCovMatrix")

# Background uncertainties (statistical and normalization)
mCovBkg = mCovInput.Clone("mCovBkg")
mCovBkg.Reset()
for name, background in backgrounds.iteritems():
    mCovBkgStat = unfold.GetEmatrixSysBackgroundUncorr(background.name,"mCovBkgStat_"+background.name)
    mCovBkg.Add(mCovBkgStat)
    hUncBkgScale = unfold.GetDeltaSysBackgroundScale(background.name,"hUncBkgScale_"+background.name)
    for ibin in xrange(1,mCovBkg.GetNbinsX()+1):
        mCovBkg.SetBinContent(ibin,ibin,mCovBkg.GetBinContent(ibin,ibin)+pow(hUncBkgScale.GetBinContent(ibin),2))

# Total covariance matrix
mCovTot = unfold.GetEmatrixTotal("mCovTot")

template = result.Clone()
template.Reset()

inputUnc  = template.Clone("inputUnc")
matrixUnc = template.Clone("matrixUnc")
bkgUnc    = template.Clone("bkgUnc")
totUnc    = template.Clone("totUnc")
sysUnc    = template.Clone("sysUnc")

for ibin in xrange(1,result.GetNbinsX()+1):
    inputUnc.SetBinContent(ibin,math.sqrt(mCovInput.GetBinContent(ibin,ibin))/result.GetBinContent(ibin))
    matrixUnc.SetBinContent(ibin,math.sqrt(mCovMatrix.GetBinContent(ibin,ibin))/result.GetBinContent(ibin))
    bkgUnc.SetBinContent(ibin,math.sqrt(mCovBkg.GetBinContent(ibin,ibin))/result.GetBinContent(ibin))
    totUnc.SetBinContent(ibin,math.sqrt(mCovTot.GetBinContent(ibin,ibin))/result.GetBinContent(ibin))

fout = TFile('Syst_unfolded.root', 'recreate')

unfold2 = TUnfoldDensity(response,TUnfold.kHistMapOutputVert, TUnfold.kRegModeCurvature, TUnfold.kEConstraintArea, TUnfoldDensity.kDensityModeBinWidth)


add_up = [0]*totUnc.GetNbinsX()
add_down = [0]*totUnc.GetNbinsX()

for name in ["pu","Trigger", "MuonID"]:

    print(name)
    tempsys_up = unfolding_input_data.Get("ttbar_"+name+"_up")
    unfold2.SetInput(tempsys_up)
    unfold2.DoUnfold(tau)
    result2 = unfold2.GetOutput("result2")
    tempsys_down = unfolding_input_data.Get("ttbar_"+name+"_down")
    unfold2.SetInput(tempsys_down)
    unfold2.DoUnfold(tau)
    result3 = unfold2.GetOutput("result3")
    result2.SetName(name+"_Up")
    result3.SetName(name+"_Down")
    gDirectory.cd('Syst_unfolded.root:/')
    gDirectory.WriteObject(result2,name+"_Up")
    gDirectory.WriteObject(result3,name+"_Down")

    for y in range(1,expectation.GetNbinsX()+1):
        mean = expectation.GetBinContent(y)
        up = result2.GetBinContent(y)
        down = result3.GetBinContent(y)
        error_up = (mean-up)/(mean*100)
        error_down = (mean-down)/(mean*100)
        add_up[y-1] += add_up[y-1] + error_up*error_up
        add_down[y-1] += add_down[y-1] + error_down*error_down

    del result2
    del result3


c2 = TCanvas("c2", "", 800, 600)
c2.SetTopMargin(0.08)
c2.SetRightMargin(0.05)
c2.SetBottomMargin(0.14)
c2.SetLeftMargin(0.16)

totUnc.GetXaxis().SetTitle("Top quark p_{T} [GeV]")
totUnc.GetYaxis().SetTitle("Uncertainty [%]")
totUnc.GetYaxis().SetRangeUser(0.0,1.0)

c2.cd()

for z in range(1,totUnc.GetNbinsX()+1):
    tot = totUnc.GetBinContent(z)
    totUnc.SetBinContent(z,math.sqrt(tot*tot + add_up[z-1]))
    sysUnc.SetBinContent(z,math.sqrt(add_up[z-1]))

totUnc.SetFillColor(17)
totUnc.SetFillStyle(3344)
totUnc.SetLineColor(16)
totUnc.SetLineWidth(2)

inputUnc.SetLineColor(1)
inputUnc.SetLineWidth(2)
inputUnc.SetMarkerColor(1)
inputUnc.SetMarkerStyle(20)

matrixUnc.SetLineColor(2)
matrixUnc.SetLineWidth(2)
matrixUnc.SetMarkerColor(2)
matrixUnc.SetMarkerStyle(34)

bkgUnc.SetLineColor(3)
bkgUnc.SetLineWidth(2)
bkgUnc.SetMarkerColor(3)
bkgUnc.SetMarkerStyle(22)

sysUnc.SetLineColor(4)
sysUnc.SetLineWidth(2)
sysUnc.SetMarkerColor(4)
sysUnc.SetMarkerStyle(21)

leg2 = TLegend(0.2,0.39,0.45,0.88)
leg2.AddEntry(totUnc,   "Total uncertainty","f")
leg2.AddEntry(inputUnc, "Input stat. unc.","lp")
leg2.AddEntry(matrixUnc,"Matrix stat. unc.","lp")
leg2.AddEntry(bkgUnc,   "Background unc.","lp")
leg2.AddEntry(sysUnc,   "Systematic unc.","lp")

leg2.SetFillStyle(0);
leg2.SetBorderSize(0);
leg2.SetTextSize(0.04);
leg2.SetTextFont(42);

totUnc.Draw("hist")
inputUnc.Draw("ep,same")
matrixUnc.Draw("ep,same")
bkgUnc.Draw("ep,same")
sysUnc.Draw("ep,same")

leg2.Draw();

c2.Print(argv[1]+"_Unc_data.pdf")




# Mormilize tot cav matrx
c3 = TCanvas("c3", "", 800, 600)
c3.SetTopMargin(0.07)
c3.SetRightMargin(0.12)
c3.SetBottomMargin(0.15)
c3.SetLeftMargin(0.15)

# Normalize covariance matrix
diagonals = []
for ibin in xrange(1,mCovTot.GetNbinsX()+1):
    tmp = math.sqrt(mCovTot.GetBinContent(ibin,ibin)) if (math.sqrt(mCovTot.GetBinContent(ibin,ibin)) is not 0) else 1.0
    diagonals.append(tmp)
for ibinx in xrange(1,mCovTot.GetNbinsX()+1):
    for ibiny in xrange(1,mCovTot.GetNbinsY()+1):
        tmp = mCovTot.GetBinContent(ibinx,ibiny) / diagonals[ibinx-1] / diagonals[ibiny-1]
        mCovTot.SetBinContent(ibinx,ibiny,tmp)

mCovTot.GetZaxis().SetRangeUser(-1.0,1.0)
mCovTot.SetTitle(";unfolded top quark p_{T} [GeV];unfolded top quark p_{T} [GeV]")

mCovTot.Draw("colz")

c3.Print("Cov_matrx_data.pdf")

    
## ratio of unfolded data to generator-level

ratio = expectation.Clone()
ratio.SetName("ratio")
ratio.SetTitle(";DeltaY;Theory/Data")
ratio.Divide(result)
    
# Convert total, statistical uncertainty into error bands
for ibin in xrange(1,expectation.GetNbinsX()+1):
    totUnc.SetBinError(ibin,totUnc.GetBinContent(ibin))
    totUnc.SetBinContent(ibin,1.0)
    inputUnc.SetBinError(ibin,inputUnc.GetBinContent(ibin))
    inputUnc.SetBinContent(ibin,1.0)
        
totUnc.SetMarkerSize(0)
totUnc.SetLineColor(0)
totUnc.SetFillColor(860-9)
totUnc.SetFillStyle(1001)
    
inputUnc.SetMarkerSize(0)
inputUnc.SetLineColor(0)
inputUnc.SetFillColor(18)
inputUnc.SetFillStyle(1001)    
    
# Plot
c4 = TCanvas("c4", "", 700, 700)
pad1 =  TPad("pad1","pad1",0,0.3,1,1)
pad1.SetBottomMargin(0.05)
pad1.Draw()
pad1.cd()
    
result.SetMarkerStyle(21)
measurement.SetMarkerStyle(25)
expectation.SetLineColor(4)
expectation.GetYaxis().SetTitleSize(25)
expectation.GetXaxis().SetLabelSize(0)

result.SetTitle(";;Events")
result.GetYaxis().SetTitleOffset(1.2)
result.SetMinimum(0.0)
result.SetAxisRange(0,max(result.GetMaximum(),result.GetMaximum())*1.15,"Y")
result.Draw()
expectation.Draw('hist same')
measurement.Draw('same')
    
leg4 = TLegend(0.5, 0.5, 0.9, 0.75)
leg4.SetFillStyle(0)
leg4.SetTextFont(42)
leg4.SetTextSize(0.045)
leg4.SetBorderSize(0)
    
leg4.AddEntry( result, 'Unfolded data', 'p')
leg4.AddEntry( measurement, 'Measured data', 'p')
leg4.AddEntry( expectation, 'Generator prediction', 'l')
leg4.AddEntry( inputUnc, 'Stat. uncertainty','f');
leg4.AddEntry( totUnc, 'Stat. #oplus syst. uncertainties','f');
leg4.Draw()
    
c4.cd()
pad2 =  TPad("pad2","pad2",0,0.0,1,0.28)
pad2.SetTopMargin(0.05)
pad2.SetBottomMargin(0.4)
pad2.Draw()
pad2.cd()
pad2.SetGridy()
ratio.SetMaximum(1.35)
ratio.SetMinimum(0.65)
ratio.UseCurrentStyle()
ratio.GetYaxis().SetTitleSize(25)
ratio.GetYaxis().SetTitleOffset(2.0)
ratio.GetXaxis().SetTitleOffset(4.0)
ratio.GetXaxis().SetLabelSize(25)
ratio.GetYaxis().SetNdivisions(4,4,0,False)
totUnc.Draw("same,e2")

ratio.Draw("hist")
totUnc.Draw("same,e2")
inputUnc.Draw("same,e2")
ratio.Draw("same,hist")
c4.Update()
c4.Print(argv[1]+"_Result_data.pdf")




for i in range (0,9):
	print result.GetBinContent(i) 




'''
fout = TFile('Syst_unfolded.root', 'recreate')

unfold2 = TUnfoldDensity(response,TUnfold.kHistMapOutputVert, TUnfold.kRegModeCurvature, TUnfold.kEConstraintArea, TUnfoldDensity.kDensityModeBinWidth)


add_up = [0]*totUnc.GetNbinsX()
add_down = [0]*totUnc.GetNbinsX()

for name in ["pu","Trigger", "MuonID"]:

    print(name)
    tempsys_up = unfolding_input_data.Get("ttbar_"+name+"_up")
    unfold2.SetInput(tempsys_up)
    unfold2.DoUnfold(tau)
    result2 = unfold2.GetOutput("result2")
    tempsys_down = unfolding_input_data.Get("ttbar_"+name+"_down") 
    unfold2.SetInput(tempsys_down)
    unfold2.DoUnfold(tau)
    result3 = unfold2.GetOutput("result3")
    result2.SetName(name+"_Up")
    result3.SetName(name+"_Down")
    gDirectory.cd('Syst_unfolded.root:/')
    gDirectory.WriteObject(result2,name+"_Up")
    gDirectory.WriteObject(result3,name+"_Down")

    for y in range(1,expectation.GetNbinsX()+1):
        mean = expectation.GetBinContent(y)
        up = result2.GetBinContent(y)
        down = result3.GetBinContent(y)
        error_up = (mean-up)/mean
        error_down = (mean-down)/mean
        add_up[y-1] += add_up[y-1] + error_up*error_up
        add_down[y-1] += add_down[y-1] + error_down*error_down
        
    del result2
    del result3


c2 = TCanvas("c2", "", 800, 600)
c2.SetTopMargin(0.08)
c2.SetRightMargin(0.05)
c2.SetBottomMargin(0.14)
c2.SetLeftMargin(0.16)

totUnc.GetXaxis().SetTitle("Top quark p_{T} [GeV]")
totUnc.GetYaxis().SetTitle("Uncertainty [%]")
totUnc.GetYaxis().SetRangeUser(0.0,5.0)

c2.cd()

for z in range(1,totUnc.GetNbinsX()+1):
    tot = totUnc.GetBinContent(z)
    totUnc.SetBinContent(z,math.sqrt(tot*tot + add_up[z-1]))
    sysUnc.SetBinContent(z,math.sqrt(add_up[z-1]))    

totUnc.SetFillColor(17)
totUnc.SetFillStyle(3344)
totUnc.SetLineColor(16)
totUnc.SetLineWidth(2)

inputUnc.SetLineColor(1)
inputUnc.SetLineWidth(2)
inputUnc.SetMarkerColor(1)
inputUnc.SetMarkerStyle(20)

matrixUnc.SetLineColor(2)
matrixUnc.SetLineWidth(2)
matrixUnc.SetMarkerColor(2)
matrixUnc.SetMarkerStyle(34)

bkgUnc.SetLineColor(3)
bkgUnc.SetLineWidth(2)
bkgUnc.SetMarkerColor(3)
bkgUnc.SetMarkerStyle(22)

sysUnc.SetLineColor(4)
sysUnc.SetLineWidth(2)
sysUnc.SetMarkerColor(4)
sysUnc.SetMarkerStyle(21)

leg2 = TLegend(0.2,0.39,0.45,0.88)
leg2.AddEntry(totUnc,   "Total uncertainty","f")
leg2.AddEntry(inputUnc, "Input stat. unc.","lp")
leg2.AddEntry(matrixUnc,"Matrix stat. unc.","lp")
leg2.AddEntry(bkgUnc,   "Background unc.","lp")
leg2.AddEntry(sysUnc,   "Systematic unc.","lp")

leg2.SetFillStyle(0);
leg2.SetBorderSize(0);
leg2.SetTextSize(0.04);
leg2.SetTextFont(42);

totUnc.Draw("hist")
inputUnc.Draw("ep,same")
matrixUnc.Draw("ep,same")
bkgUnc.Draw("ep,same")
sysUnc.Draw("ep,same")

leg2.Draw();

c2.Print(argv[1]+"_Unc_data.pdf")

'''
