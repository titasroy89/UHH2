from ROOT import *
import os
import math
import sys
from sys import argv
from optparse import OptionParser

from numpy import log10
from array import array


_fileDir ="/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/"
stackList = {"TTToHadronic_2018":[kBlue-5], "TTTo2L2Nu_2018":[kRed-5], "TTToSemiLeptonic_2018":[kRed],"DYJetsToLL_M-50_HT_2018":[kBlue], "QCD_HT_2018":[kTeal], "WJetsToLNu_2018":[kGreen], "ST_2018":[kYellow], "WW_WZ_ZZ_2018":[kOrange]}
print stackList

_file = {}
_file_pu_up={}
_file_pu_down={}
_file_muID_up={}
_file_muID_down={}
_file_trigger_up={}
_file_trigger_down={}
_file_pt_up={}

stack = THStack("hs","stack")
stack_pu_up = THStack("hs_pu_up","stack_pu_up")
stack_pu_down = THStack("hs_pu_down","stack_pu_down")
stack_muID_up = THStack("hs_muID_up","stack_muID_up")
stack_muID_down = THStack("hs_muID_down","stack_muID_down")
stack_trigger_up = THStack("hs_trigger_up","stack_trigger_up")
stack_trigger_down = THStack("hs_trigger_down","stack_trigger_down")
stack_pt_up = THStack("hs_pt_up","stack_pt_up")

histName=argv[1]
sum_=0

tree_MC={}
tree2_MC={}
tree2_MC_pu_up={}
tree2_MC_pu_down={}
tree2_MC_muID_up={}
tree2_MC_muID_down={}
tree2_MC_trigger_up={}
tree2_MC_trigger_down={}
tree2_MC_pt_up={}

hist={}

hist1_={}
hist1_pu_up={}
hist1_pu_down={}
hist1_muID_up={}
hist1_muID_down={}
hist1_trigger_up={}
hist1_trigger_down={}
hist1_pt_up={}

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
		tree2_MC[sample]=_file[sample].Get("AnalysisTree")
	        tree2_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_[sample] = tree2_MC[sample].GetHistogram()                
		stack.Add(hist1_[sample])     

for sample in sample_names:
                _file_pu_up[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_pu_up[sample]=_file_pu_up[sample].Get("AnalysisTree")
                tree2_MC_pu_up[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu_up*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_pu_up[sample] = tree2_MC_pu_up[sample].GetHistogram()
                stack_pu_up.Add(hist1_pu_up[sample])

for sample in sample_names:
                _file_pu_down[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_pu_down[sample]=_file_pu_down[sample].Get("AnalysisTree")
                tree2_MC_pu_down[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu_down*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_pu_down[sample] = tree2_MC_pu_down[sample].GetHistogram()
                stack_pu_down.Add(hist1_pu_down[sample])

for sample in sample_names:
                _file_muID_up[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_muID_up[sample]=_file_muID_up[sample].Get("AnalysisTree")
                tree2_MC_muID_up[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_muID_up[sample] = tree2_MC_muID_up[sample].GetHistogram()
                stack_muID_up.Add(hist1_muID_up[sample])

for sample in sample_names:
                _file_muID_down[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_muID_down[sample]=_file_muID_down[sample].Get("AnalysisTree")
                tree2_MC_muID_down[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_muID_down[sample] = tree2_MC_muID_down[sample].GetHistogram()
                stack_muID_down.Add(hist1_muID_down[sample])

for sample in sample_names:
                _file_trigger_up[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_trigger_up[sample]=_file_trigger_up[sample].Get("AnalysisTree")
                tree2_MC_trigger_up[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfmu_HighPtID_up*weight_sfmu_Trigger_up*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_trigger_up[sample] = tree2_MC_trigger_up[sample].GetHistogram()
                stack_trigger_up.Add(hist1_trigger_up[sample])

for sample in sample_names:
                _file_trigger_down[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_trigger_down[sample]=_file_trigger_down[sample].Get("AnalysisTree")
                tree2_MC_trigger_down[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfmu_HighPtID_down*weight_sfmu_Trigger_down*weight_pt_rew*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_trigger_down[sample] = tree2_MC_trigger_down[sample].GetHistogram()
                stack_trigger_down.Add(hist1_trigger_down[sample])

for sample in sample_names:
                _file_pt_up[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
                tree2_MC_pt_up[sample]=_file_pt_up[sample].Get("AnalysisTree")
                tree2_MC_pt_up[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"weight*weight_pu*weight_sfmu_HighPtID_up*weight_sfmu_Trigger_up*weight_btagdisc_central*1.0*(btagN>=1 && rec_chi2 < 30 && wtagN == 0 && ttagN == 0 && Mttbar < 2000)")
                hist1_pt_up[sample] = tree2_MC_pt_up[sample].GetHistogram()
                stack_pt_up.Add(hist1_pt_up[sample])


_file["Data"] = TFile("%s/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2018.root"%(_fileDir),"read")

tree = _file["Data"].Get("AnalysisTree")
tree.Draw("%s>>dat_hist(%i,%i,%f)"%(histName,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"(wtagN == 0 && ttagN == 0 && btagN>=1 && rec_chi2 < 30 && Mttbar < 2000)")
dataHist=tree.GetHistogram()
data=dataHist.GetBinContent(1)
dataHist.SetMarkerColor(kBlack)
dataHist.SetYTitle(histograms[histName][1])     
dataHist.Draw("pe,x0")
stack.Draw("HIST,SAME")


errorband=stack.GetStack().Last().Clone("error")
errorband.Sumw2()


errorband_pu_up=stack_pu_up.GetStack().Last().Clone("error_pu_up")
errorband_pu_down=stack_pu_down.GetStack().Last().Clone("error_pu_down")
errorband_muID_up=stack_muID_up.GetStack().Last().Clone("error_muID_up")
errorband_muID_down=stack_muID_down.GetStack().Last().Clone("error_muID_down")
errorband_trigger_up=stack_trigger_up.GetStack().Last().Clone("error_trigger_up")
errorband_trigger_down=stack_trigger_down.GetStack().Last().Clone("error_trigger_down")
errorband_pt_up=stack_pt_up.GetStack().Last().Clone("error_pt_up")


error=[]
for i in range(0,errorband.GetNbinsX()):

    error.append(math.sqrt( pow(  abs(abs(errorband_muID_up.GetBinContent(i)) - abs(errorband.GetBinContent(i))) + abs(abs(errorband_muID_down.GetBinContent(i)) - abs(errorband.GetBinContent(i)))         ,2)/4  +    pow(  abs(abs(errorband_pu_up.GetBinContent(i)) - abs(errorband.GetBinContent(i))) + abs(abs(errorband_pu_down.GetBinContent(i)) - abs(errorband.GetBinContent(i)))         ,2)/4  +  pow(  abs(abs(errorband_trigger_up.GetBinContent(i)) - abs(errorband.GetBinContent(i))) + abs(abs(errorband_trigger_down.GetBinContent(i)) - abs(errorband.GetBinContent(i)))         ,2)/4  +  pow(  abs(abs(errorband_muID_up.GetBinContent(i)) - abs(errorband.GetBinContent(i))),2)     ))
 
print error


















