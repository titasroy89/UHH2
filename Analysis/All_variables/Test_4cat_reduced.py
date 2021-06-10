import array
from ROOT import *
from scales import *
import sys
import numpy
ct = '(wgtMC__topptREWGT_ct)*(weight_sfmu_ID)*(weight_pu)*(weight_sfmu_TRK)*(weight_sfmu_HLT)*(wgtMC__ttagSF_ct)*(weight_csv_central)'
jerupdir = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/TTbarLJAnalysisLiteModule_NOTBLINDED_20180331_JERhybrid_topptReweight_oldMuonSF_toptagMLE3_addTTBarRecDebugVars_dRlepAK8_removeAK8_jer_up/T1_v06/muon/"


samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016_BLINDED.root',
'singletop':'uhh2.AnalysisModuleRunner.MC.ST.root',
'QCD':'uhh2.AnalysisModuleRunner.MC.QCD_Pt.root',
'DY':'uhh2.AnalysisModuleRunner.MC.DY.root',
'VV':'uhh2.AnalysisModuleRunner.MC.VV.root',
'wjets_l':'uhh2.AnalysisModuleRunner.MC.WJets__L.root',
'wjets_b':'uhh2.AnalysisModuleRunner.MC.WJets__B.root',
'wjets_c':'uhh2.AnalysisModuleRunner.MC.WJets__C.root',
'ttbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root',
'ZprimeNarrow0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0500.root', 'ZprimeWide0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M0500.root', 'ZprimeUltraWide1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M1000.root', 'ZprimeJets0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M0500.root',
'ZprimeNarrow0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0750.root', 'ZprimeWide0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M0750.root', 'ZprimeUltraWide2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M2000.root', 'ZprimeJets0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M0750.root',	
'ZprimeNarrow1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1000.root', 'ZprimeWide1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1000.root', 'ZprimeUltraWide3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M3000.root', 'ZprimeJets1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1000.root',
'ZprimeNarrow1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1250.root', 'ZprimeWide1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1250.root', 'ZprimeUltraWide4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M4000.root', 'ZprimeJets1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1250.root',
'ZprimeNarrow1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1500.root', 'ZprimeWide1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1500.root', 'ZprimeUltraWide5000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M5000.root', 'ZprimeJets1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1500.root',
'ZprimeNarrow2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2000.root', 'ZprimeWide2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2000.root', 'ZprimeUltraWide6000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M6000.root', 'ZprimeJets2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M2000.root',
'ZprimeNarrow2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2500.root', 'ZprimeWide2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2500.root', 'ZprimeUltraWide6500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M6500.root', 'ZprimeJets2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M2500.root',
'ZprimeNarrow3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3000.root', 'ZprimeWide3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3000.root', 'ZprimeUltraWide7000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M7000.root', 'ZprimeJets3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3000.root',
'ZprimeNarrow3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3500.root', 'ZprimeWide3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3500.root', 'ZprimeJets3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3500.root',
'ZprimeNarrow4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M4000.root', 'ZprimeWide4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M4000.root', 'ZprimeJets4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M4000.root',
'ZprimeNarrow4500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M4500.root', 'ZprimeWide4500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M4500.root', 
'ZprimeNarrow5000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M5000.root', 'ZprimeWide5000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M5000.root', 
'ZprimeNarrow6000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M6000.root', 'ZprimeWide6000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M6000.root', 
'ZprimeNarrow6500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M6500.root', 'ZprimeWide6500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M6500.root', 
'ZprimeNarrow7000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M7000.root', 'ZprimeWide7000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M7000.root' 
}

categories=['T1','T0', 'NT0', 'NT1']
fout = TFile('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root', 'recreate')

