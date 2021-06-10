from ROOT import *
import sys
import numpy

ct_top = '(weight)'
systematic_direction_ttbar={'nominal':ct_top}

for i in range(0,100):
    pdfstring  = '*(wgtMC__PDF['+str(i)+'])'
    systematic_direction_ttbar['wgtMC__PDF_'+str(i)] = ct_top+pdfstring

samplelist = {
'ttbar':'/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon///workdir_Zprime_Analysis_2018_CHS/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_2.root',
}

categories=['T1']
fout = TFile('mu_Test_4cat_PDF_SR1T.root', 'recreate')

fout.mkdir("SR1T")
fout.mkdir("SR1T/ttbar")
gROOT.SetBatch(kTRUE)
                               
for cat in categories:
    cut_string_GL='(Mttbar<2000 & Mttbar>200 &'
    if cat == 'T1':
        cut_string = cut_string_GL+' rec_chi2<30  '
        a=0
        for key_sample in samplelist:
            if key_sample == 'QCD':
                continue
            myfile = TFile(samplelist[key_sample])
            mytree = myfile.Get("AnalysisTree")
            mytree.SetAlias("invmass","DeltaY")
            gDirectory.cd('mu_Test_4cat_PDF_SR1T.root:/SR1T/'+key_sample)
            if key_sample == 'DATA':
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat_PDF_SR1T.root:/SR1T/data_obs')
                cut = str(cut_string+' & ttagN==1 & btagN>=0)')
                print("--------------------------------------")
                print "Processing: ",key_sample
                print "Applying cut:",cut
                tempdata = TH1F("tempdata","tempdata",8,-2,2)
                mytree.Draw("invmass>>tempdata",cut)
                tempdata.SetName(key_sample)
                gDirectory.WriteObject(tempdata,'nominal')
                del tempdata
            elif 'ttbar' in key_sample:
                for syst in systematic_direction_ttbar:
                    cut = str(cut_string+' & ttagN==1 & btagN>=0)*1.00*'+systematic_direction_ttbar[syst])
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    if syst == 'nominal':
                        temp = TH1F("temp","temp",8,-2,2)
                        mytree.Draw("invmass>>temp",cut)
                        temp.SetName(syst)
                        print "Rebinning T1 nom:", str(temp.GetNbinsX())
                        gDirectory.WriteObject(temp,syst)
                        del temp
                    elif 'nominal' not in syst:
                        temp2sys = TH1F("temp2sys","temp2sys",8,-2,2)
                        mytree.Draw("invmass>>temp2sys",cut)
                        temp2sys.SetName(syst)
                        gDirectory.WriteObject(temp2sys,syst)
                        del temp2sys
            elif 'wjets_l' in key_sample:
                for syst in systematic_direction_wjets:
                    cut = str(cut_string+' &  ttagN==1 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_wjets[syst])
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    if syst == 'nominal':
                        temp = TH1F("temp","temp",140,200,7000)
                        mytree.Draw("invmass>>temp",cut)
                        temp.SetName(syst)
                        print "Rebinning T1 nom:", str(temp.GetNbinsX())
                        gDirectory.WriteObject(temp,syst)
                        del temp
                    elif 'nominal' not in syst:
                        temp2sys = TH1F("temp2sys","temp2sys",140,200,7000)
                        mytree.Draw("invmass>>temp2sys",cut)
                        temp2sys.SetName(syst)
                        gDirectory.WriteObject(temp2sys,syst)
                        del temp2sys
            elif 'singletop' or 'DY' or 'wjets_c' or 'wjets_b' in key_sample:
                for syst in systematic_direction_wjets:
                    cut = str(cut_string+' &  ttagN==1 & btagN>=0)*(wgtMC__GEN)*'+systematic_direction_otherbkgs[syst])
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    if syst == 'nominal':
                        temp = TH1F("temp","temp",140,200,7000)
                        mytree.Draw("invmass>>temp",cut)
                        temp.SetName(syst)
                        print "Rebinning T1 nom:", str(temp.GetNbinsX())
                        gDirectory.WriteObject(temp,syst)
                        del temp
                    elif 'nominal' not in syst:
                        temp2sys = TH1F("temp2sys","temp2sys",140,200,7000)
                        mytree.Draw("invmass>>temp2sys",cut)
                        temp2sys.SetName(syst)
                        gDirectory.WriteObject(temp2sys,syst)
                        del temp2sys


