
import array
import ROOT as R
import sys
import numpy as np

#primero gen y luego rec
samplelist = {
'11':'Input_undfolding_data_1_1.root',
'12':'Input_undfolding_data_1_2.root',
#'13':'Input_undfolding_data_1_3.root',
'21':'Input_undfolding_data_2_1.root',
'22':'Input_undfolding_data_2_2.root',
#'23':'Input_undfolding_data_2_3.root',
#'31':'Input_undfolding_data_3_1.root',
#'32':'Input_undfolding_data_3_2.root',
#'33':'Input_undfolding_data_3_3.root',
}

fout = R.TFile('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/Combine_higgs/dd_inputs.root', 'recreate')


my_array_gen = array.array('d', [-2.,-1.,0.,1.,2.,
				3.,4.,5,6])
#				6.5,7.,7.5,8.,8.5,9.,9.5,10])
my_array_rec = array.array('d', [-2,-1.,-0.5,0.,0.5,1.,2.,
				 3.,3.5,4.,4.5,5,6])
#				 6.5,6.75,7.,7.25,7.5,7.75,8.,8.25,8.5,8.75,9.,9.25,9.5,10.])

bins_array_gen = len(my_array_gen) - 1
bins_array_rec = len(my_array_rec) - 1 

 
Migration_Matrix = R.TH2F("Migration_Matrix","",bins_array_rec,my_array_rec,bins_array_gen,my_array_gen);
Data = R.TH1F("Data","",bins_array_rec,my_array_rec);
TTbar = R.TH1F("TTbar","",bins_array_rec,my_array_rec);
WJets = R.TH1F("WJets","",bins_array_rec,my_array_rec);
ST = R.TH1F("ST","",bins_array_rec,my_array_rec);
DY = R.TH1F("DY","",bins_array_rec,my_array_rec);
QCD = R.TH1F("QCD","",bins_array_rec,my_array_rec);
Var_gen = R.TH1F("Var_gen","",bins_array_gen,my_array_gen);

ttbar_pu_down = R.TH1F("ttbar_pu_down","",bins_array_rec,my_array_rec); 
ttbar_pu_up = R.TH1F("ttbar_pu_up","",bins_array_rec,my_array_rec);
ttbar_Trigger_down = R.TH1F("ttbar_Trigger_down","",bins_array_rec,my_array_rec);
ttbar_Trigger_up = R.TH1F("ttbar_Trigger_up","",bins_array_rec,my_array_rec);
ttbar_MuonID_down = R.TH1F("ttbar_MuonID_down","",bins_array_rec,my_array_rec);
ttbar_MuonID_up = R.TH1F("ttbar_MuonID_up","",bins_array_rec,my_array_rec);
ttbar_mistoptag_down = R.TH1F("ttbar_mistoptag_down","",bins_array_rec,my_array_rec);
ttbar_mistoptag_up = R.TH1F("ttbar_mistoptag_up","",bins_array_rec,my_array_rec);

dd_Matrix = R.TH2F("","",bins_array_rec,my_array_rec,bins_array_gen,my_array_gen) 

