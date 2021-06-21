import math
import sys
import ROOT
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
       	        self.err  = 0.3
        if(name == 'dy'):
                self.norm = 1.
                self.err  = 0.3
        if(name == 'qcd'):
                self.norm = 1.
                self.err  = 0.3
        if(name == 'st'):
                self.norm = 1.
                self.err  = 0.3
        if(name == 'ttbar_others'):
                self.norm = 1.
                self.err  = 0.3
class Systematic :
    def __init__(self, name, response):
        self.name = name
        self.response = response


gStyle.SetOptStat(0)
gROOT.SetBatch(True)
unfolding_input_data = TFile("Input_undfolding_data.root")
measurement = unfolding_input_data.Get("Data")
expectation = unfolding_input_data.Get("Var_gen")
ttbar = unfolding_input_data.Get("TTbar")
ttbar_others = unfolding_input_data.Get("TTbar_others")
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
backgrounds["ttbar_others"] = Background("ttbar_others",ttbar_others)
 
systematics2 = {}
for name in ["pu","MuonID","Trigger","mistoptag","cferr1","cferr2","hf","lf","hfstats1","hfstats2","lfstats1","lfstats2","jes","pt_rew","toptag","muon_rec","pdf","q2","jer","jec"]:
    systematics2[name+"Up"] = Systematic(name,unfolding_input_data.Get("ttbar_semi_"+name+"Up"))
    systematics2[name+"Down"] = Systematic(name,unfolding_input_data.Get("ttbar_semi_"+name+"Down"))

unfold = TUnfoldDensity(response,TUnfold.kHistMapOutputVert, TUnfold.kRegModeCurvature, TUnfold.kEConstraintArea, TUnfoldDensity.kDensityModeBinWidth)
unfold.SetInput(measurement)


for name, background in backgrounds.iteritems():
    unfold.SubtractBackground(background.hist,background.name,background.norm,background.err)


# Do unfolding using ScanTau to determine regularization strength
cc = TCanvas("cc", "cc", 700, 700)
cc.Divide(1,1)
cc.cd(1)
bestTau = TGraph(1)
scanResult = TSpline3()
iBest = unfold.ScanTau(100,0.0001,0.1,scanResult,TUnfoldDensity.kEScanTauRhoAvgSys)
Tau = Double(0)
rho = Double(0)
scanResult.GetKnot(iBest,Tau,rho)
bestTau.SetPoint(1,Tau,rho)
bestTau.SetMarkerColor(2)
tl2 = TLatex()
tl2.SetNDC()
tl2.SetTextFont(42)
legend = ""
#tl2.DrawLatex(0.55,0.8,legend)
scanResult.SetTitle("")
scanResult.Draw("P")
bestTau.Draw("*")
latex = ROOT.TLatex()
latex.SetTextSize(0.042)
latex.SetTextAlign(11)
latex.DrawLatex(-3.9,1.02,"Work in progress")
latex2 = ROOT.TLatex()
latex2.SetTextSize(0.042)
latex2.SetTextAlign(11)
latex2.DrawLatex(-2.2,1.02,"58.8 fb^{-1} (13 TeV)")
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


addUp = [0]*totUnc.GetNbinsX()
addDown = [0]*totUnc.GetNbinsX()

for name in ["pileup","muHLT", "muID","misttag","miswtag","cferr1","cferr2","hf","lf","hfstats1","hfstats2","lfstats1","lfstats2","jes","toptag","muon_rec","jer","jec"]:

    print(name)
    tempsysUp = unfolding_input_data.Get("ttbar_semi_"+name+"Up")
    unfold2.SetInput(tempsysUp)
    unfold2.DoUnfold(tau)
    result2 = unfold2.GetOutput("result2")
    tempsysDown = unfolding_input_data.Get("ttbar_semi_"+name+"Down")
    unfold2.SetInput(tempsysDown)
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
        errorUp = (mean-up)/(mean)
        errorDown = (mean-down)/(mean)
        addUp[y-1] = addUp[y-1] + errorUp*errorUp
        addDown[y-1] = addDown[y-1] + errorDown*errorDown
    
     
    del result2
    del result3

