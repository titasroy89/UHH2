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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "")
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);
    TChain *chreco_data = new TChain("AnalysisTree","");
    chreco_data->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2017*.root/AnalysisTree");
    TTree *treereco_data = (TTree*) chreco_data;

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTTo*.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TChain *chreco_wjets = new TChain("AnalysisTree","");
    chreco_wjets->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2017*.root/AnalysisTree");
    TTree *treereco_wjets = (TTree*) chreco_wjets;

    TChain *chreco_ST = new TChain("AnalysisTree","");
    chreco_ST->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/uhh2.AnalysisModuleRunner.MC.ST_2017*.root/AnalysisTree");
    TTree *treereco_ST = (TTree*) chreco_ST;

    TChain *chreco_DY = new TChain("AnalysisTree","");
    chreco_DY->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2017*.root/AnalysisTree");
    TTree *treereco_DY = (TTree*) chreco_DY;

    TChain *chreco_QCD = new TChain("AnalysisTree","");
    chreco_QCD->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2017_CHS/muon/uhh2.AnalysisModuleRunner.MC.QCD_HT_2017*.root/AnalysisTree");
    TTree *treereco_QCD = (TTree*) chreco_QCD;

//array for variable 

    int len = 0; int len_rec = 0;
    if(var_name == "DeltaY") len = 9, len_rec = 15;
    if(var_name == "Mttbar") len = 8, len_rec = 13;   
    if(var_name == "Rapidity_ttbar") len = 13, len_rec = 23;
    if(var_name == "tlead_pT") len = 6, len_rec = 9;
    if(var_name == "pT_ttbar") len = 6, len_rec = 9;

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
    TH1F *WJets_boosted = new TH1F("WJets_boosted","",newrec,new_rec);
    TH1F *ST_boosted = new TH1F("ST_boosted","",newrec,new_rec);
    TH1F *DY_boosted = new TH1F("DY_boosted","",newrec,new_rec);
    TH1F *QCD_boosted = new TH1F("QCD_boosted","",newrec,new_rec);

    TH1F *Data_resolved = new TH1F("Data_resolved","",newrec,new_rec);
    TH1F *TTbar_resolved = new TH1F("TTbar_resolved","",newrec,new_rec);
    TH1F *WJets_resolved = new TH1F("WJets_resolved","",newrec,new_rec);
    TH1F *ST_resolved = new TH1F("ST_resolved","",newrec,new_rec);
    TH1F *DY_resolved = new TH1F("DY_resolved","",newrec,new_rec);
    TH1F *QCD_resolved = new TH1F("QCD_resolved","",newrec,new_rec);

    TH1F *Data_semiresolved = new TH1F("Data_semiresolved","",newrec,new_rec);
    TH1F *TTbar_semiresolved = new TH1F("TTbar_semiresolved","",newrec,new_rec);
    TH1F *WJets_semiresolved = new TH1F("WJets_semiresolved","",newrec,new_rec);
    TH1F *ST_semiresolved = new TH1F("ST_semiresolved","",newrec,new_rec);
    TH1F *DY_semiresolved = new TH1F("DY_semiresolved","",newrec,new_rec);
    TH1F *QCD_semiresolved = new TH1F("QCD_semiresolved","",newrec,new_rec);


