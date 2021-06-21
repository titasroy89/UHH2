#include <algorithm>
#include <iterator>
#include <TROOT.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TRandom.h"
#include "TUnfoldDensity.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);
    TChain *chreco_data = new TChain("AnalysisTree","");
    chreco_data->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.DATA.DATA*.root/AnalysisTree",year.c_str()));
    TTree *treereco_data = (TTree*) chreco_data;

    TChain *chreco_ttbar_others = new TChain("AnalysisTree","");
    chreco_ttbar_others->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToO*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_others = (TTree*) chreco_ttbar_others; 

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

    TChain *chreco_wjets = new TChain("AnalysisTree","");
    chreco_wjets->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.WJets*.root/AnalysisTree",year.c_str()));
    TTree *treereco_wjets = (TTree*) chreco_wjets;

    TChain *chreco_ST = new TChain("AnalysisTree","");
    chreco_ST->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.ST_*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ST = (TTree*) chreco_ST;

    TChain *chreco_DY = new TChain("AnalysisTree","");
    chreco_DY->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.DYJetsToLL*.root/AnalysisTree",year.c_str()));
    TTree *treereco_DY = (TTree*) chreco_DY;

    TChain *chreco_QCD = new TChain("AnalysisTree","");
    chreco_QCD->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.QCD_HT*.root/AnalysisTree",year.c_str()));
    TTree *treereco_QCD = (TTree*) chreco_QCD;

    //jec
    TChain *chreco_ttbar_semi_semi_jec = new TChain("AnalysisTree","");
    chreco_ttbar_semi_semi_jec->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/workdir_Zprime_Analysis_%s_CHS_jec/jec/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_semi_jec = (TTree*) chreco_ttbar_semi_semi_jec;

    //jer
    TChain *chreco_ttbar_semi_semi_jer = new TChain("AnalysisTree","");
    chreco_ttbar_semi_semi_jer->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/workdir_Zprime_Analysis_%s_CHS_jer/jer/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_semi_jer = (TTree*) chreco_ttbar_semi_semi_jer;

//array for variable 

    int len = 0; int len_rec = 0;
    if(var_name == "DeltaY") len = 9, len_rec = 15;
    if(var_name == "Mttbar") len = 8, len_rec = 13;   
    if(var_name == "Rapidity_ttbar_semi") len = 13, len_rec = 23;
    if(var_name == "tlead_pT") len = 6, len_rec = 9;
    if(var_name == "pT_ttbar_semi") len = 6, len_rec = 9;

    Float_t bins_gen[len];
    Float_t new_rec[len_rec];


    if(var_name == "DeltaY"){ 
        Float_t Bins_gen[] = {-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.};
        Float_t New_rec[] = {-2.,-1.5,-1.25,-1.,-0.75,-0.5,-0.25,0.,0.25,0.5,0.75,1.,1.25,1.5,2.};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);

    }

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//-----Bacgrounds------??
    TH1F *Data_boosted = new TH1F("Data_boosted","",newrec,new_rec);
    TH1F *TTbar_boosted = new TH1F("TTbar_boosted","",newrec,new_rec);
    TH1F *TTbar_others_boosted = new TH1F("TTbar_others_bosted","",newrec,new_rec);
    TH1F *WJets_boosted = new TH1F("WJets_boosted","",newrec,new_rec);
    TH1F *ST_boosted = new TH1F("ST_boosted","",newrec,new_rec);
    TH1F *DY_boosted = new TH1F("DY_boosted","",newrec,new_rec);
    TH1F *QCD_boosted = new TH1F("QCD_boosted","",newrec,new_rec);

    TH1F *Data_resolved = new TH1F("Data_resolved","",newrec,new_rec);
    TH1F *TTbar_resolved = new TH1F("TTbar_resolved","",newrec,new_rec);
    TH1F *TTbar_others_resolved = new TH1F("TTbar_others_resolved","",newrec,new_rec);
    TH1F *WJets_resolved = new TH1F("WJets_resolved","",newrec,new_rec);
    TH1F *ST_resolved = new TH1F("ST_resolved","",newrec,new_rec);
    TH1F *DY_resolved = new TH1F("DY_resolved","",newrec,new_rec);
    TH1F *QCD_resolved = new TH1F("QCD_resolved","",newrec,new_rec);

    TH1F *Data_semiresolved = new TH1F("Data_semiresolved","",newrec,new_rec);
    TH1F *TTbar_semiresolved = new TH1F("TTbar_semiresolved","",newrec,new_rec);
    TH1F *TTbar_others_semiresolved = new TH1F("TTbar_others_semiresolved","",newrec,new_rec);
    TH1F *WJets_semiresolved = new TH1F("WJets_semiresolved","",newrec,new_rec);
    TH1F *ST_semiresolved = new TH1F("ST_semiresolved","",newrec,new_rec);
    TH1F *DY_semiresolved = new TH1F("DY_semiresolved","",newrec,new_rec);
    TH1F *QCD_semiresolved = new TH1F("QCD_semiresolved","",newrec,new_rec);


