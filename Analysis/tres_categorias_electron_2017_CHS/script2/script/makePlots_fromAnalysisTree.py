#from ROOT import TFile, TLegend, TCanvas, TPad, THStack, TF1, TPaveText, TGaxis, SetOwnership, TObject, gStyle,TH1F
from ROOT import *
import os

import sys
from optparse import OptionParser

from numpy import log10
from array import array

import cms_figure

padRatio = 0.25
padOverlap = 0.15

padGap = 0.01

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

stackList = { "Ttbar":[kRed], "wjets":[kGreen], "singletop":[kYellow], "dy":[kBlue], "vv":[kOrange], "qcd":[kTeal]}

print stackList

_channelText = "#mu+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True


H = 600;
W = 800;


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
#              "Mttbar": ["Mttbar", "Events", 20, [0, 2000]], 
              "DeltaY": ["DeltaY", "Events", 8, [-2,2]], 
}

sample_names = [ "Ttbar", "dy", "qcd", "singletop", "vv", "wjets"]
control_regions = ["CR1_muon_prefit", "CR1_muon_postfit","SR0T_muon_prefit", "SR0T_muon_postfit", "SR1T_muon_prefit", "SR1T_muon_postfit"]
legend_index = 0
for region in control_regions:
    _file = {}
    sum_=0
    tree_MC={}
    tree2_MC={}
    hist={}
    hist1_={}
    histo={}
    for sample in sample_names:
    	_file[sample] = TFile("MDF_shapes.root","read")
        _file[sample].cd(region)
        hist1_[sample] = _file[sample].Get(region+'/'+sample)            
        hist1_[sample].SetFillColor(stackList[sample][0])
        hist1_[sample].SetLineColor(stackList[sample][0])
        if(legend_index == 0):
            legendR.AddEntry(hist1_[sample],sample,'f')       
        hist1_[sample].SetYTitle(histograms[histName][1])        
    	stack.Add(hist1_[sample])     
    _file["Data"] = TFile("MDF_shapes.root","read")
    _file["Data"].cd(region) 
    dataHist=_file["Data"].Get(region+'/'+"data_obs")
    data=dataHist.GetBinContent(1)
    dataHist.SetMarkerColor(kBlack)
    dataHist.SetYTitle(histograms[histName][1])     
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
    stack.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(1.-padRatio+padOverlap))
    stack.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(1.-padRatio+padOverlap))
    stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap))
    stack.GetYaxis().SetTitle("Events")
    
    dataHist.Draw("E,X0,SAME")
    if(legend_index == 0):
        legendR.AddEntry(dataHist, "Data", 'pe')
    ratio = dataHist.Clone("temp")
    temp = stack.GetStack().Last().Clone("temp")
#    for i_bin in range(1,temp.GetNbinsX()+1):
#       temp.SetBinError(i_bin,0.)
    ratio.Divide(temp)
    ratio.SetTitle('')
    ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
    ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
    ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
    ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
    ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
    ratio.GetYaxis().SetRangeUser(0.4,1.6)
    ratio.GetYaxis().SetNdivisions(504)
    ratio.GetXaxis().SetTitle(histograms[histName][0])
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
    	canvasRatio.SaveAs("%s.pdf"%(region))
    legend_index = legend_index + 1 
    
'''    
