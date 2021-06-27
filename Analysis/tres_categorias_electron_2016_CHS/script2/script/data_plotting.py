from ROOT import *
import os

import sys
from optparse import OptionParser

from numpy import log10
from array import array


padRatio = 0.25
padOverlap = 0.15

padGap = 0.005

plotDirectory = "data_pre_plots"

_fileDir ="/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/"

gROOT.SetBatch(True)

YesLog = True
NoLog=False


regionText ="loose selection"


import CMS_lumi

from Style import *
thestyle = Style()

HasCMSStyle = False
style = None
if os.path.isfile('tdrstyle.C'):
    ROOT.gROOT.ProcessLine('.L tdrstyle.C')
    ROOT.setTDRStyle()
    print "Found tdrstyle.C file, using this style."
    HasCMSStyle = True
    if os.path.isfile('CMSTopStyle.cc'):
        gROOT.ProcessLine('.L CMSTopStyle.cc+')
        style = CMSTopStyle()
        style.setupICHEPv1()
        print "Found CMSTopStyle.cc file, use TOP style if requested in xml file."
if not HasCMSStyle:
    print "Using default style defined in cuy package."
    thestyle.SetStyle()

ROOT.gROOT.ForceStyle()

stackList = { "TTbar":[kRed], "WJets":[kGreen], "ST":[kYellow], "DY":[kBlue], "VV":[kOrange], "QCD":[kTeal]}

print stackList

_channelText = "#mu+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True


H = 1000;
W = 1200;


# references for T, B, L, R                                                                                                             
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.1*W

# SetOwnership(canvas, False)
# SetOwnership(canvasRatio, False)
# SetOwnership(pad1, False)
# SetOwnership(pad2, False)

legendHeightPer = 0.04
legList = stackList.keys() 
#legList.reverse()

legendStart = 0.69
legendEnd = 0.97-(R/W)

legend = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.), legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))
legend.SetNColumns(2)


legendR = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.)-0.1, legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))

legendR.SetNColumns(2)

legendR.SetBorderSize(0)
legendR.SetFillColor(0)

legend.SetBorderSize(0)
legend.SetFillColor(0)

_file = {}

canvas = TCanvas('c1','c1',W,H)
canvas.SetFillColor(0)
canvas.SetBorderMode(0)
canvas.SetFrameFillStyle(0)
canvas.SetFrameBorderMode(0)
canvas.SetLeftMargin( L/W )
canvas.SetRightMargin( R/W )
canvas.SetTopMargin( T/H )
canvas.SetBottomMargin( B/H )
canvas.SetTickx(0)

canvasRatio = TCanvas('c1Ratio','c1Ratio',W,H)
canvasRatio.SetFillColor(0)
canvasRatio.SetBorderMode(0)
canvasRatio.SetFrameFillStyle(0)
canvasRatio.SetFrameBorderMode(0)
canvasRatio.SetLeftMargin( L/W )
canvasRatio.SetRightMargin( R/W )
canvasRatio.SetTopMargin( T/H )
canvasRatio.SetBottomMargin( B/H )
canvasRatio.SetTickx(0)
canvasRatio.SetTicky(0)
canvasRatio.Draw()
canvasRatio.cd()


pad1 = TPad("zxc_p1","zxc_p1",0,padRatio-padOverlap,1,1)
pad2 = TPad("qwe_p2","qwe_p2",0,0,1,padRatio+padOverlap)
pad1.SetLeftMargin( L/W )
pad1.SetRightMargin( R/W )
pad1.SetTopMargin( T/H/(1-padRatio+padOverlap) )
pad1.SetBottomMargin( (padOverlap+padGap)/(1-padRatio+padOverlap) )
pad2.SetLeftMargin( L/W )
pad2.SetRightMargin( R/W )
pad2.SetTopMargin( (padOverlap)/(padRatio+padOverlap) )
pad2.SetBottomMargin( B/H/(padRatio+padOverlap) )
pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetFrameFillStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetTickx(0)
pad1.SetTicky(0)

pad2.SetFillColor(0)
pad2.SetFillStyle(4000)
pad2.SetBorderMode(0)
pad2.SetFrameFillStyle(0)
pad2.SetFrameBorderMode(0)
pad2.SetTickx(0)
pad2.SetTicky(0)


canvasRatio.cd()
pad1.Draw()
pad2.Draw()


canvas.cd()


canvas.ResetDrawn()

stack = THStack("hs","stack")
#SetOwnership(stack,True)
histName="DeltaY"
histograms = {
              "TTbar"   : ["#cbar #Delta y #cbar", "Events", 28, [-2.,-1.,-0.5,0.,0.5,1.,2.]],
              "WJets"   : ["#cbar #Delta y #cbar", "Events", 28, [-2.,-1.,-0.5,0.,0.5,1.,2]],
              "ST"   : ["#cbar #Delta y #cbar", "Events", 28, [-2.,-1.,-0.5,0.,0.5,1.,2.]],
              "QCD"   : ["#cbar #Delta y #cbar", "Events", 28, [-2.,-1.,-0.5,0.,0.5,1.,2.]],
              "DY"   : ["#cbar #Delta y #cbar", "Events", 28, [-2.,-1.,-0.5,0.,0.5,1.,2.]],
}

