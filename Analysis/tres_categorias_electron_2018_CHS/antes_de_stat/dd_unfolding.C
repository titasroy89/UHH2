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

void dd_unfolding(string var_name = "", string var_gen = "", string region = "", string year = "", Int_t gen_up = 0.0, Int_t gen_down = 0.0, Int_t rec_up = 0.0, Int_t rec_down = 0.0)
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);
    TChain *chreco_data = new TChain("AnalysisTree","");
    chreco_data->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s/muon/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2018.root/AnalysisTree",year.c_str()));
    TTree *treereco_data = (TTree*) chreco_data;

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TChain *chreco_wjets = new TChain("AnalysisTree","");
    chreco_wjets->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s/muon/uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2018.root/AnalysisTree",year.c_str()));
    TTree *treereco_wjets = (TTree*) chreco_wjets;

    TChain *chreco_ST = new TChain("AnalysisTree","");
    chreco_ST->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s/muon/uhh2.AnalysisModuleRunner.MC.ST_2018.root/AnalysisTree",year.c_str()));
    TTree *treereco_ST = (TTree*) chreco_ST;

    TChain *chreco_DY = new TChain("AnalysisTree","");
    chreco_DY->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s/muon/uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2018.root/AnalysisTree",year.c_str()));
    TTree *treereco_DY = (TTree*) chreco_DY;

    TChain *chreco_QCD = new TChain("AnalysisTree","");
    chreco_QCD->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s/muon/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018.root/AnalysisTree",year.c_str()));
    TTree *treereco_QCD = (TTree*) chreco_QCD;

//array for variable 

    int len = 0; int len_rec = 0;
    if(var_name == "DeltaY") len = 5, len_rec = 7;
    if(var_name == "Mttbar") len = 8, len_rec = 13;   
    if(var_name == "Rapidity_ttbar") len = 13, len_rec = 23;
    if(var_name == "tlead_pT") len = 6, len_rec = 9;
    if(var_name == "pT_ttbar") len = 6, len_rec = 9;

    Float_t bins_gen[len];
    Float_t new_rec[len_rec];

    if(var_name == "pT_ttbar"){
        Float_t Bins_gen[] = {0,200,400,600,800,1200};
        Float_t New_rec[] = {0,200,300,400,500,600,700,800,1200};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);

    }

    if(var_name == "DeltaY"){ 
        Float_t Bins_gen[] = {-2.,-1.,0.,1.,2.};
        Float_t New_rec[] = {-2.,-1.,-0.5,0.,0.5,1.,2.};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);

    }
    if(var_name == "Mttbar"){
        Float_t Bins_gen[] = {880,1050,1300,1500,1800,2200,2600,4000};
        Float_t New_rec[] = {880,1050,1175,1300,1400,1500,1650,1800,2000,2200,2400,2600,4000};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);
    }

    if(var_name == "Rapidity_ttbar"){
        Float_t Bins_gen[] = {-2.4,-2.,-1.6,-1.2,-0.8,-0.4,0.0,0.4,0.8,1.2,1.6,2,2.4};
        Float_t New_rec[] = {-2.4,-2.,-1.8,-1.6,-1.4,-1.2,-1.,-0.8,-0.6,-0.4,-0.2,0,0.2,0.4,0.6,0.8,1.,1.2,1.4,1.6,1.8,2,2.4};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);
    }

    if(var_name == "tlead_pT"){
        Float_t Bins_gen[] = {0,200,400,600,800,1200};
        Float_t New_rec[] = {0,200,300,400,500,600,700,800,1200};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);
    }

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//-----Bacgrounds------??
    TH1F *Data = new TH1F("Data","",newrec,new_rec);
    TH1F *TTbar = new TH1F("TTbar","",newrec,new_rec);
    TH1F *WJets = new TH1F("WJets","",newrec,new_rec);
    TH1F *ST = new TH1F("ST","",newrec,new_rec);
    TH1F *DY = new TH1F("DY","",newrec,new_rec);
    TH1F *QCD = new TH1F("QCD","",newrec,new_rec);