//-------Syst----------??

    TH1F *ttbar_semi_boosted_pu_up = new TH1F("ttbar_semi_boosted_pu_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_pu_down  = new TH1F("ttbar_semi_boosted_pu_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_MuonID_up  = new TH1F("ttbar_semi_boosted_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_MuonID_down  = new TH1F("ttbar_semi_boosted_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_Trigger_up  = new TH1F("ttbar_semi_boosted_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_Trigger_down  = new TH1F("ttbar_semi_boosted_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_mistag_up  = new TH1F("ttbar_semi_boosted_mistag_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_mistag_down  = new TH1F("ttbar_semi_boosted_mistag_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_cferr1_up  = new TH1F("ttbar_semi_boosted_cferr1_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_cferr1_down  = new TH1F("ttbar_semi_boosted_cferr1_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_cferr2_up  = new TH1F("ttbar_semi_boosted_cferr2_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_cferr2_down  = new TH1F("ttbar_semi_boosted_cferr2_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_hf_up  = new TH1F("ttbar_semi_boosted_hf_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_hf_down  = new TH1F("ttbar_semi_boosted_hf_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_lf_up  = new TH1F("ttbar_semi_boosted_lf_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_lf_down  = new TH1F("ttbar_semi_boosted_lf_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_hfstats1_up  = new TH1F("ttbar_semi_boosted_hfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_hfstats1_down  = new TH1F("ttbar_semi_boosted_hfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_hfstats2_up  = new TH1F("ttbar_semi_boosted_hfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_hfstats2_down  = new TH1F("ttbar_semi_boosted_hfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_lfstats1_up  = new TH1F("ttbar_semi_boosted_lfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_lfstats1_down  = new TH1F("ttbar_semi_boosted_lfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_lfstats2_up  = new TH1F("ttbar_semi_boosted_lfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_lfstats2_down  = new TH1F("ttbar_semi_boosted_lfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_jes_up  = new TH1F("ttbar_semi_boosted_jes_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_jes_down  = new TH1F("ttbar_semi_boosted_jes_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_ptrew_up  = new TH1F("ttbar_semi_boosted_ptrew_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_ptrew_down  = new TH1F("ttbar_semi_boosted_ptrew_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_toptag_up  = new TH1F("ttbar_semi_boosted_toptag_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_toptag_down  = new TH1F("ttbar_semi_boosted_toptag_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_muonrec_up  = new TH1F("ttbar_semi_boosted_muonrec_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_muonrec_down  = new TH1F("ttbar_semi_boosted_muonrec_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_jec_up  = new TH1F("ttbar_semi_boosted_jec_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_jer_up  = new TH1F("ttbar_semi_boosted_jer_up","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_jec_down  = new TH1F("ttbar_semi_boosted_jec_down","",newrec,new_rec);
    TH1F *ttbar_semi_boosted_jer_down  = new TH1F("ttbar_semi_boosted_jer_down","",newrec,new_rec);

    TH1F *ttbar_semi_semiresolved_pu_up = new TH1F("ttbar_semi_semiresolved_pu_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_pu_down  = new TH1F("ttbar_semi_semiresolved_pu_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_MuonID_up  = new TH1F("ttbar_semi_semiresolved_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_MuonID_down  = new TH1F("ttbar_semi_semiresolved_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_Trigger_up  = new TH1F("ttbar_semi_semiresolved_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_Trigger_down  = new TH1F("ttbar_semi_semiresolved_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_mistag_up  = new TH1F("ttbar_semi_semiresolved_mistag_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_mistag_down  = new TH1F("ttbar_semi_semiresolved_mistag_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_cferr1_up  = new TH1F("ttbar_semi_semiresolved_cferr1_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_cferr1_down  = new TH1F("ttbar_semi_semiresolved_cferr1_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_cferr2_up  = new TH1F("ttbar_semi_semiresolved_cferr2_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_cferr2_down  = new TH1F("ttbar_semi_semiresolved_cferr2_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_hf_up  = new TH1F("ttbar_semi_semiresolved_hf_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_hf_down  = new TH1F("ttbar_semi_semiresolved_hf_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_lf_up  = new TH1F("ttbar_semi_semiresolved_lf_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_lf_down  = new TH1F("ttbar_semi_semiresolved_lf_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_hfstats1_up  = new TH1F("ttbar_semi_semiresolved_hfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_hfstats1_down  = new TH1F("ttbar_semi_semiresolved_hfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_hfstats2_up  = new TH1F("ttbar_semi_semiresolved_hfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_hfstats2_down  = new TH1F("ttbar_semi_semiresolved_hfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_lfstats1_up  = new TH1F("ttbar_semi_semiresolved_lfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_lfstats1_down  = new TH1F("ttbar_semi_semiresolved_lfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_lfstats2_up  = new TH1F("ttbar_semi_semiresolved_lfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_lfstats2_down  = new TH1F("ttbar_semi_semiresolved_lfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_jes_up  = new TH1F("ttbar_semi_semiresolved_jes_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_jes_down  = new TH1F("ttbar_semi_semiresolved_jes_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_ptrew_up  = new TH1F("ttbar_semi_semiresolved_ptrew_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_ptrew_down  = new TH1F("ttbar_semi_semiresolved_ptrew_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_toptag_up  = new TH1F("ttbar_semi_semiresolved_toptag_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_toptag_down  = new TH1F("ttbar_semi_semiresolved_toptag_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_muonrec_up  = new TH1F("ttbar_semi_semiresolved_muonrec_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_muonrec_down  = new TH1F("ttbar_semi_semiresolved_muonrec_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_jec_up  = new TH1F("ttbar_semi_semiresolved_jec_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_jer_up  = new TH1F("ttbar_semi_semiresolved_jer_up","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_jec_down  = new TH1F("ttbar_semi_semiresolved_jec_down","",newrec,new_rec);
    TH1F *ttbar_semi_semiresolved_jer_down  = new TH1F("ttbar_semi_semiresolved_jer_down","",newrec,new_rec);

    TH1F *ttbar_semi_resolved_pu_up = new TH1F("ttbar_semi_resolved_pu_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_pu_down  = new TH1F("ttbar_semi_resolved_pu_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_MuonID_up  = new TH1F("ttbar_semi_resolved_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_MuonID_down  = new TH1F("ttbar_semi_resolved_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_Trigger_up  = new TH1F("ttbar_semi_resolved_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_Trigger_down  = new TH1F("ttbar_semi_resolved_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_mistag_up  = new TH1F("ttbar_semi_resolved_mistag_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_mistag_down  = new TH1F("ttbar_semi_resolved_mistag_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_cferr1_up  = new TH1F("ttbar_semi_resolved_cferr1_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_cferr1_down  = new TH1F("ttbar_semi_resolved_cferr1_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_cferr2_up  = new TH1F("ttbar_semi_resolved_cferr2_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_cferr2_down  = new TH1F("ttbar_semi_resolved_cferr2_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_hf_up  = new TH1F("ttbar_semi_resolved_hf_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_hf_down  = new TH1F("ttbar_semi_resolved_hf_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_lf_up  = new TH1F("ttbar_semi_resolved_lf_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_lf_down  = new TH1F("ttbar_semi_resolved_lf_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_hfstats1_up  = new TH1F("ttbar_semi_resolved_hfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_hfstats1_down  = new TH1F("ttbar_semi_resolved_hfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_hfstats2_up  = new TH1F("ttbar_semi_resolved_hfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_hfstats2_down  = new TH1F("ttbar_semi_resolved_hfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_lfstats1_up  = new TH1F("ttbar_semi_resolved_lfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_lfstats1_down  = new TH1F("ttbar_semi_resolved_lfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_lfstats2_up  = new TH1F("ttbar_semi_resolved_lfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_lfstats2_down  = new TH1F("ttbar_semi_resolved_lfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_jes_up  = new TH1F("ttbar_semi_resolved_jes_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_jes_down  = new TH1F("ttbar_semi_resolved_jes_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_ptrew_up  = new TH1F("ttbar_semi_resolved_ptrew_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_ptrew_down  = new TH1F("ttbar_semi_resolved_ptrew_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_toptag_up  = new TH1F("ttbar_semi_resolved_toptag_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_toptag_down  = new TH1F("ttbar_semi_resolved_toptag_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_muonrec_up  = new TH1F("ttbar_semi_resolved_muonrec_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_muonrec_down  = new TH1F("ttbar_semi_resolved_muonrec_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_jec_up  = new TH1F("ttbar_semi_resolved_jec_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_jer_up  = new TH1F("ttbar_semi_resolved_jer_up","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_jec_down  = new TH1F("ttbar_semi_resolved_jec_down","",newrec,new_rec);
    TH1F *ttbar_semi_resolved_jer_down  = new TH1F("ttbar_semi_resolved_jer_down","",newrec,new_rec);

//--------Unfold----------??
    TH2F *Migration_Matrix_boosted = new TH2F("Migration_Matrix_boosted","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_semiresolved = new TH2F("Migration_Matrix_semiresolved","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_resolved = new TH2F("Migration_Matrix_resolved","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *PS_boosted = new TH2F("PS_boosted","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH2F *PS_semiresolved = new TH2F("PS_semiresolved","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH2F *PS_resolved = new TH2F("PS_resolved","",binnum_gen,bins_gen,binnum_gen,bins_gen);

    TH1F *Var_gen_boosted = new TH1F("Var_gen_boosted","",binnum_gen,bins_gen);
    TH1F *Var_gen_semiresolved = new TH1F("Var_gen_semiresolved","",binnum_gen,bins_gen);
    TH1F *Var_gen_resolved = new TH1F("Var_gen_resolved","",binnum_gen,bins_gen);

//---------selection_cuts && weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*s --------??


//    string Mttbar_semi_gen = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";


    Float_t mistag_boosted = 0.95;
    Float_t mistag_boosted_up = 1.;
    Float_t mistag_boosted_down = 1.05;

    Float_t mistag_semiresolved = 0.95;
    Float_t mistag_semiresolved_up = 1.;
    Float_t mistag_semiresolved_down = 1.05;

    Float_t mistag_resolved = 1.;
    Float_t mistag_resolved_up = 1.;
    Float_t mistag_resolved_down = 1.;       

    string selcuts_boosted_central = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_boosted);
    string selcuts_boosted_up = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_boosted_up);
    string selcuts_boosted_down = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_boosted_down);

    string selcuts_semiresolved_central = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)*%f",region.c_str(),mistag_semiresolved);
    string selcuts_semiresolved_up = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)*%f",region.c_str(),mistag_semiresolved_up);
    string selcuts_semiresolved_down = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)*%f",region.c_str(),mistag_semiresolved_down);

    string selcuts_resolved_central = Form("(ttagN == 0 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_resolved);
    string selcuts_resolved_up = Form("(ttagN == 0 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_resolved_up);
    string selcuts_resolved_down = Form("(ttagN == 0 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_resolved_down);

    string selcuts_data_boosted = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)",region.c_str());  
    string selcuts_data_semiresolved = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)",region.c_str());
    string selcuts_data_resolved = Form("(ttagN == 0 && btagN >= 1 && wtagN == 0 && %s)",region.c_str());

// "ttagN == 1 && btagN >= 1 && wtagN == 0 && rec_chi2 < 30" "ttagN == 0 && btagN == 1 && wtagN == 0 && rec_chi2 < 30" "ttagN == 0 && btagN >= 1 && wtagN == 1 && rec_chi2 < 30

//------Filling_bkgs---------??
    treereco_data->Project("Data_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s",selcuts_data_boosted.c_str()));
    treereco_ttbar_semi->Project("TTbar_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_others->Project("TTbar_others_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_wjets->Project("WJets_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ST->Project("ST_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_DY->Project("DY_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_QCD->Project("QCD_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));

    treereco_data->Project("Data_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s",selcuts_data_semiresolved.c_str()));
    treereco_ttbar_semi->Project("TTbar_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_others->Project("TTbar_others_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_wjets->Project("WJets_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ST->Project("ST_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_DY->Project("DY_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_QCD->Project("QCD_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));

    treereco_data->Project("Data_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s",selcuts_data_resolved.c_str()));
    treereco_ttbar_semi->Project("TTbar_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_others->Project("TTbar_others_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_wjets->Project("WJets_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ST->Project("ST_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_DY->Project("DY_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_QCD->Project("QCD_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));

// ------ filling_syst_1D_histograms----------??

//boosted
    treereco_ttbar_semi->Project("ttbar_semi_boosted_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str())); 
    treereco_ttbar_semi->Project("ttbar_semi_boosted_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_mistag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_mistag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_cferr1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr1up*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_cferr1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr1down*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_cferr2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr2up*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_cferr2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr2down*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_hf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_hfup*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_hf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfdown*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_lf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfup*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_lf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfdown*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_hfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats1up*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_hfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats1down*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_hfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats2up*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_hfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats2down*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_jes_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_jesup*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_jes_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_jesdown*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_lfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats1up*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_lfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats1down*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_lfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats2up*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_lfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats2down*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_ptrew_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_ptrew_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_ptrew_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_up_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_ptrew_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_toptag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_up_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_toptag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_muonrec_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_up",selcuts_boosted_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_boosted_muonrec_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_down",selcuts_boosted_down.c_str()));
 
/////jec and jer 
    treereco_ttbar_semi_semi_jec->Project("ttbar_semi_boosted_jec_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_semi_jer->Project("ttbar_semi_boosted_jer_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));

    treereco_ttbar_semi_semi_jec->Project("ttbar_semi_boosted_jec_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_semi_jer->Project("ttbar_semi_boosted_jer_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));

//semiresolved

    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_mistag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_mistag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_cferr1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr1up*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_cferr1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr1down*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_cferr2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr2up*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_cferr2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr2down*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_hf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_hfup*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_hf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfdown*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_lf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfup*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_lf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfdown*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_hfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats1up*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_hfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats1down*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_hfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats2up*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_hfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats2down*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_jes_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_jesup*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_jes_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_jesdown*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_lfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats1up*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_lfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats1down*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_lfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats2up*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_lfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats2down*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_ptrew_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_ptrew_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_ptrew_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_up_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_ptrew_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_toptag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_up_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_toptag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_muonrec_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_up",selcuts_semiresolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_semiresolved_muonrec_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_down",selcuts_semiresolved_down.c_str()));

/////jec and jer 

    treereco_ttbar_semi_semi_jec->Project("ttbar_semi_semiresolved_jec_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi_semi_jer->Project("ttbar_semi_semiresolved_jer_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));

    treereco_ttbar_semi_semi_jec->Project("ttbar_semi_semiresolved_jec_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi_semi_jer->Project("ttbar_semi_semiresolved_jer_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));

//resolved

    treereco_ttbar_semi->Project("ttbar_semi_resolved_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_mistag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_mistag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_cferr1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr1up*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_cferr1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr1down*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_cferr2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr2up*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_cferr2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_cferr2down*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_hf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_hfup*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_hf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfdown*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_lf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfup*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_lf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfdown*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_hfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats1up*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_hfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats1down*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_hfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats2up*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_hfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_hfstats2down*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_jes_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_jesup*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_jes_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_jesdown*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_lfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats1up*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_lfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats1down*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_lfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats2up*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_lfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_lfstats2down*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_ptrew_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_ptrew_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_down*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_ptrew_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_up_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_ptrew_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_toptag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_up_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_up.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_toptag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_muonrec_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_up",selcuts_resolved_down.c_str()));
    treereco_ttbar_semi->Project("ttbar_semi_resolved_muonrec_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_down_*weight_pt_rew*weight_btagdisc_central*muonrecSF_down",selcuts_resolved_down.c_str()));

    treereco_ttbar_semi_semi_jec->Project("ttbar_semi_resolved_jec_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi_semi_jer->Project("ttbar_semi_resolved_jer_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi_semi_jec->Project("ttbar_semi_resolved_jec_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi_semi_jer->Project("ttbar_semi_resolved_jer_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));

//-------Migration_Matrix_for_nominal_unfolding------??  

//boosted
    treereco_ttbar_semi->Project("Migration_Matrix_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Var_gen_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));

//semiresolved

    treereco_ttbar_semi->Project("Migration_Matrix_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));
    treereco_ttbar_semi->Project("Var_gen_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));

//resolved

    treereco_ttbar_semi->Project("Migration_Matrix_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));
    treereco_ttbar_semi->Project("Var_gen_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));


//-----------Juntando todo en los viejos histogramas --------- ?? 


    TH1F *Data = new TH1F("Data","",newrec,new_rec);
    TH1F *TTbar = new TH1F("TTbar","",newrec,new_rec);
    TH1F *TTbar_others = new TH1F("TTbar_others","",newrec,new_rec);
    TH1F *WJets = new TH1F("WJets","",newrec,new_rec);
    TH1F *ST = new TH1F("ST","",newrec,new_rec);
    TH1F *DY = new TH1F("DY","",newrec,new_rec);
    TH1F *QCD = new TH1F("QCD","",newrec,new_rec);

    TH1F *ttbar_semi_pu_up = new TH1F("ttbar_semi_pu_up","",newrec,new_rec);
    TH1F *ttbar_semi_pu_down  = new TH1F("ttbar_semi_pu_down","",newrec,new_rec);
    TH1F *ttbar_semi_MuonID_up  = new TH1F("ttbar_semi_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_semi_MuonID_down  = new TH1F("ttbar_semi_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_semi_Trigger_up  = new TH1F("ttbar_semi_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_semi_Trigger_down  = new TH1F("ttbar_semi_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_semi_mistag_up  = new TH1F("ttbar_semi_mistag_up","",newrec,new_rec);
    TH1F *ttbar_semi_mistag_down  = new TH1F("ttbar_semi_mistag_down","",newrec,new_rec);
    TH1F *ttbar_semi_cferr1_up  = new TH1F("ttbar_semi_cferr1_up","",newrec,new_rec);
    TH1F *ttbar_semi_cferr1_down  = new TH1F("ttbar_semi_cferr1_down","",newrec,new_rec);
    TH1F *ttbar_semi_cferr2_up  = new TH1F("ttbar_semi_cferr2_up","",newrec,new_rec);
    TH1F *ttbar_semi_cferr2_down  = new TH1F("ttbar_semi_cferr2_down","",newrec,new_rec);
    TH1F *ttbar_semi_hf_up  = new TH1F("ttbar_semi_hf_up","",newrec,new_rec);
    TH1F *ttbar_semi_hf_down  = new TH1F("ttbar_semi_hf_down","",newrec,new_rec);
    TH1F *ttbar_semi_lf_up  = new TH1F("ttbar_semi_lf_up","",newrec,new_rec);
    TH1F *ttbar_semi_lf_down  = new TH1F("ttbar_semi_lf_down","",newrec,new_rec);
    TH1F *ttbar_semi_hfstats1_up  = new TH1F("ttbar_semi_hfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_hfstats1_down  = new TH1F("ttbar_semi_hfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_hfstats2_up  = new TH1F("ttbar_semi_hfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_hfstats2_down  = new TH1F("ttbar_semi_hfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_lfstats1_up  = new TH1F("ttbar_semi_lfstats1_up","",newrec,new_rec);
    TH1F *ttbar_semi_lfstats1_down  = new TH1F("ttbar_semi_lfstats1_down","",newrec,new_rec);
    TH1F *ttbar_semi_lfstats2_up  = new TH1F("ttbar_semi_lfstats2_up","",newrec,new_rec);
    TH1F *ttbar_semi_lfstats2_down  = new TH1F("ttbar_semi_lfstats2_down","",newrec,new_rec);
    TH1F *ttbar_semi_jes_up  = new TH1F("ttbar_semi_jes_up","",newrec,new_rec);
    TH1F *ttbar_semi_jes_down  = new TH1F("ttbar_semi_jes_down","",newrec,new_rec);
    TH1F *ttbar_semi_ptrew_up  = new TH1F("ttbar_semi_ptrew_up","",newrec,new_rec);
    TH1F *ttbar_semi_ptrew_down  = new TH1F("ttbar_semi_ptrew_down","",newrec,new_rec);
    TH1F *ttbar_semi_toptag_up  = new TH1F("ttbar_semi_toptag_up","",newrec,new_rec);
    TH1F *ttbar_semi_toptag_down  = new TH1F("ttbar_semi_toptag_down","",newrec,new_rec);
    TH1F *ttbar_semi_muonrec_up  = new TH1F("ttbar_semi_muonrec_up","",newrec,new_rec);
    TH1F *ttbar_semi_muonrec_down  = new TH1F("ttbar_semi_muonrec_down","",newrec,new_rec);
    TH1F *ttbar_semi_jecUp  = new TH1F("ttbar_semi_jecUp","",newrec,new_rec);
    TH1F *ttbar_semi_jerUp  = new TH1F("ttbar_semi_jerUp","",newrec,new_rec);
    TH1F *ttbar_semi_jecDown  = new TH1F("ttbar_semi_jecDown","",newrec,new_rec);
    TH1F *ttbar_semi_jerDown  = new TH1F("ttbar_semi_jerDown","",newrec,new_rec);

    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *PS = new TH2F("PS","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH1F *Var_gen = new TH1F("Var_gen","",binnum_gen,bins_gen);

    Data->Sumw2();
    Data->Add(Data_boosted);
    Data->Add(Data_semiresolved);
    Data->Add(Data_resolved);

    TTbar->Sumw2();
    TTbar->Add(TTbar_boosted);
    TTbar->Add(TTbar_semiresolved);
    TTbar->Add(TTbar_resolved);
  
    TTbar_others->Sumw2();
    TTbar_others->Add(TTbar_others_boosted);
    TTbar_others->Add(TTbar_others_semiresolved);
    TTbar_others->Add(TTbar_others_resolved);

    WJets->Sumw2(); 
    WJets->Add(WJets_boosted);
    WJets->Add(WJets_semiresolved);
    WJets->Add(WJets_resolved);

    ST->Sumw2(); 
    ST->Add(ST_boosted);
    ST->Add(ST_semiresolved);
    ST->Add(ST_resolved);

    DY->Sumw2();
    DY->Add(DY_boosted);
    DY->Add(DY_semiresolved);
    DY->Add(DY_resolved);

    QCD->Sumw2(); 
    QCD->Add(QCD_boosted);
    QCD->Add(QCD_semiresolved);
    QCD->Add(QCD_resolved);    
 
    ttbar_semi_pu_up->Sumw2();
    ttbar_semi_pu_down->Sumw2();
    ttbar_semi_MuonID_up->Sumw2();
    ttbar_semi_MuonID_down->Sumw2();
    ttbar_semi_Trigger_up->Sumw2();
    ttbar_semi_Trigger_down->Sumw2();
    ttbar_semi_mistag_up->Sumw2();
    ttbar_semi_mistag_down->Sumw2();
    ttbar_semi_cferr1_up->Sumw2();
    ttbar_semi_cferr1_down->Sumw2();
    ttbar_semi_cferr2_up->Sumw2();
    ttbar_semi_cferr2_down->Sumw2();
    ttbar_semi_hf_up->Sumw2();
    ttbar_semi_hf_down->Sumw2();
    ttbar_semi_lf_up->Sumw2();
    ttbar_semi_lf_down->Sumw2();
    ttbar_semi_hfstats1_up->Sumw2();
    ttbar_semi_hfstats1_down->Sumw2();
    ttbar_semi_hfstats2_up->Sumw2();
    ttbar_semi_hfstats2_down->Sumw2();
    ttbar_semi_lfstats1_up->Sumw2();
    ttbar_semi_lfstats1_down->Sumw2();
    ttbar_semi_lfstats2_up->Sumw2();
    ttbar_semi_lfstats2_down->Sumw2();
    ttbar_semi_jes_up->Sumw2();
    ttbar_semi_jes_down->Sumw2();
    ttbar_semi_ptrew_up->Sumw2();
    ttbar_semi_ptrew_down->Sumw2();
    ttbar_semi_toptag_up->Sumw2();
    ttbar_semi_toptag_down->Sumw2();
    ttbar_semi_muonrec_up->Sumw2();
    ttbar_semi_muonrec_down->Sumw2();
    ttbar_semi_jecUp->Sumw2();
    ttbar_semi_jerUp->Sumw2();
    ttbar_semi_jecDown->Sumw2();
    ttbar_semi_jerDown->Sumw2();

    ttbar_semi_pu_up->Add(ttbar_semi_boosted_pu_up);
    ttbar_semi_pu_down->Add(ttbar_semi_boosted_pu_down);
    ttbar_semi_MuonID_up->Add(ttbar_semi_boosted_MuonID_up);
    ttbar_semi_MuonID_down->Add(ttbar_semi_boosted_MuonID_down);
    ttbar_semi_Trigger_up->Add(ttbar_semi_boosted_Trigger_up);
    ttbar_semi_Trigger_down->Add(ttbar_semi_boosted_Trigger_down);
    ttbar_semi_mistag_up->Add(ttbar_semi_boosted_mistag_up);
    ttbar_semi_mistag_down->Add(ttbar_semi_boosted_mistag_down);
    ttbar_semi_cferr1_up->Add(ttbar_semi_boosted_cferr1_up);
    ttbar_semi_cferr1_down->Add(ttbar_semi_boosted_cferr1_down);
    ttbar_semi_cferr2_up->Add(ttbar_semi_boosted_cferr2_up);
    ttbar_semi_cferr2_down->Add(ttbar_semi_boosted_cferr2_down);
    ttbar_semi_hf_up->Add(ttbar_semi_boosted_hf_up);
    ttbar_semi_hf_down->Add(ttbar_semi_boosted_hf_down);
    ttbar_semi_lf_up->Add(ttbar_semi_boosted_lf_up);
    ttbar_semi_lf_down->Add(ttbar_semi_boosted_lf_down);
    ttbar_semi_hfstats1_up->Add(ttbar_semi_boosted_hfstats1_up);
    ttbar_semi_hfstats1_down->Add(ttbar_semi_boosted_hfstats1_down);
    ttbar_semi_hfstats2_up->Add(ttbar_semi_boosted_hfstats2_up);
    ttbar_semi_hfstats2_down->Add(ttbar_semi_boosted_hfstats2_down);
    ttbar_semi_lfstats1_up->Add(ttbar_semi_boosted_lfstats1_up);
    ttbar_semi_lfstats1_down->Add(ttbar_semi_boosted_lfstats1_down);
    ttbar_semi_lfstats2_up->Add(ttbar_semi_boosted_lfstats2_up);
    ttbar_semi_lfstats2_down->Add(ttbar_semi_boosted_lfstats2_down);
    ttbar_semi_jes_up->Add(ttbar_semi_boosted_jes_up);
    ttbar_semi_jes_down->Add(ttbar_semi_boosted_jes_down);
    ttbar_semi_ptrew_up->Add(ttbar_semi_boosted_ptrew_up);
    ttbar_semi_ptrew_down->Add(ttbar_semi_boosted_ptrew_down);
    ttbar_semi_toptag_up->Add(ttbar_semi_boosted_toptag_up);
    ttbar_semi_toptag_down->Add(ttbar_semi_boosted_toptag_down);
    ttbar_semi_muonrec_up->Add(ttbar_semi_boosted_muonrec_up);
    ttbar_semi_muonrec_down->Add(ttbar_semi_boosted_muonrec_down);
    ttbar_semi_jecUp->Add(ttbar_semi_boosted_jec_up);
    ttbar_semi_jerUp->Add(ttbar_semi_boosted_jer_up);
    ttbar_semi_jecDown->Add(ttbar_semi_boosted_jec_down);
    ttbar_semi_jerDown->Add(ttbar_semi_boosted_jer_down);


    ttbar_semi_pu_up->Add(ttbar_semi_semiresolved_pu_up);
    ttbar_semi_pu_down->Add(ttbar_semi_semiresolved_pu_down);
    ttbar_semi_MuonID_up->Add(ttbar_semi_semiresolved_MuonID_up);
    ttbar_semi_MuonID_down->Add(ttbar_semi_semiresolved_MuonID_down);
    ttbar_semi_Trigger_up->Add(ttbar_semi_semiresolved_Trigger_up);
    ttbar_semi_Trigger_down->Add(ttbar_semi_semiresolved_Trigger_down);
    ttbar_semi_mistag_up->Add(ttbar_semi_semiresolved_mistag_up);
    ttbar_semi_mistag_down->Add(ttbar_semi_semiresolved_mistag_down);
    ttbar_semi_cferr1_up->Add(ttbar_semi_semiresolved_cferr1_up);
    ttbar_semi_cferr1_down->Add(ttbar_semi_semiresolved_cferr1_down);
    ttbar_semi_cferr2_up->Add(ttbar_semi_semiresolved_cferr2_up);
    ttbar_semi_cferr2_down->Add(ttbar_semi_semiresolved_cferr2_down);
    ttbar_semi_hf_up->Add(ttbar_semi_semiresolved_hf_up);
    ttbar_semi_hf_down->Add(ttbar_semi_semiresolved_hf_down);
    ttbar_semi_lf_up->Add(ttbar_semi_semiresolved_lf_up);
    ttbar_semi_lf_down->Add(ttbar_semi_semiresolved_lf_down);
    ttbar_semi_hfstats1_up->Add(ttbar_semi_semiresolved_hfstats1_up);
    ttbar_semi_hfstats1_down->Add(ttbar_semi_semiresolved_hfstats1_down);
    ttbar_semi_hfstats2_up->Add(ttbar_semi_semiresolved_hfstats2_up);
    ttbar_semi_hfstats2_down->Add(ttbar_semi_semiresolved_hfstats2_down);
    ttbar_semi_lfstats1_up->Add(ttbar_semi_semiresolved_lfstats1_up);
    ttbar_semi_lfstats1_down->Add(ttbar_semi_semiresolved_lfstats1_down);
    ttbar_semi_lfstats2_up->Add(ttbar_semi_semiresolved_lfstats2_up);
    ttbar_semi_lfstats2_down->Add(ttbar_semi_semiresolved_lfstats2_down);
    ttbar_semi_jes_up->Add(ttbar_semi_semiresolved_jes_up);
    ttbar_semi_jes_down->Add(ttbar_semi_semiresolved_jes_down);
    ttbar_semi_ptrew_up->Add(ttbar_semi_semiresolved_ptrew_up);
    ttbar_semi_ptrew_down->Add(ttbar_semi_semiresolved_ptrew_down);
    ttbar_semi_toptag_up->Add(ttbar_semi_semiresolved_toptag_up);
    ttbar_semi_toptag_down->Add(ttbar_semi_semiresolved_toptag_down);
    ttbar_semi_muonrec_up->Add(ttbar_semi_semiresolved_muonrec_up);
    ttbar_semi_muonrec_down->Add(ttbar_semi_semiresolved_muonrec_down);
    ttbar_semi_jecUp->Add(ttbar_semi_semiresolved_jec_up);
    ttbar_semi_jerUp->Add(ttbar_semi_semiresolved_jer_up);
    ttbar_semi_jecDown->Add(ttbar_semi_semiresolved_jec_down);
    ttbar_semi_jerDown->Add(ttbar_semi_semiresolved_jer_down);

    ttbar_semi_pu_up->Add(ttbar_semi_resolved_pu_up);
    ttbar_semi_pu_down->Add(ttbar_semi_resolved_pu_down);
    ttbar_semi_MuonID_up->Add(ttbar_semi_resolved_MuonID_up);
    ttbar_semi_MuonID_down->Add(ttbar_semi_resolved_MuonID_down);
    ttbar_semi_Trigger_up->Add(ttbar_semi_resolved_Trigger_up);
    ttbar_semi_Trigger_down->Add(ttbar_semi_resolved_Trigger_down);
    ttbar_semi_mistag_up->Add(ttbar_semi_resolved_mistag_up);
    ttbar_semi_mistag_down->Add(ttbar_semi_resolved_mistag_down);
    ttbar_semi_cferr1_up->Add(ttbar_semi_resolved_cferr1_up);
    ttbar_semi_cferr1_down->Add(ttbar_semi_resolved_cferr1_down);
    ttbar_semi_cferr2_up->Add(ttbar_semi_resolved_cferr2_up);
    ttbar_semi_cferr2_down->Add(ttbar_semi_resolved_cferr2_down);
    ttbar_semi_hf_up->Add(ttbar_semi_resolved_hf_up);
    ttbar_semi_hf_down->Add(ttbar_semi_resolved_hf_down);
    ttbar_semi_lf_up->Add(ttbar_semi_resolved_lf_up);
    ttbar_semi_lf_down->Add(ttbar_semi_resolved_lf_down);
    ttbar_semi_hfstats1_up->Add(ttbar_semi_resolved_hfstats1_up);
    ttbar_semi_hfstats1_down->Add(ttbar_semi_resolved_hfstats1_down);
    ttbar_semi_hfstats2_up->Add(ttbar_semi_resolved_hfstats2_up);
    ttbar_semi_hfstats2_down->Add(ttbar_semi_resolved_hfstats2_down);
    ttbar_semi_lfstats1_up->Add(ttbar_semi_resolved_lfstats1_up);
    ttbar_semi_lfstats1_down->Add(ttbar_semi_resolved_lfstats1_down);
    ttbar_semi_lfstats2_up->Add(ttbar_semi_resolved_lfstats2_up);
    ttbar_semi_lfstats2_down->Add(ttbar_semi_resolved_lfstats2_down);
    ttbar_semi_jes_up->Add(ttbar_semi_resolved_jes_up);
    ttbar_semi_jes_down->Add(ttbar_semi_resolved_jes_down);
    ttbar_semi_ptrew_up->Add(ttbar_semi_resolved_ptrew_up);
    ttbar_semi_ptrew_down->Add(ttbar_semi_resolved_ptrew_down);
    ttbar_semi_toptag_up->Add(ttbar_semi_resolved_toptag_up);
    ttbar_semi_toptag_down->Add(ttbar_semi_resolved_toptag_down);
    ttbar_semi_muonrec_up->Add(ttbar_semi_resolved_muonrec_up);
    ttbar_semi_muonrec_down->Add(ttbar_semi_resolved_muonrec_down);
    ttbar_semi_jecUp->Add(ttbar_semi_resolved_jec_up);
    ttbar_semi_jerUp->Add(ttbar_semi_resolved_jer_up);
    ttbar_semi_jecDown->Add(ttbar_semi_resolved_jec_down);
    ttbar_semi_jerDown->Add(ttbar_semi_resolved_jer_down);

    Migration_Matrix->Sumw2();
    Migration_Matrix->Add(Migration_Matrix_boosted);
    Migration_Matrix->Add(Migration_Matrix_semiresolved);
    Migration_Matrix->Add(Migration_Matrix_resolved);

    Var_gen->Sumw2();
    Var_gen->Add(Var_gen_boosted);
    Var_gen->Add(Var_gen_semiresolved);
    Var_gen->Add(Var_gen_resolved);

//-------Migration_matrxi_for_P&S--------------------    
    treereco_ttbar_semi->Project("PS_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_boosted_central.c_str()));    

    treereco_ttbar_semi->Project("PS_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_semiresolved_central.c_str()));

    treereco_ttbar_semi->Project("PS_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal",selcuts_resolved_central.c_str()));

    PS->Sumw2();
    PS->Add(PS_boosted);
    PS->Add(PS_semiresolved);
    PS->Add(PS_resolved);


//--------Para simetrizar, quitar para unblinding 
 
    for(int s=1;s<=newrec/2;s++){

       Data->SetBinContent(s,Data->GetBinContent(newrec+1-s));
       TTbar->SetBinContent(s,TTbar->GetBinContent(newrec+1-s));
       TTbar_others->SetBinContent(s,TTbar_others->GetBinContent(newrec+1-s));
       WJets->SetBinContent(s,WJets->GetBinContent(newrec+1-s));
       ST->SetBinContent(s,ST->GetBinContent(newrec+1-s));
       DY->SetBinContent(s,DY->GetBinContent(newrec+1-s));
       QCD->SetBinContent(s,QCD->GetBinContent(newrec+1-s));

    }  


//----------Making_input_root_file_for_unfolding-----------?

    TFile out("Input_undfolding_data_.root","recreate");
    Data->Write();
    TTbar->Write();
    TTbar_others->Write();
    WJets->Write(); 
    ST->Write(); 
    DY->Write();
    QCD->Write();
    Migration_Matrix->Write();    
    Var_gen->Write();
/*
    ttbar_semi_pu_down->Write();
    ttbar_semi_pu_up->Write();
    ttbar_semi_MuonID_up->Write();
    ttbar_semi_MuonID_down->Write();
    ttbar_semi_Trigger_up->Write();
    ttbar_semi_Trigger_down->Write();
    ttbar_semi_mistag_up->Write();
    ttbar_semi_mistag_down->Write();
    ttbar_semi_cferr1_up->Write();
    ttbar_semi_cferr1_down->Write();
    ttbar_semi_cferr2_up->Write();
    ttbar_semi_cferr2_down->Write();
    ttbar_semi_hf_up->Write();
    ttbar_semi_hf_down->Write();
    ttbar_semi_lf_up->Write();
    ttbar_semi_lf_down->Write();
    ttbar_semi_hfstats1_up->Write();
    ttbar_semi_hfstats1_down->Write();
    ttbar_semi_hfstats2_up->Write();
    ttbar_semi_hfstats2_down->Write();
    ttbar_semi_lfstats1_up->Write();
    ttbar_semi_lfstats1_down->Write();
    ttbar_semi_lfstats2_up->Write();
    ttbar_semi_lfstats2_down->Write();
    ttbar_semi_jes_up->Write();
    ttbar_semi_jes_down->Write();
    ttbar_semi_ptrew_up->Write();
    ttbar_semi_ptrew_down->Write();
    ttbar_semi_toptag_up->Write();
    ttbar_semi_toptag_down->Write();
    ttbar_semi_muonrec_up->Write();
    ttbar_semi_muonrec_down->Write();
*/
    ttbar_semi_jecUp->Write();
    ttbar_semi_jerUp->Write();
    ttbar_semi_jecDown->Write();
    ttbar_semi_jerDown->Write();

   auto c1    = new TCanvas("c1","c1",600,400);
   c1->cd();
   Migration_Matrix->GetYaxis()->SetTitle("#Delta #cbar y_{gen} #cbar");   
   Migration_Matrix->GetXaxis()->SetTitle("#Delta #cbar y_{rec} #cbar");
   Migration_Matrix->Draw("COLZ");

   TLatex latex;
   latex.SetTextSize(0.045);
   latex.SetTextAlign(11);  //align at top
   latex.DrawLatex(-1.9,2.05,"CMS preliminary");

   TLatex latex2;
   latex2.SetTextSize(0.045);
   latex2.SetTextAlign(11);  //align at top
   latex2.DrawLatex(0.9,2.05,"58.8 fb^{-1} (13 TeV)");

   c1->Print("Migration_Matrix.ps");


    TH2F *Stability_Matrix = new TH2F("Stability_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);

   for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
            Stability_Matrix->SetBinContent(a,b,PS->GetBinContent(a,b)/PS->Integral(1,binnum_gen,b,b));
            Purity_Matrix->SetBinContent(a,b,PS->GetBinContent(a,b)/PS->Integral(a,a,1,binnum_gen));
       }
   }


// Purity && Stability

   TH1F *Stability = new TH1F("Stability","",binnum_gen,bins_gen);
   TH1F *Purity = new TH1F("Purity","",binnum_gen,bins_gen);
 
   for(Int_t m=1;m<=binnum_gen;m++){
       Stability->SetBinContent(m,Stability_Matrix->GetBinContent(m,m));
       Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
   }

   Stability->GetYaxis()->SetRangeUser(0,1);
   Stability->GetYaxis()->SetTitle("P&S");
   Stability->GetXaxis()->SetTitle("#Delta #cbar y_{rec} #cbar");
   Purity->SetLineColor(kRed);
   Purity->SetLineWidth(2);
   Stability->SetLineColor(kBlue);
   Stability->SetLineWidth(2);   

   TCanvas* cc = new TCanvas("cc","",2400,1200);
   cc->Divide(1,1);
   cc->cd(1);
   Stability->Draw("same");
   Purity->Draw("same");

   Float_t a = Stability->GetMaximum();

   TLegend leg(.65, .65, .85, .85, "");
   leg.SetFillColor(0);
   leg.AddEntry(Purity, "Purity");
   leg.AddEntry(Stability, "Stability");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   TLatex latex3;
   latex3.SetTextSize(0.045);
   latex3.SetTextAlign(11);
   latex3.DrawLatex(-1.9,1.04,"Work in progress");

   TLatex latex4;
   latex4.SetTextSize(0.045);
   latex4.SetTextAlign(11);
   latex4.DrawLatex(1.1,1.04,"58.8 fb^{-1} (13 TeV)");

   cc->Print("PS.pdf");

}