type = ['SR1T','SR0T','CR1','CR2']
process  = ['ttbar','wjets_l','singletop','ZprimeNarrow1500','ZprimeNarrow3000','data_obs','QCD','wjets_c','wjets_b','VV','DY','ZprimeNarrow0500','ZprimeNarrow0750','ZprimeNarrow1000','ZprimeNarrow1250','ZprimeNarrow2000','ZprimeNarrow2500','ZprimeNarrow3500','ZprimeNarrow4000','ZprimeNarrow4500','ZprimeNarrow5000','ZprimeNarrow6000','ZprimeNarrow6500','ZprimeNarrow7000',
            'ZprimeWide0500','ZprimeWide0750','ZprimeWide1000','ZprimeWide1250','ZprimeWide1500','ZprimeWide2000','ZprimeWide2500','ZprimeWide3000','ZprimeWide3500','ZprimeWide4000','ZprimeWide4500','ZprimeWide5000','ZprimeWide6000','ZprimeWide6500','ZprimeWide7000',
            'ZprimeUltraWide0500','ZprimeUltraWide0750','ZprimeUltraWide1000','ZprimeUltraWide1250','ZprimeUltraWide1500','ZprimeUltraWide2000','ZprimeUltraWide2500','ZprimeUltraWide3000','ZprimeUltraWide3500','ZprimeUltraWide4000','ZprimeUltraWide4500','ZprimeUltraWide5000','ZprimeUltraWide6000','ZprimeUltraWide6500','ZprimeUltraWide7000',
            'ZprimeJets0500','ZprimeJets0750','ZprimeJets1000','ZprimeJets1250','ZprimeJets1500','ZprimeJets2000','ZprimeJets2500','ZprimeJets3000','ZprimeJets3500','ZprimeJets4000'] 

for t in type:
    for p in process:
        fout.mkdir(t+'/'+p)
gROOT.SetBatch(kTRUE)