//-------Syst----------??

    TH1F *ttbar_pu_up = new TH1F("ttbar_pu_up","",newrec,new_rec);
    TH1F *ttbar_pu_down  = new TH1F("ttbar_pu_down","",newrec,new_rec);
    TH1F *ttbar_cferr1_up = new TH1F("ttbar_cferr1_up","",newrec,new_rec);
    TH1F *ttbar_cferr1_down = new TH1F("ttbar_cferr1_down","",newrec,new_rec);
    TH1F *ttbar_cferr2_up = new TH1F("ttbar_cferr2_up","",newrec,new_rec);
    TH1F *ttbar_cferr2_down  = new TH1F("ttbar_cferr2_down","",newrec,new_rec);
    TH1F *ttbar_hf_up = new TH1F("ttbar_hf_up","",newrec,new_rec);
    TH1F *ttbar_hf_down  = new TH1F("ttbar_hf_down","",newrec,new_rec);
    TH1F *ttbar_hfstats1_up = new TH1F("ttbar_hfstats1_up","",newrec,new_rec);
    TH1F *ttbar_hfstats1_down  = new TH1F("ttbar_hfstats1_down","",newrec,new_rec);
    TH1F *ttbar_hfstats2_up = new TH1F("ttbar_hfstats2_up","",newrec,new_rec);
    TH1F *ttbar_hfstats2_down  = new TH1F("ttbar_hfstats2_down","",newrec,new_rec);
    TH1F *ttbar_jes_up = new TH1F("ttbar_jes_up","",newrec,new_rec);
    TH1F *ttbar_jes_down  = new TH1F("ttbar_jes_down","",newrec,new_rec);
    TH1F *ttbar_lf_up = new TH1F("ttbar_lf_up","",newrec,new_rec);
    TH1F *ttbar_lf_down  = new TH1F("ttbar_lf_down","",newrec,new_rec);
    TH1F *ttbar_lfstats1_up = new TH1F("ttbar_lfstats1_up","",newrec,new_rec);
    TH1F *ttbar_lfstats1_down  = new TH1F("ttbar_lfstats1_down","",newrec,new_rec);
    TH1F *ttbar_lfstats2_up = new TH1F("ttbar_lfstats2_up","",newrec,new_rec);
    TH1F *ttbar_lfstats2_down  = new TH1F("ttbar_lfstats2_down","",newrec,new_rec);
    TH1F *ttbar_MuonID_up  = new TH1F("ttbar_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_MuonID_down  = new TH1F("ttbar_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_Trigger_up  = new TH1F("ttbar_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_Trigger_down  = new TH1F("ttbar_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_mistoptag_up  = new TH1F("ttbar_mistoptag_up","",newrec,new_rec);
    TH1F *ttbar_mistoptag_down  = new TH1F("ttbar_mistoptag_down","",newrec,new_rec);


//--------Unfold----------??
    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","",newrec,new_rec,binnum_gen,bins_gen);
    TH1F *Var_gen = new TH1F("Var_gen","",binnum_gen,bins_gen);
    TH2F *PS = new TH2F("PS","",binnum_gen,bins_gen,binnum_gen,bins_gen);

//---------selection_cuts && weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*s --------??


    string Mttbar_gen = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";

    float_t mistoptag = 1.;
    float_t mistoptag_up = 1.;
    float_t mistoptag_down = 1.;

    if (region == "ttagN == 1 && btagN >= 1 && wtagN == 0 && rec_chi2 < 30"){
        mistoptag = 0.82;
        mistoptag_up = 0.87;
        mistoptag_down = 0.77;
    }

    cout << mistoptag << endl;

    Float_t dd[] = {0,1000,10000};
    Float_t dd_gen[] = {0,1000,10000};

    Int_t  num_dd = sizeof(dd)/sizeof(Float_t) - 1;
    

      string selcuts_data = Form("(%s && Mttbar < %f && Mttbar > %f)",region.c_str(),dd[rec_up], dd[rec_down]);
      string selcuts_central = Form("(%s && Mttbar < %f && Mttbar > %f && %s < %f && %s > %f)*%f",region.c_str(),dd[rec_up], dd[rec_down], Mttbar_gen.c_str(),dd[gen_up],Mttbar_gen.c_str(),dd[gen_down],mistoptag); 
      string selcuts_up = Form("(%s && Mttbar < %f && Mttbar > %f && %s < %f && %s > %f)*%f",region.c_str(),dd[rec_up], dd[rec_down], Mttbar_gen.c_str(),dd[gen_up],Mttbar_gen.c_str(),dd[gen_down],mistoptag_up);
      string selcuts_down = Form("(%s && Mttbar < %f && Mttbar > %f && %s < %f && %s > %f)*%f",region.c_str(),dd[rec_up], dd[rec_down], Mttbar_gen.c_str(),dd[gen_up],Mttbar_gen.c_str(),dd[gen_down],mistoptag_down);

//    string selcuts_data = Form("(ttagN == 0 && btagN == 1 && Mttbar < %f && Mttbar > %f)",dd[rec_up], dd[rec_down]);
//    string selcuts = Form("(ttagN == 0 && btagN == 1 && Mttbar < %f && Mttbar > %f && %s < %f && %s > %f)",dd[rec_up], dd[rec_down], Mttbar_gen.c_str(),dd[gen_up],Mttbar_gen.c_str(),dd[gen_down]);

    cout << selcuts_central.c_str() << endl;

//------Filling_bkgs---------??
    treereco_data->Project("Data",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s",selcuts_data.c_str()));
    treereco_ttbar->Project("TTbar",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    treereco_wjets->Project("WJets",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    treereco_ST->Project("ST",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    treereco_DY->Project("DY",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    treereco_QCD->Project("QCD",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));

// ------ filling_syst_1D_histograms----------??

    treereco_ttbar->Project("ttbar_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down",selcuts_central.c_str()));
/*    treereco_ttbar->Project("ttbar_cferr1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_cferr1up",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_cferr1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_cferr1down",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_cferr2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_cferr2up",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_cferr2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_cferr2down",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_hf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_hfup",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_hf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_hfdown",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_hfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_hfstats1up",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_hfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_hfstats1down",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_hfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_hfstats2up",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_hfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_hfstats2down",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_jes_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_jesup",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_jes_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_jesdown",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_lf_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_lfup",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_lf_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_lfdown",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_lfstats1_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_lfstats1up",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_lfstats1_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_lfstats1down",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_lfstats2_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_lfstats2up",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_lfstats2_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_lfstats2down",selcuts_central.c_str()));
*/
    treereco_ttbar->Project("ttbar_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str())); 
    treereco_ttbar->Project("ttbar_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_central.c_str()));
    treereco_ttbar->Project("ttbar_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_central.c_str()));
  
    treereco_ttbar->Project("ttbar_mistoptag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_up.c_str()));
    treereco_ttbar->Project("ttbar_mistoptag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_down.c_str()));


//-------Migration_Matrix_for_nominal_unfolding------??  
    treereco_ttbar->Project("Migration_Matrix",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    treereco_ttbar->Project("Var_gen",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));
    
//-------Migration_matrxi_for_P&S--------------------    
    treereco_ttbar->Project("PS",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_central.c_str()));

//----------Making_input_root_file_for_unfolding-----------?

    TFile out(Form("Input_undfolding_data_%d_%d.root",gen_up,rec_up),"recreate");
    Data->Write();
    TTbar->Write();
    WJets->Write(); 
    ST->Write(); 
    DY->Write();
    QCD->Write();
    Migration_Matrix->Write();    
    Var_gen->Write();

    ttbar_pu_down->Write();
    ttbar_pu_up->Write();
/*    ttbar_cferr1_up->Write();
    ttbar_cferr1_down->Write();
    ttbar_cferr2_up->Write();
    ttbar_cferr2_down->Write();
    ttbar_hf_up->Write();
    ttbar_hf_down->Write();
    ttbar_hfstats1_down->Write();
    ttbar_hfstats1_up->Write();
    ttbar_hfstats2_up->Write();
    ttbar_hfstats2_down->Write();
    ttbar_jes_up->Write();
    ttbar_jes_down->Write();
    ttbar_lf_up->Write();
    ttbar_lf_down->Write();
    ttbar_lfstats1_up->Write();
    ttbar_lfstats1_down->Write();
    ttbar_lfstats2_up->Write();
    ttbar_lfstats2_down->Write();
*/
    ttbar_MuonID_up->Write();
    ttbar_MuonID_down->Write();
    ttbar_Trigger_up->Write();
    ttbar_Trigger_down->Write();
    ttbar_mistoptag_up->Write();
    ttbar_mistoptag_down->Write();

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

// Purity && Stability

    TH2F *Stability_Matrix = new TH2F("Stability_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);

   for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
            Stability_Matrix->SetBinContent(a,b,PS->GetBinContent(a,b)/PS->Integral(1,binnum_gen,b,b));
            Purity_Matrix->SetBinContent(a,b,PS->GetBinContent(a,b)/PS->Integral(a,a,1,binnum_gen));
       }
   }


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

   TLegend leg(.65, .65, .85, .85, "");
   leg.SetFillColor(0);
   leg.AddEntry(Purity, "Purity");
   leg.AddEntry(Stability, "Stability");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   cc->Print("PS.pdf");

}

