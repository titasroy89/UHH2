#include <TROOT.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "TTree.h"
#include "TH1D.h"
#include "TH1F.h"
#include "THStack.h"
#include "TFrame.h"
#include "TPad.h"
#include "TLegend.h"


void all_unfolding_data()
{

    
//----obetener_toda_la_informacion_de_entrada--------??

/*    gStyle->SetOptStat(0);
    TChain *chreco_data = new TChain("AnalysisTree","");
    chreco_data->Add(Form("/nfs/dust/cms/user/hugobg/Zprime_102X/analysis_output/%s/muon/workdir_Zprime_Analysis_muon/uhh2.AnalysisModuleRunner.DATA.DATA.root/AnalysisTree",year.c_str()));
    TTree *treereco_data = (TTree*) chreco_data;
*/
    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon///workdir_Zprime_Analysis_2018/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_0.root");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon///workdir_Zprime_Analysis_2018/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_1.root");    
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon///workdir_Zprime_Analysis_2018/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018_2.root");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TChain *chreco_wjets = new TChain("AnalysisTree","");
    chreco_wjets->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon///workdir_Zprime_Analysis_2018/uhh2.AnalysisModuleRunner.MC.WJ*.root/AnalysisTree");
    TTree *treereco_wjets = (TTree*) chreco_wjets;

    cout << treereco_wjets->GetEntries() << endl;

/*
    TChain *chreco_ST = new TChain("AnalysisTree","");
    chreco_ST->Add(Form("/nfs/dust/cms/user/hugobg/Zprime_102X/analysis_output/%s/muon/workdir_Zprime_Analysis_muon/uhh2.AnalysisModuleRunner.MC.ST.root/AnalysisTree",year.c_str()));
    TTree *treereco_ST = (TTree*) chreco_ST;

    TChain *chreco_DY = new TChain("AnalysisTree","");
    chreco_DY->Add(Form("/nfs/dust/cms/user/hugobg/Zprime_102X/analysis_output/%s/muon/workdir_Zprime_Analysis_muon/uhh2.AnalysisModuleRunner.MC.DYJets.root/AnalysisTree",year.c_str()));
    TTree *treereco_DY = (TTree*) chreco_DY;

    TChain *chreco_QCD = new TChain("AnalysisTree","");
    chreco_QCD->Add(Form("/nfs/dust/cms/user/hugobg/Zprime_102X/analysis_output/%s/muon/workdir_Zprime_Analysis_muon/uhh2.AnalysisModuleRunner.MC.QCD.root/AnalysisTree",year.c_str()));
    TTree *treereco_QCD = (TTree*) chreco_QCD;
*/
//array for variable 


//-----Bacgrounds------??

//    TH1F *Data = new TH1F("Data","",newrec,new_rec);
    TH1F *h_TH_M = new TH1F("h_TH_M","",30,50,300);
    TH1F *h_TL_M = new TH1F("h_TL_M","",30,50,300);
    TH1F *h_Wtag_mass = new TH1F("h_Wtag_mass","",10,60,110);
    TH1F *h_Wtag_eta = new TH1F("h_Wtag_eta","",12,-4,4);
    TH1F *h_Wtag_phi = new TH1F("h_Wtag_phi","",12,-3,3);
    TH1F *h_genW_mass  = new TH1F("h_genW_mass","",18,0,7);
    TH1F *h_Wjets_mass = new TH1F("h_Wjets_mass","",30,50,300);
    TH1F *h_Wjets_dR = new TH1F("h_Wjets_dR","",18,0,7);
    TH1F *h_chi2_ttbar = new TH1F("h_chi2_ttbar","",30,0,30);
    TH1F *h_chi2_wjets = new TH1F("h_chi2_wjets","",30,0,30);
//    TH1F *ST = new TH1F("ST","",newrec,new_rec);
//    TH1F *DY = new TH1F("DY","",newrec,new_rec);
//    TH1F *QCD = new TH1F("QCD","",newrec,new_rec);

//---------selection_cuts && weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*s --------??

    string selcuts_mass = "(ttagN == 0 && btagN >= 0 && wtagN == 1)";
    string selcuts = "(ttagN == 0 && btagN >= 0 && wtagN == 1)";

    string top_W1 = "TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[2]]) == 24 && (GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]] < 6 && GenParticles.m_pdgId[GenParticles.m_daughter2[GenParticles.m_daughter1[2]]] < 6)";
    string top_W2 = "TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter2[2]]) == 24 && (GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter2[2]]] < 6 && GenParticles.m_pdgId[GenParticles.m_daughter2[GenParticles.m_daughter2[2]]] < 6)";
    string antitop_W1 = "TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[3]]) == 24 && (GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[3]]] < 6 && GenParticles.m_pdgId[GenParticles.m_daughter2[GenParticles.m_daughter1[3]]] < 6)";
    string antitop_W2 = "TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter2[3]]) == 24 && (GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter2[3]]] < 6 && GenParticles.m_pdgId[GenParticles.m_daughter2[GenParticles.m_daughter2[3]]] < 6)";

    string dR_topW1 = "TMath::Sqrt((GenParticles.m_eta[GenParticles.m_daughter1[2]] - Wtag_eta)*(GenParticles.m_eta[GenParticles.m_daughter1[2]] - Wtag_eta) + (GenParticles.m_phi[GenParticles.m_daughter1[2]] - Wtag_phi)*(GenParticles.m_phi[GenParticles.m_daughter1[2]] - Wtag_phi))";
    string dR_topW2 = "TMath::Sqrt((GenParticles.m_eta[GenParticles.m_daughter2[2]] - Wtag_eta)*(GenParticles.m_eta[GenParticles.m_daughter2[2]] - Wtag_eta) + (GenParticles.m_phi[GenParticles.m_daughter2[2]] - Wtag_phi)*(GenParticles.m_phi[GenParticles.m_daughter2[2]] - Wtag_phi))";
    string dR_antitopW1 = "TMath::Sqrt((GenParticles.m_eta[GenParticles.m_daughter1[3]] - Wtag_eta)*(GenParticles.m_eta[GenParticles.m_daughter1[3]] - Wtag_eta) + (GenParticles.m_phi[GenParticles.m_daughter1[3]] - Wtag_phi)*(GenParticles.m_phi[GenParticles.m_daughter1[3]] - Wtag_phi))";
    string dR_antitopW2 = "TMath::Sqrt((GenParticles.m_eta[GenParticles.m_daughter2[3]] - Wtag_eta)*(GenParticles.m_eta[GenParticles.m_daughter2[3]] - Wtag_eta) + (GenParticles.m_phi[GenParticles.m_daughter2[3]] - Wtag_phi)*(GenParticles.m_phi[GenParticles.m_daughter2[3]] - Wtag_phi))";

//------Filling_bkgs---------??
    treereco_ttbar->Project("h_TH_M","TH_M",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts_mass.c_str()));
    treereco_wjets->Project("h_Wjets_mass","TH_M",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts_mass.c_str()));
    treereco_ttbar->Project("h_TL_M","TL_M",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts_mass.c_str()));
    treereco_ttbar->Project("h_Wtag_mass","Wtag_mass",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts.c_str()));
    treereco_ttbar->Project("h_Wtag_eta","Wtag_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts.c_str()));
    treereco_ttbar->Project("h_Wtag_phi","Wtag_phi",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts.c_str()));
    treereco_ttbar->Project("h_genW_mass",Form("%s ? %s : (%s ? %s : (%s ? %s : (%s ? %s : -1.)))",top_W1.c_str(),dR_topW1.c_str(),top_W2.c_str(),dR_topW2.c_str(),antitop_W1.c_str(),dR_antitopW1.c_str(),antitop_W2.c_str(),dR_antitopW2.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts.c_str()));
    treereco_wjets->Project("h_Wjets_dR",Form("%s ? %s : (%s ? %s : (%s ? %s : (%s ? %s : -1.)))",top_W1.c_str(),dR_topW1.c_str(),top_W2.c_str(),dR_topW2.c_str(),antitop_W1.c_str(),dR_antitopW1.c_str(),antitop_W2.c_str(),dR_antitopW2.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts.c_str()));


    treereco_ttbar->Project("h_chi2_ttbar","rec_chi2",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts_mass.c_str()));
    treereco_wjets->Project("h_chi2_wjets","rec_chi2",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_btagdisc_central",selcuts_mass.c_str()));

//    treereco_ttbar-eProject("h_genW_mass","TMath::Abs(GenParticles.m_pdgId[GenParticles.m_daughter1[2]]) == 24 && (GenParticles.m_pdgId[GenParticles.m_daughter1[GenParticles.m_daughter1[2]]] < 6 && GenParticles.m_pdgId[GenParticles.m_daughter2[GenParticles.m_daughter1[2]]] < 6) ? GenParticles.m_pdgId[2] : GenParticles.m_pdgId[3]");
    

    TCanvas c1("c1","stacked hists",10,10,700,900);
    c1.Divide(3,3);
    c1.cd(1);
    THStack *hs = new THStack("hs"," stacked"); 
    h_Wjets_mass->SetFillColor(kBlue);
    hs->Add(h_Wjets_mass);
    h_TH_M->SetFillColor(kRed);
    hs->Add(h_TH_M);
    hs->Draw("HIST");
    c1.cd(2);
    gPad->SetLogy(0);
    THStack *hs3 = new THStack("hs3"," stacked");
    h_chi2_wjets->SetFillColor(kBlue);
    hs3->Add(h_chi2_wjets);
    h_chi2_ttbar->SetFillColor(kRed);
    hs3->Add(h_chi2_ttbar);
    hs3->Draw("HIST");
    c1.cd(3);
    h_Wtag_mass->SetFillColor(kRed); 
    h_Wtag_mass->Draw("HIST");
    c1.cd(4); 
    h_Wtag_eta->SetFillColor(kRed);     
    h_Wtag_eta->Draw("HIST");
    c1.cd(5);
    h_Wtag_phi->SetFillColor(kRed);
    h_Wtag_phi->Draw("HIST");
    c1.cd(6);
    THStack *hs2 = new THStack("hs2"," stacked");
    h_genW_mass->SetFillColor(kRed);
    hs2->Add(h_genW_mass);
    gPad->SetLogy();
    hs2->Draw("HIST"); 
    c1.Print("W_tag.pdf");
    

}