print addUp
print addDown
c2 = TCanvas("c2", "", 800, 600)
c2.SetTopMargin(0.08)
c2.SetRightMargin(0.05)
c2.SetBottomMargin(0.14)
c2.SetLeftMargin(0.16)

totUnc.GetXaxis().SetTitle("\Delta #cbar y #cbar")
totUnc.GetYaxis().SetTitle("Uncertainty [%]")
totUnc.GetYaxis().SetRangeUser(0.0,1.0)

c2.cd()


print ("tot + addUp")
for z in range(1,totUnc.GetNbinsX()+1):
    tot = totUnc.GetBinContent(z)
    totUnc.SetBinContent(z,math.sqrt(tot*tot + addUp[z-1]))
    sysUnc.SetBinContent(z,math.sqrt(addUp[z-1]))

print("Syt. Error")
for z in range(1,totUnc.GetNbinsX()+1):
    print(sysUnc.GetBinContent(z))    
   
print("Tot. Error")
for z in range(1,totUnc.GetNbinsX()+1):
    print(totUnc.GetBinContent(z)) 

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

leg2 = TLegend(0.55,0.49,0.88,0.88)
leg2.AddEntry(totUnc,   "Total uncertainty","f")
leg2.AddEntry(inputUnc, "Input stat. unc.","lp")
leg2.AddEntry(matrixUnc,"Matrix stat. unc.","lp")
leg2.AddEntry(bkgUnc,   "Background unc.","lp")
leg2.AddEntry(sysUnc,   "Systematic unc.","lp")

leg2.SetFillStyle(0);
leg2.SetBorderSize(0);
leg2.SetTextSize(0.03);
leg2.SetTextFont(42);

totUnc.SetTitle("")

totUnc.Draw("hist")
inputUnc.Draw("ep,same")
matrixUnc.Draw("ep,same")
bkgUnc.Draw("ep,same")
sysUnc.Draw("ep,same")

leg2.Draw();

latex3 = ROOT.TLatex()
latex3.SetTextSize(0.042)
latex3.SetTextAlign(11)
latex3.DrawLatex(-1.9,1.02,"Work in progress")
latex4 = ROOT.TLatex()
latex4.SetTextSize(0.042)
latex4.SetTextAlign(11)
latex4.DrawLatex(0.8,1.02,"58.8 fb^{-1} (13 TeV)")

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


#for i in range (0,9):
#        print sysUnc.GetBinContent(i) 
   
## ratio of unfolded data to generator-level

ratio = expectation.Clone()
ratio.SetName("ratio")
#ratio.GetXaxis().SetTitleSize(0.085)
#ratio.GetXaxis().SetTitle("#Delta #cbar y #cbar")
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
pad1.SetBottomMargin(0.08)
pad1.Draw()
pad1.cd()


for i in range (1,5):
    result.SetBinContent(i,result.GetBinContent(9-i)) 
    expectation.SetBinContent(i,expectation.GetBinContent(9-i))
    
result.SetMarkerStyle(21)
measurement.SetMarkerStyle(25)
measurement.SetLineColor(kRed)
measurement.SetFillColor(kRed)
expectation.SetLineColor(kBlue)
#expectation.SetFillColor(kBlue)
expectation.GetYaxis().SetTitleSize(25)
expectation.GetXaxis().SetLabelSize(0)

result.SetTitle(";;Events")
result.GetYaxis().SetTitleOffset(1.2)
result.SetMinimum(0.0)
result.SetAxisRange(0,max(result.GetMaximum(),result.GetMaximum())*1.15,"Y")
result.GetXaxis().SetTitle("#Delta #cbar y #cbar")
result.Draw()
expectation.Draw('hist same')
result.Draw("same")
#measurement.Draw('same')
    
leg4 = TLegend(0.6, 0.65, 0.95, 0.90)
leg4.SetFillStyle(0)
leg4.SetTextFont(42)
leg4.SetTextSize(0.025)
leg4.SetBorderSize(0)
    
leg4.AddEntry( result, 'Unfolded data', 'p')
#leg4.AddEntry( measurement, 'Measured data', 'l')
leg4.AddEntry( expectation, 'Generator prediction', 'l')
leg4.AddEntry( inputUnc, 'Stat. uncertainty','f');
leg4.AddEntry( totUnc, 'Stat. #oplus syst. uncertainties','f');
leg4.Draw()