sample_names = [ "TTbar", "DY", "QCD", "ST", "WJets"]
hist1_={}
for sample in sample_names:
    _file[sample] = TFile("Input_undfolding_data.root","read")
    hist1_[sample] = _file[sample].Get(sample)            
    hist1_[sample].SetFillColor(stackList[sample][0])
    hist1_[sample].SetLineColor(stackList[sample][0])
    hist1_[sample].SetYTitle(histograms["TTbar"][1])        
    legendR.AddEntry(hist1_[sample],sample,'f')
    stack.Add(hist1_[sample])     

_file["Data"] = TFile("Input_undfolding_data_.root","read")
dataHist=_file["Data"].Get("Data")
data=dataHist.GetBinContent(1)
dataHist.SetMarkerColor(kBlack)
dataHist.SetYTitle(histograms["TTbar"][1])     
dataHist.Draw("pe,x0")
stack.Draw("HIST,SAME")

oneLine = TF1("oneline","1",-9e9,9e9)
oneLine.SetLineColor(kBlack)
oneLine.SetLineWidth(1)
oneLine.SetLineStyle(2)


maxVal =stack.GetMaximum()
minVal = 1
minVal = max(stack.GetStack()[0].GetMinimum(),1)

log=0
if log:
    stack.SetMaximum(10**(1.5*log10(maxVal) - 0.5*log10(minVal)))
else:
    stack.SetMaximum(1.7*maxVal)
    stack.SetMinimum(minVal)

errorband=stack.GetStack().Last().Clone("error")
errorband.Sumw2()
errorband.SetLineColor(kBlack)
errorband.SetFillColor(kBlack)
errorband.SetFillStyle(3245)
errorband.SetMarkerSize(0)

canvas.Clear()
canvasRatio.cd()
canvasRatio.ResetDrawn()
canvasRatio.Draw()
canvasRatio.cd()

pad1.Draw()
pad2.Draw()

pad1.cd()

pad1.SetLogy(log)

y2 = pad1.GetY2()


stack.Draw("HIST")

stack.GetXaxis().SetTitle('')
stack.GetYaxis().SetTitle(dataHist.GetYaxis().GetTitle())

stack.SetTitle('')
stack.GetXaxis().SetLabelSize(0)
stack.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(1.3-padRatio+padOverlap))
stack.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitle("Events")


dataHist.Draw("E,X0,SAME")
legendR.AddEntry(dataHist, "Data", 'pe')
ratio = dataHist.Clone("temp")
temp = stack.GetStack().Last().Clone("temp")
for i_bin in range(1,temp.GetNbinsX()+1):
    temp.SetBinError(i_bin,0.)
ratio.Divide(temp)
ratio.SetTitle('')
ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(10+padRatio+padOverlap))
ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(0.4+padRatio+padOverlap))
#ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(0.3+padRatio+padOverlap))
ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
ratio.GetYaxis().SetRangeUser(0.4,1.6)

labels = ["[-2.,-1.5]","[-1.5,-1.25]","[-1.25,-1]","[-1,-0.75]","[-0.75,-0.5]","[-0.5,-0.25]","[-0.25,0]","[0,0.25]","[0.25,0.5]","[0.5,0.75]","[0.75,1.]","[1,1.25]","[1.25,1.5]","[1.5,2.]",
         "[-2.,-1.5]","[-1.5,-1.25]","[-1.25,-1]","[-1,-0.75]","[-0.75,-0.5]","[-0.5,-0.25]","[-0.25,0]","[0,0.25]","[0.25,0.5]","[0.5,0.75]","[0.75,1.]","[1,1.25]","[1.25,1.5]","[1.5,2.]"]
#"[-1.5,-1.25]","[-1.25,-1]","[-1,-0.75]","[-0.75,-0.5]","[-0.5,-0.25]","[-0.25,0]","[0,0.25]","[0.25,0.5]","[0.5,0.75]","[0.75,1.]","[1,1.25]","[1.25,1.5]","[1.5,2.]"]
y=-2400
t = TText( 1.5, 9.75, 'File' )
t.SetTextAngle(45);
t.SetTextSize(0.02);
t.SetTextAlign(33);
for i in range(0,28):
    x = ratio.GetXaxis().GetBinCenter(i+1);
    t.DrawText(x,y,labels[i]);

#ratio.GetXaxis().SetLabelOffset(999);
#ratio.GetXaxis().SetLabelSize(0);


ratio.GetYaxis().SetNdivisions(504)
ratio.GetXaxis().SetTitle(histograms["TTbar"][0])
ratio.GetYaxis().SetTitle("Data/MC")
CMS_lumi.CMS_lumi(pad1, 4, 11)
legendR.Draw()
pad2.cd()
ratio.SetMarkerStyle(dataHist.GetMarkerStyle())
ratio.SetMarkerSize(dataHist.GetMarkerSize())
ratio.SetLineColor(dataHist.GetLineColor())
ratio.SetLineWidth(dataHist.GetLineWidth())
ratio.Draw('e,x0')
errorband.Divide(temp)
errorband.Draw('e2,same')
oneLine.Draw("same")

canvasRatio.Update()
canvasRatio.RedrawAxis()
if log:
    canvasRatio.SaveAs("%s_new_log.pdf"%(histName))
else:
    canvasRatio.SaveAs("DeltaY_stack.pdf")