bin_index = 0
for key_sample in sorted(samplelist):
    print(key_sample[1])
    fin = R.TFile(samplelist[key_sample])
    dir = R.gDirectory.GetListOfKeys()
    for key_dir in dir:
        name = key_dir.GetName()
        temp = fin.Get(name)
        if(name != "Migration_Matrix"):
            for i in range(1,7):
                suma = temp.GetBinContent(i) 
                if(key_sample[1] == "1"):
                    bin_index = 0
                if(key_sample[1] == "2"):
                    bin_index = 6
                if(key_sample[1] == "3"):
                    bin_index = 12
                if (name == "Data" and key_sample[0] == "1"):
                    Data.SetBinContent(i + bin_index,Data.GetBinContent(i + bin_index)+ suma) 
                if (name == "TTbar"):
                    TTbar.SetBinContent(i + bin_index,TTbar.GetBinContent(i + bin_index)+ suma)
                if (name == "WJets"):
                    WJets.SetBinContent(i + bin_index,WJets.GetBinContent(i + bin_index)+ suma)
                if (name == "ST"):
                    ST.SetBinContent(i + bin_index,ST.GetBinContent(i + bin_index)+ suma)                
                if (name == "QCD"):
                    QCD.SetBinContent(i + bin_index,QCD.GetBinContent(i + bin_index)+ suma)
                if (name == "DY"):
                    DY.SetBinContent(i + bin_index,DY.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_pu_up"):
                    ttbar_pu_up.SetBinContent(i + bin_index,ttbar_pu_up.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_pu_down"):
                    ttbar_pu_down.SetBinContent(i + bin_index,ttbar_pu_down.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_Trigger_up"):
                    ttbar_Trigger_up.SetBinContent(i + bin_index,ttbar_Trigger_up.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_Trigger_down"):
                    ttbar_Trigger_down.SetBinContent(i + bin_index,ttbar_Trigger_down.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_MuonID_up"):
                    ttbar_MuonID_up.SetBinContent(i + bin_index,ttbar_MuonID_up.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_MuonID_down"):
                    ttbar_MuonID_down.SetBinContent(i + bin_index,ttbar_MuonID_down.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_mistoptag_up"):
                    ttbar_MuonID_up.SetBinContent(i + bin_index,ttbar_mistoptag_up.GetBinContent(i + bin_index)+ suma)
                if (name == "ttbar_mistoptag_down"):
                    ttbar_MuonID_down.SetBinContent(i + bin_index,ttbar_mistoptag_down.GetBinContent(i + bin_index)+ suma)
            for i in range(1,5):
                suma = temp.GetBinContent(i)
                if(key_sample[0] == "1"):
                    bin_index = 0
                if(key_sample[0] == "2"):
                    bin_index = 4
                if(key_sample[0] == "3"):
                    bin_index = 8                
                if (name == "Var_gen"):
                    Var_gen.SetBinContent(i + bin_index,Var_gen.GetBinContent(i + bin_index)+ suma)
            del temp 
        if(name == "Migration_Matrix"):
           for i in range(1,7):
               for j in range(1,9):
                    if(key_sample[1] == "1"):
                        bin_index_rec = 0
                    if(key_sample[1] == "2"):
                        bin_index_rec = 6
                    if(key_sample[1] == "3"):
                        bin_index_rec = 12               
                    if(key_sample[0] == "1"):
                        bin_index_gen = 0
                    if(key_sample[0] == "2"):
                        bin_index_gen = 4
                    if(key_sample[0] == "3"):
                        bin_index_gen = 8
                    suma = temp.GetBinContent(i,j)         
                    Migration_Matrix.SetBinContent(i + bin_index_rec,j + bin_index_gen, suma)
               
            
fout.cd('')
R.gDirectory.WriteObject(Migration_Matrix,"Migration_Matrix")
R.gDirectory.WriteObject(TTbar,"TTbar")
R.gDirectory.WriteObject(WJets,"WJets")
R.gDirectory.WriteObject(Data,"Data")
R.gDirectory.WriteObject(ST,"ST")
R.gDirectory.WriteObject(QCD,"QCD")
R.gDirectory.WriteObject(DY,"DY")
R.gDirectory.WriteObject(Var_gen,"Var_gen")
R.gDirectory.WriteObject(ttbar_pu_up,"ttbar_pu_up")
R.gDirectory.WriteObject(ttbar_pu_down,"ttbar_pu_down")
R.gDirectory.WriteObject(ttbar_Trigger_up,"ttbar_Trigger_up")
R.gDirectory.WriteObject(ttbar_Trigger_down,"ttbar_Trigger_down")
R.gDirectory.WriteObject(ttbar_MuonID_up,"ttbar_MuonID_up")
R.gDirectory.WriteObject(ttbar_MuonID_down,"ttbar_MuonID_down")
R.gDirectory.WriteObject(ttbar_MuonID_up,"ttbar_mistoptag_up")
R.gDirectory.WriteObject(ttbar_MuonID_down,"ttbar_mistoptag_down")
