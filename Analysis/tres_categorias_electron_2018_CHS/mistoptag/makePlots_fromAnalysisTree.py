#from ROOT import TFile, TLegend, TCanvas, TPad, THStack, TF1, TPaveText, TGaxis, SetOwnership, TObject, gStyle,TH1F
from ROOT import *
import os

import sys
from sys import argv
from optparse import OptionParser

from numpy import log10
from array import array



padRatio = 0.25
padOverlap = 0.15

padGap = 0.01

plotDirectory = "data_pre_plots"

_fileDir ="/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/electron/"

gROOT.SetBatch(True)

YesLog = True
NoLog=False


# Histogram Information:
# [X-axis title, 
#  Y-axis title,
#  Rebinning factor,
#  [x-min,x-max], -1 means keep as is
#  Extra text about region
#  log plot]
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

stackList = {"TTToHadronic_2018":[kBlue-5], "TTTo2L2Nu_2018":[kRed-5], "TTToSemiLeptonic_2018":[kRed],"DYJetsToLL_M-50_HT_2018":[kBlue], "QCD_HT_2018":[kTeal], "WJetsToLNu_2018":[kGreen], "ST_2018":[kYellow], "WW_WZ_ZZ_2018":[kOrange]}

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

#legend = TLegend(2*legendStart - legendEnd, 1-T/H-0.01 - legendHeightPer*(len(legList)+1), legendEnd, 0.99-(T/H)-0.01)
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
stack_pu_up = THStack("hs_pu_up","stack_pu_up")
stack_pu_down = THStack("hs_pu_down","stack_pu_down")


histName=argv[1]
sum_=0
tree_MC={}
tree2_MC={}
tree_pu_up_MC={}

hist={}
hist1_={}

hist1_muonId_Up={}
hist1_muonId_Down={}
hist1_pu_Up={}
hist1_pu_Down={}




histo={}

histograms = {
              "MET_pt"   : ["missing E_{T} [GeV]", "Events", 10, [50,1500]],
              "lep1_pt":[ "p_{T}^{#lep} [GeV]", "Events",50, [50, 500]],
              "Mttbar": ["Mttbar", "Events", 20, [0, 2000]], 
              "Ak8_j1_pt": ["Ak8_j1_pt", "Events", 25, [400,1200]],
              "rec_chi2": ["rec_chi2", "Events", 20, [30,300]],
              "N_Ak8": ["N_Ak8", "Events", 5, [0,5]],
              "N_Ak4": ["N_Ak4", "Events", 10, [0,10]],
              "DeltaY": ["DeltaY", "Events", 8, [-2,2]], 
}

sample_names = ["TTToHadronic_2018", "TTTo2L2Nu_2018", "DYJetsToLL_M-50_HT_2018", "QCD_HT_2018", "WJetsToLNu_2018", "ST_2018", "WW_WZ_ZZ_2018", "TTToSemiLeptonic_2018"]

for sample in sample_names:
        	print sample, histName
		_file[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
        	print "%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample)
		tree2_MC[sample]=_file[sample].Get("AnalysisTree")
	        tree2_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pt_rew*weight_btagdisc_central*1.*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_[sample] = tree2_MC[sample].GetHistogram()                
      	  	hist1_[sample].SetFillColor(stackList[sample][0])
        	hist1_[sample].SetLineColor(stackList[sample][0])
		legendR.AddEntry(hist1_[sample],sample,'f')       
        	hist1_[sample].SetYTitle(histograms[histName][1])        
		stack.Add(hist1_[sample])     

                tree_pu_up_MC[sample]=_file[sample].Get("AnalysisTree")
                tree_pu_up_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu_up*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pt_rew*weight_btagdisc_central*1.*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_pu_Up[sample] = tree2_MC[sample].GetHistogram()
                hist1_pu_Up[sample].SetFillColor(stackList[sample][0])
                hist1_pu_Up[sample].SetLineColor(stackList[sample][0])
                stack_pu_up.Add(hist1_pu_Up[sample])

#                tree2_MC[sample]=_file[sample].Get("AnalysisTree")
#                tree2_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu_down*weight_sfelec_TightID*weight_sfelec_Trigger*weight_pt_rew*weight_btagdisc_central*1.*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
#                hist1_pu_Down[sample] = tree2_MC[sample].GetHistogram()
#                hist1_pu_Down[sample].SetFillColor(stackList[sample][0])
#                hist1_pu_Down[sample].SetLineColor(stackList[sample][0])
#                stack_pu_down.Add(hist1_pu_Down[sample])


_file["Data"] = TFile("%s/uhh2.AnalysisModuleRunner.DATA.DATA_EGamma_Run2018.root"%(_fileDir),"read")
print "%s/uhh2.AnalysisModuleRunner.DATA.DATA.root"%(_fileDir)

tree = _file["Data"].Get("AnalysisTree")
tree.Draw("%s>>dat_hist(%i,%i,%f)"%(histName,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"(wtagN == 0 && ttagN == 0 && btagN>=1 && rec_chi2 < 30 && Mttbar < 2000)")
dataHist=tree.GetHistogram()
print "total:",dataHist.Integral()
print "bins:",dataHist.GetNbinsX()
data=dataHist.GetBinContent(1)
print data
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
print minVal, maxVal

print "data, top:",dataHist.GetBinContent(1)

print "max stack:",1.5*maxVal
print histName 

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


histName=argv[1]

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

legendR.AddEntry(dataHist, "Data", 'pe')

ratio = dataHist.Clone("temp")
temp = stack.GetStack().Last().Clone("temp")
print temp.GetNbinsX(), ratio.GetNbinsX()

for i_bin in range(1,temp.GetNbinsX()+1):
       	temp.SetBinError(i_bin,0.)
ratio.Divide(temp)
print ratio.GetNbinsX()
print ratio
print ratio.GetNbinsX()
ratio.SetTitle('')


ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
ratio.GetYaxis().SetRangeUser(0.4,1.6)
ratio.GetYaxis().SetNdivisions(504)
#ratio.GetXaxis().SetTitle(histograms[histName][0])
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
	canvasRatio.SaveAs("%s_new.pdf"%(histName))