//-------Syst----------??

    TH1F *ttbar_boosted_pu_up = new TH1F("ttbar_boosted_pu_up","",newrec,new_rec);
    TH1F *ttbar_boosted_pu_down  = new TH1F("ttbar_boosted_pu_down","",newrec,new_rec);
    TH1F *ttbar_boosted_MuonID_up  = new TH1F("ttbar_boosted_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_boosted_MuonID_down  = new TH1F("ttbar_boosted_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_boosted_Trigger_up  = new TH1F("ttbar_boosted_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_boosted_Trigger_down  = new TH1F("ttbar_boosted_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_boosted_mistag_up  = new TH1F("ttbar_boosted_mistag_up","",newrec,new_rec);
    TH1F *ttbar_boosted_mistag_down  = new TH1F("ttbar_boosted_mistag_down","",newrec,new_rec);

    TH1F *ttbar_semiresolved_pu_up = new TH1F("ttbar_semiresolved_pu_up","",newrec,new_rec);
    TH1F *ttbar_semiresolved_pu_down  = new TH1F("ttbar_semiresolved_pu_down","",newrec,new_rec);
    TH1F *ttbar_semiresolved_MuonID_up  = new TH1F("ttbar_semiresolved_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_semiresolved_MuonID_down  = new TH1F("ttbar_semiresolved_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_semiresolved_Trigger_up  = new TH1F("ttbar_semiresolved_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_semiresolved_Trigger_down  = new TH1F("ttbar_semiresolved_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_semiresolved_mistag_up  = new TH1F("ttbar_semiresolved_mistag_up","",newrec,new_rec);
    TH1F *ttbar_semiresolved_mistag_down  = new TH1F("ttbar_semiresolved_mistag_down","",newrec,new_rec);

    TH1F *ttbar_resolved_pu_up = new TH1F("ttbar_resolved_pu_up","",newrec,new_rec);
    TH1F *ttbar_resolved_pu_down  = new TH1F("ttbar_resolved_pu_down","",newrec,new_rec);
    TH1F *ttbar_resolved_MuonID_up  = new TH1F("ttbar_resolved_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_resolved_MuonID_down  = new TH1F("ttbar_resolved_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_resolved_Trigger_up  = new TH1F("ttbar_resolved_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_resolved_Trigger_down  = new TH1F("ttbar_resolved_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_resolved_mistag_up  = new TH1F("ttbar_resolved_mistag_up","",newrec,new_rec);
    TH1F *ttbar_resolved_mistag_down  = new TH1F("ttbar_resolved_mistag_down","",newrec,new_rec);

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


    string Mttbar_gen = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";


    Float_t mistag_boosted = 0.71;
    Float_t mistag_boosted_up = 0.66;
    Float_t mistag_boosted_down = 0.76;

    Float_t mistag_semiresolved = 0.73;
    Float_t mistag_semiresolved_up = 0.68;
    Float_t mistag_semiresolved_down = 0.78;

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
    treereco_ttbar->Project("TTbar_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));
    treereco_wjets->Project("WJets_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));
    treereco_ST->Project("ST_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));
    treereco_DY->Project("DY_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));
    treereco_QCD->Project("QCD_boosted",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));

    treereco_data->Project("Data_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s",selcuts_data_semiresolved.c_str()));
    treereco_ttbar->Project("TTbar_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_wjets->Project("WJets_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_ST->Project("ST_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_DY->Project("DY_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_QCD->Project("QCD_semiresolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));

    treereco_data->Project("Data_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s",selcuts_data_resolved.c_str()));
    treereco_ttbar->Project("TTbar_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_wjets->Project("WJets_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_ST->Project("ST_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_DY->Project("DY_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_QCD->Project("QCD_resolved",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));

// ------ filling_syst_1D_histograms----------??

//boosted
    treereco_ttbar->Project("ttbar_boosted_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up",selcuts_boosted_central.c_str()));
    treereco_ttbar->Project("ttbar_boosted_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down",selcuts_boosted_central.c_str()));
    treereco_ttbar->Project("ttbar_boosted_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str())); 
    treereco_ttbar->Project("ttbar_boosted_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));
    treereco_ttbar->Project("ttbar_boosted_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_boosted_central.c_str()));
    treereco_ttbar->Project("ttbar_boosted_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_boosted_central.c_str()));
    treereco_ttbar->Project("ttbar_boosted_mistag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_boosted_up.c_str()));
    treereco_ttbar->Project("ttbar_boosted_mistag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_boosted_down.c_str()));

//semiresolved

    treereco_ttbar->Project("ttbar_semiresolved_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_mistag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_semiresolved_up.c_str()));
    treereco_ttbar->Project("ttbar_semiresolved_mistag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_semiresolved_down.c_str()));


//resolved

    treereco_ttbar->Project("ttbar_resolved_pu_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_up",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("ttbar_resolved_pu_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu_down",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("ttbar_resolved_MuonID_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_up*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("ttbar_resolved_MuonID_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID_down*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("ttbar_resolved_Trigger_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("ttbar_resolved_Trigger_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("ttbar_resolved_mistag_up",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_up*weight_pu",selcuts_resolved_up.c_str()));
    treereco_ttbar->Project("ttbar_resolved_mistag_down",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str(),var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger_down*weight_pu",selcuts_resolved_down.c_str()));


//-------Migration_Matrix_for_nominal_unfolding------??  

//boosted
    treereco_ttbar->Project("Migration_Matrix_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));
    treereco_ttbar->Project("Var_gen_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));

//semiresolved

    treereco_ttbar->Project("Migration_Matrix_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));
    treereco_ttbar->Project("Var_gen_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));

//resolved

    treereco_ttbar->Project("Migration_Matrix_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));
    treereco_ttbar->Project("Var_gen_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));


//-----------Juntando todo en los viejos histogramas --------- ?? 


    TH1F *Data = new TH1F("Data","",newrec,new_rec);
    TH1F *TTbar = new TH1F("TTbar","",newrec,new_rec);
    TH1F *WJets = new TH1F("WJets","",newrec,new_rec);
    TH1F *ST = new TH1F("ST","",newrec,new_rec);
    TH1F *DY = new TH1F("DY","",newrec,new_rec);
    TH1F *QCD = new TH1F("QCD","",newrec,new_rec);

    TH1F *ttbar_pu_up = new TH1F("ttbar_pu_up","",newrec,new_rec);
    TH1F *ttbar_pu_down  = new TH1F("ttbar_pu_down","",newrec,new_rec);
    TH1F *ttbar_MuonID_up  = new TH1F("ttbar_MuonID_up","",newrec,new_rec);
    TH1F *ttbar_MuonID_down  = new TH1F("ttbar_MuonID_down","",newrec,new_rec);
    TH1F *ttbar_Trigger_up  = new TH1F("ttbar_Trigger_up","",newrec,new_rec);
    TH1F *ttbar_Trigger_down  = new TH1F("ttbar_Trigger_down","",newrec,new_rec);
    TH1F *ttbar_mistag_up  = new TH1F("ttbar_mistag_up","",newrec,new_rec);
    TH1F *ttbar_mistag_down  = new TH1F("ttbar_mistag_down","",newrec,new_rec);

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
 
    ttbar_pu_up->Sumw2();
    ttbar_pu_down->Sumw2();
    ttbar_MuonID_up->Sumw2();
    ttbar_MuonID_down->Sumw2();
    ttbar_Trigger_up->Sumw2();
    ttbar_Trigger_down->Sumw2();
    ttbar_mistag_up->Sumw2();
    ttbar_mistag_down->Sumw2();

    ttbar_pu_up->Add(ttbar_boosted_pu_up);
    ttbar_pu_down->Add(ttbar_boosted_pu_down);
    ttbar_MuonID_up->Add(ttbar_boosted_MuonID_up);
    ttbar_MuonID_down->Add(ttbar_boosted_MuonID_down);
    ttbar_Trigger_up->Add(ttbar_boosted_Trigger_up);
    ttbar_Trigger_down->Add(ttbar_boosted_Trigger_down);
    ttbar_mistag_up->Add(ttbar_boosted_mistag_up);
    ttbar_mistag_down->Add(ttbar_boosted_mistag_down);

    ttbar_pu_up->Add(ttbar_semiresolved_pu_up);
    ttbar_pu_down->Add(ttbar_semiresolved_pu_down);
    ttbar_MuonID_up->Add(ttbar_semiresolved_MuonID_up);
    ttbar_MuonID_down->Add(ttbar_semiresolved_MuonID_down);
    ttbar_Trigger_up->Add(ttbar_semiresolved_Trigger_up);
    ttbar_Trigger_down->Add(ttbar_semiresolved_Trigger_down);
    ttbar_mistag_up->Add(ttbar_semiresolved_mistag_up);
    ttbar_mistag_down->Add(ttbar_semiresolved_mistag_down);

    ttbar_pu_up->Add(ttbar_resolved_pu_up);
    ttbar_pu_down->Add(ttbar_resolved_pu_down);
    ttbar_MuonID_up->Add(ttbar_resolved_MuonID_up);
    ttbar_MuonID_down->Add(ttbar_resolved_MuonID_down);
    ttbar_Trigger_up->Add(ttbar_resolved_Trigger_up);
    ttbar_Trigger_down->Add(ttbar_resolved_Trigger_down);
    ttbar_mistag_up->Add(ttbar_resolved_mistag_up);
    ttbar_mistag_down->Add(ttbar_resolved_mistag_down);

    Migration_Matrix->Sumw2();
    Migration_Matrix->Add(Migration_Matrix_boosted);
    Migration_Matrix->Add(Migration_Matrix_semiresolved);
    Migration_Matrix->Add(Migration_Matrix_resolved);

    Var_gen->Sumw2();
    Var_gen->Add(Var_gen_boosted);
    Var_gen->Add(Var_gen_semiresolved);
    Var_gen->Add(Var_gen_resolved);

//-------Migration_matrxi_for_P&S--------------------    
    treereco_ttbar->Project("PS_boosted",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_boosted_central.c_str()));    

    treereco_ttbar->Project("PS_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_semiresolved_central.c_str()));

    treereco_ttbar->Project("PS_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu",selcuts_resolved_central.c_str()));

    PS->Sumw2();
    PS->Add(PS_boosted);
    PS->Add(PS_semiresolved);
    PS->Add(PS_resolved);

//----------Making_input_root_file_for_unfolding-----------?

    TFile out("Input_undfolding_data_.root","recreate");
    Data->Write();
    TTbar->Write();
    WJets->Write(); 
    ST->Write(); 
    DY->Write();
    QCD->Write();
    Migration_Matrix->Write();    
    Var_gen->Write();

    Data_resolved->Write();
    TTbar_resolved->Write();
    WJets_resolved->Write();
    ST_resolved->Write();
    DY_resolved->Write();
    QCD_resolved->Write();

    ttbar_pu_down->Write();
    ttbar_pu_up->Write();
    ttbar_MuonID_up->Write();
    ttbar_MuonID_down->Write();
    ttbar_Trigger_up->Write();
    ttbar_Trigger_down->Write();
    ttbar_mistag_up->Write();
    ttbar_mistag_down->Write();


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

   TLegend leg(.65, .65, .85, .85, "");
   leg.SetFillColor(0);
   leg.AddEntry(Purity, "Purity");
   leg.AddEntry(Stability, "Stability");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   cc->Print("PS.pdf");

 
   Float_t Bins_pow[] = {0,500,600,900,1500};
   Int_t  binnum_pow = sizeof(Bins_pow)/sizeof(Float_t) - 1;

   TH1F *Powheg = new TH1F("Powheg","",binnum_pow,Bins_pow);

   Powheg->SetBinContent(1,0.0033);
   Powheg->SetBinContent(2,0.0039);
   Powheg->SetBinContent(3,0.0056);
   Powheg->SetBinContent(4,0.012);

   Powheg->GetYaxis()->SetRangeUser(-0.02,0.07);
   Powheg->GetYaxis()->SetTitle("A_{c}");
   Powheg->GetXaxis()->SetTitle("M_{t #bar{t}}");
   Powheg->SetLineColor(kRed);
   Powheg->SetLineWidth(2);

   TCanvas* gg = new TCanvas("gg","",2400,1200);
   gg->Divide(1,1);
   gg->cd(1);
   Powheg->Draw();

   TLegend legg(.15, .65, .35, .85, "");
   legg.SetFillColor(0);
   legg.AddEntry(Purity, "Powheg+Pythia8");
   legg.SetBorderSize(0);
   legg.Draw("Same");


   gg->Print("Powheg.pdf");

   Float_t Bins_pow2[] = {0,0.01,0.02,0.03,0.04,0.05,0.06,0.07,0.08};
   Int_t  binnum_pow2 = sizeof(Bins_pow2)/sizeof(Float_t) - 1;

   TH1F *Powheg2 = new TH1F("Powheg2","",binnum_pow2,Bins_pow2);

   Powheg2->SetBinContent(1,0);
   Powheg2->SetBinContent(2,5);
   Powheg2->SetBinContent(3,16);
   Powheg2->SetBinContent(4,33);
   Powheg2->SetBinContent(5,35);
   Powheg2->SetBinContent(6,19);
   Powheg2->SetBinContent(7,6);
   Powheg2->SetBinContent(8,0);

   Powheg2->Write();

   Float_t Bins_pow3[] = {0.005,0.008,0.011,0.014,0.017,0.020,0.023,0.026};
   Int_t  binnum_pow3 = sizeof(Bins_pow3)/sizeof(Float_t) - 1;

   TH1F *Powheg3 = new TH1F("Powheg3","",binnum_pow3,Bins_pow3);

   Powheg3->SetBinContent(1,1);
   Powheg3->SetBinContent(2,7);
   Powheg3->SetBinContent(3,18);
   Powheg3->SetBinContent(4,38);
   Powheg3->SetBinContent(5,17);
   Powheg3->SetBinContent(6,8);
   Powheg3->SetBinContent(7,3);

   Powheg3->Write();

}