for cat in categories:
    cut_string_GL='(muoN==1 & Mttbar<2000.0 & Mttbar>200.0 &'
    if cat == 'T1':
            cut_string = cut_string_GL+' WJets_TMVA_response>=0.5 & rec_chi2<30  '
            a=0
            for key_sample in samplelist:
                myfile = TFile(samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass","Mttbar")
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR1T/'+key_sample)
                if key_sample == 'DATA':
                    gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR1T/data_obs')
                    cut = str(cut_string+' & ttagN==1 & btagN>=0)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    tempdata = TH1F("tempdata","tempdata",20,200,2000)
                    mytree.Draw("invmass>>tempdata",cut)
                    tempdata.SetName(key_sample)
                    gDirectory.WriteObject(tempdata,'nominal')
                    del tempdata
                elif 'Zprime'in key_sample:
                    for syst in systematic_direction_signal:
                        cut = str(cut_string+' & ttagN==1 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_signal[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",20,200,2000)
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,syst)
                            del temp
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
     		            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR1T/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                elif 'ttbar' in key_sample:
                    for syst in systematic_direction_ttbar:
                        cut = str(cut_string+' & ttagN==1 & btagN>=0)*1.00*(wgtMC__GEN)*'+systematic_direction_ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",20,200,2000)
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,syst)
                            del temp
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR1T/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                elif 'wjets_l' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str(cut_string+' &  ttagN==1 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",20,200,2000)
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,syst)
                            del temp
                        elif 'nominal' not in syst:
		            scale = scales[cat+'__'+key_sample+'__'+syst]
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut+'*('+str(scale)+')')
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                elif 'singletop' in key_sample or 'wjets_b' in key_sample or 'wjets_c' in key_sample or 'DY' in key_sample or 'VV' in key_sample or 'QCD' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str(cut_string+' &  ttagN==1 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp = TH1F("temp","temp",20,200,2000)
                            mytree.Draw("invmass>>temp",cut)
                            temp.SetName(syst)
                            gDirectory.WriteObject(temp,syst)
                            del temp
                        elif 'nominal' not in syst:
                            scale = scales[cat+'__'+key_sample+'__'+syst]
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut+'*('+str(scale)+')')
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys

    elif cat == 'T0':
            a=0
            cut_string = cut_string_GL+' WJets_TMVA_response>=0.5 & rec_chi2<30  '
            for key_sample in samplelist:
                myfile = TFile(samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass","Mttbar")
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR0T/'+key_sample)

                if key_sample == 'DATA':
                    gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR0T/data_obs')
                    cut = str(cut_string+' & ttagN==0 & btagN>=0)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    temp2data = TH1F("temp2data","temp2data",20,200,2000)
                    mytree.Draw("invmass>>temp2data",cut)
                    temp2data.SetName(key_sample)
                    gDirectory.WriteObject(temp2data,'nominal')
                    del temp2data
                elif 'Zprime'in key_sample:
                    for syst in systematic_direction_signal:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_signal[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR0T/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            mytree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                elif 'ttbar' in key_sample:
                    for syst in systematic_direction_ttbar:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*1.00*(wgtMC__GEN)*'+systematic_direction_ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/SR0T/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                                tempsys = TH1F("tempsys","tempsys",20,200,2000)
                                mytree.Draw("invmass>>tempsys",cut)
                                tempsys.SetName(syst)
                                gDirectory.WriteObject(tempsys,syst)
                                del tempsys
                elif 'wjets_l' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif 'nominal' not in syst:
                            scale = scales[cat+'__'+key_sample+'__'+syst]
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            mytree.Draw("invmass>>tempsys",cut+'*('+str(scale)+')')
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                elif 'singletop' in key_sample or 'wjets_b' in key_sample or 'wjets_c' in key_sample or 'QCD' in key_sample or 'DY' in key_sample or 'VV' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str(cut_string+' & ttagN == 0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName('nominal')
                            gDirectory.WriteObject(temp2,'nominal')
                            del temp2
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
			    scale = scales[cat+'__'+key_sample+'__'+syst]
                            mytree.Draw("invmass>>temp2sys",cut+'*('+str(scale)+')')
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                
    elif cat == 'NT0':
            a=0
            cut_string = cut_string_GL+' WJets_TMVA_response < -0.75 & rec_chi2<30  '
            for key_sample in samplelist:
                myfile = TFile(samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass","Mttbar")
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR1/'+key_sample)
                
                if key_sample == 'DATA':
                    gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR1/data_obs')
                    cut = str(cut_string+' & ttagN==0 & btagN>=0)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    temp2data = TH1F("temp2data","temp2data",20,200,2000)
                    mytree.Draw("invmass>>temp2data",cut)
                    temp2data.SetName(key_sample)
                    gDirectory.WriteObject(temp2data,'nominal')
                    del temp2data
                elif 'Zprime'in key_sample:
                    for syst in systematic_direction_signal:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_signal[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR1/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            mytree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                elif 'ttbar' in key_sample:
                    for syst in systematic_direction_ttbar:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*1.00*(wgtMC__GEN)*'+systematic_direction_ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR1/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            mytree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                elif 'wjets_l' in key_sample:
                    for syst in systematic_direction_wjets:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_wjets[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR1/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            mytree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys   
                elif 'singletop' in key_sample or 'wjets_b' in key_sample or 'wjets_c' in key_sample or 'DY' in key_sample or 'VV' in key_sample or 'QCD' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif 'nominal' not in syst:
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            scale = scales[cat+'__'+key_sample+'__'+syst]
                            mytree.Draw("invmass>>tempsys",cut+'*('+str(scale)+')')
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
    elif cat == 'NT1':
            a=0
            cut_string = cut_string_GL+' WJets_TMVA_response < 0.5 & WJets_TMVA_response > 0 & rec_chi2<30  '
            for key_sample in samplelist:
                myfile = TFile(samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass","Mttbar")
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR2/'+key_sample)
                
                if key_sample == 'DATA':
                    gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR2/data_obs')
                    print("--------------------------------------")
                    cut = str(cut_string+' & ttagN==0 & btagN>=0)')
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    temp2data = TH1F("temp2data","temp2data",20,200,2000)
                    mytree.Draw("invmass>>temp2data",cut)
                    temp2data.SetName(key_sample)
                    gDirectory.WriteObject(temp2data,'nominal')
                    del temp2data
                elif 'Zprime'in key_sample:
                    for syst in systematic_direction_signal:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_signal[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR2/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                elif 'ttbar' in key_sample:
                    for syst in systematic_direction_ttbar:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*1.00*(wgtMC__GEN)*'+systematic_direction_ttbar[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR2/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
                elif 'wjets_l' in key_sample:
                    for syst in systematic_direction_wjets:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_wjets[syst])
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat.root:/CR2/'+key_sample)
                            je_tree.SetAlias("invmass","Mttbar")
                            tempsys = TH1F("tempsys","tempsys",20,200,2000)
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,syst)
                            del tempsys
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys
    
                elif 'singletop' in key_sample or 'wjets_b' in key_sample or 'wjets_c' in key_sample or 'DY' in key_sample or 'VV' in key_sample or 'QCD' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str(cut_string+' & ttagN==0 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst == 'nominal':
                            temp2 = TH1F("temp2","temp2",20,200,2000)
                            mytree.Draw("invmass>>temp2",cut)
                            temp2.SetName(syst)
                            gDirectory.WriteObject(temp2,syst)
                            del temp2
                        elif 'nominal' not in syst:
                            temp2sys = TH1F("temp2sys","temp2sys",20,200,2000)
                            scale = scales[cat+'__'+key_sample+'__'+syst]
                            mytree.Draw("invmass>>temp2sys",cut+'*('+str(scale)+')')
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,syst)
                            del temp2sys