print("*********")
print (result.GetMaximum())
latex5 = ROOT.TLatex()
latex5.SetTextSize(0.042)
latex5.SetTextAlign(11)
latex5.DrawLatex(-1.9,result.GetMaximum()*1.01,"Work in progress")
latex6 = ROOT.TLatex()
latex6.SetTextSize(0.042)
latex6.SetTextAlign(11)
latex6.DrawLatex(0.8,result.GetMaximum()*1.01,"58.8 fb^{-1} (13 TeV)")
    
c4.cd()
pad2 =  TPad("pad2","pad2",0,0.0,1,0.28)
pad2.SetTopMargin(0.05)
pad2.SetBottomMargin(0.4)
pad2.Draw()
pad2.cd()
pad2.SetGridy()
ratio.SetMaximum(1.6)
ratio.SetMinimum(0.4)
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



print("Result:")
for i in range (1,9):
	print result.GetBinContent(i) 


'''
print("###############################")

array_gen = [-2,-1.5,-1,-0.5,0.,0.5,1,1.5,2]
array_rec = [-2,-1.5,-1.25,-1.0,-0.75,-0.5,-0.25,0,0.25,0.5,0.75,1.,1.25,1.5,2]

len_gen = len(array_gen) - 1
len_rec = len(array_rec) - 1

error_array = [[0]*len_gen]*1
final_array = [[0]*len_gen]*1

for i in range(0,1):

    print(i)
    tempdata = TH1F("tempdata","tempdata",len_rec,array('d',array_rec))
    gRandom.SetSeed(0);

    for j in range(1,len_rec+1):
        tempdata.SetBinContent(j,gRandom.Poisson(measurement.GetBinContent(j)))
        print(tempdata.GetBinContent(j))
    print(" n ") 
     
    unfold_stat = TUnfoldDensity(response,TUnfold.kHistMapOutputVert, TUnfold.kRegModeCurvature, TUnfold.kEConstraintArea, TUnfoldDensity.kDensityModeBinWidth)
   
    for name, background in backgrounds.iteritems():
         unfold_stat.SubtractBackground(background.hist,background.name,background.norm,background.err)

    unfold_stat.SetInput(tempdata)
    unfold_stat.DoUnfold(0.00);
    temp_result = unfold_stat.GetOutput("temp_result%s"%i)
 
    for k in range(0,len_gen): 
        final_array[i][k] = temp_result.GetBinContent(k+1) 


    # Total covariance matrix
    mCovInput_stat = unfold_stat.GetEmatrixInput("mCovInput")

    template_stat = temp_result.Clone()
    template_stat.Reset()

    inputUnc_stat = template_stat.Clone("totUnc")

    for ibin in xrange(1,result.GetNbinsX()+1):
        inputUnc_stat.SetBinContent(ibin,math.sqrt(mCovInput_stat.GetBinContent(ibin,ibin))/temp_result.GetBinContent(ibin)) 
    for k in range(0,len_gen):
        error_array[i][k] = inputUnc_stat.GetBinContent(k+1)

    del tempdata
    del temp_result
    del unfold_stat


file1 = open("MyFile.txt","a")
file1.write(str(final_array[0][0])+",")      
file1.write(str(final_array[0][1])+",")
file1.write(str(final_array[0][2])+",")
file1.write(str(final_array[0][3])+",")
file1.write(str(final_array[0][4])+",")
file1.write(str(final_array[0][5])+",")
file1.write(str(final_array[0][6])+",")
file1.write(str(final_array[0][7])+",")
file1.write("\n")

file2 = open("MyFile_error.txt","a")
file2.write(str(error_array[0][0])+",")
file2.write(str(error_array[0][1])+",")
file2.write(str(error_array[0][2])+",")
file2.write(str(error_array[0][3])+",")
file2.write(str(error_array[0][4])+",")
file2.write(str(error_array[0][5])+",")
file2.write(str(error_array[0][6])+",")
file2.write(str(error_array[0][7])+",")
file2.write("\n")




'''
