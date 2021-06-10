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


void all_unfolding_data(float_t top = 1)
{

    
//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/no_chi2_cut/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TChain *chreco_wjets = new TChain("AnalysisTree","");
    chreco_wjets->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/no_chi2_cut/uhh2.AnalysisModuleRunner.MC.WJ*.root/AnalysisTree");
    TTree *treereco_wjets = (TTree*) chreco_wjets;

    TChain *chreco_ST = new TChain("AnalysisTree","");
    chreco_ST->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/no_chi2_cut/uhh2.AnalysisModuleRunner.MC.ST*.root/AnalysisTree");
    TTree *treereco_ST = (TTree*) chreco_ST;

    TChain *chreco_DY = new TChain("AnalysisTree","");
    chreco_DY->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/no_chi2_cut/uhh2.AnalysisModuleRunner.MC.DYJets*.root/AnalysisTree");
    TTree *treereco_DY = (TTree*) chreco_DY;

    TChain *chreco_QCD = new TChain("AnalysisTree","");
    chreco_QCD->Add("/nfs/dust/cms/user/hugobg/ZpPrime_102X/analysis_output/2018/muon/no_chi2_cut/uhh2.AnalysisModuleRunner.MC.QCD*.root/AnalysisTree");
    TTree *treereco_QCD = (TTree*) chreco_QCD;
 
    TChain *chreco_data = new TChain("AnalysisTree","");
    chreco_data->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/no_chi2_cut/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2018.root/AnalysisTree");
    TTree *treereco_data = (TTree*) chreco_data;


//-----Backgrounds------??

    TH1F *DATA_mSD = new TH1F("DATA_mSD","",20,0,400);
    TH1F *ttbar_mSD = new TH1F("ttbar_mSD","",20,0,400);
    TH1F *wjets_mSD = new TH1F("wjets_mSD","",20,0,400);
    TH1F *ST_mSD = new TH1F("ST_mSD","",20,0,400);
    TH1F *DY_mSD = new TH1F("DY_mSD","",20,0,400);
    TH1F *QCD_mSD = new TH1F("QCD_mSD","",20,0,400);

    TH1F *DATA_eta = new TH1F("DATA_eta","",20,-2.5,2.5);
    TH1F *ttbar_eta = new TH1F("ttbar_eta","",20,-2.5,2.5);
    TH1F *wjets_eta = new TH1F("wjets_eta","",20,-2.5,2.5);
    TH1F *ST_eta = new TH1F("ST_eta","",20,-2.5,2.5);
    TH1F *DY_eta = new TH1F("DY_eta","",20,-2.5,2.5);
    TH1F *QCD_eta = new TH1F("QCD_eta","",20,-2.5,2.5);

    TH1F *DATA_pt = new TH1F("DATA_pt","",20,400,900);
    TH1F *ttbar_pt = new TH1F("ttbar_pt","",20,400,900);
    TH1F *wjets_pt = new TH1F("wjets_pt","",20,400,900);
    TH1F *ST_pt = new TH1F("ST_pt","",20,400,900);
    TH1F *DY_pt = new TH1F("DY_pt","",20,400,900);
    TH1F *QCD_pt = new TH1F("QCD_pt","",20,400,900);


//---------selection_cuts && weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*s --------??

    string selcuts;
    if(top == 0)  selcuts = "(rec_chi2 > 30 && btagN == 0 && Ak8_j1_pt > 500 && TMath::Abs(Ak8_j1_eta) < 2.4)";
    if(top == 1)  selcuts = "(rec_chi2 > 30 && wtagN >= 1 && btagN == 0 && Ak8_j1_pt > 500 && TMath::Abs(Ak8_j1_eta) < 2.4)";

    cout << selcuts.c_str() << endl;

//------Filling_bkgs---------??

    treereco_data->Project("DATA_mSD","Ak8_j1_mSD",Form("%s",selcuts.c_str()));
    treereco_ttbar->Project("ttbar_mSD","Ak8_j1_mSD",Form("%s*weight",selcuts.c_str()));
    treereco_wjets->Project("wjets_mSD","Ak8_j1_mSD",Form("%s*weight",selcuts.c_str()));
    treereco_ST->Project("ST_mSD","Ak8_j1_mSD",Form("%s*weight",selcuts.c_str()));
    treereco_DY->Project("DY_mSD","Ak8_j1_mSD",Form("%s*weight",selcuts.c_str()));
    treereco_QCD->Project("QCD_mSD","Ak8_j1_mSD",Form("%s*weight",selcuts.c_str()));

    treereco_data->Project("DATA_eta","Ak8_j1_eta",Form("%s",selcuts.c_str()));
    treereco_ttbar->Project("ttbar_eta","Ak8_j1_eta",Form("%s*weight",selcuts.c_str()));
    treereco_wjets->Project("wjets_eta","Ak8_j1_eta",Form("%s*weight",selcuts.c_str()));
    treereco_ST->Project("ST_eta","Ak8_j1_eta",Form("%s*weight",selcuts.c_str()));
    treereco_DY->Project("DY_eta","Ak8_j1_eta",Form("%s*weight",selcuts.c_str()));
    treereco_QCD->Project("QCD_eta","Ak8_j1_eta",Form("%s*weight",selcuts.c_str()));

    treereco_data->Project("DATA_pt","Ak8_j1_pt",Form("%s",selcuts.c_str()));
    treereco_ttbar->Project("ttbar_pt","Ak8_j1_pt",Form("%s*weight",selcuts.c_str()));
    treereco_wjets->Project("wjets_pt","Ak8_j1_pt",Form("%s*weight",selcuts.c_str()));
    treereco_ST->Project("ST_pt","Ak8_j1_pt",Form("%s*weight",selcuts.c_str()));
    treereco_DY->Project("DY_pt","Ak8_j1_pt",Form("%s*weight",selcuts.c_str()));
    treereco_QCD->Project("QCD_pt","Ak8_j1_pt",Form("%s*weight",selcuts.c_str()));



    TCanvas c1("c1","stacked hists",10,10,700,900);
    c1.Divide(1,2);
    c1.cd(1);


    THStack *hs = new THStack("hs"," stacked");
    ttbar_mSD->SetFillColor(kRed);
    hs->Add(ttbar_mSD);
    wjets_mSD->SetFillColor(kGreen);
    hs->Add(wjets_mSD);
    ST_mSD->SetFillColor(kBlue);
    hs->Add(ST_mSD);
    QCD_mSD->SetFillColor(kYellow);
    hs->Add(QCD_mSD);
    DY_mSD->SetFillColor(kOrange);
    hs->Add(DY_mSD);
    hs->Draw("HIST");
    DATA_mSD->SetMarkerStyle(21);
    DATA_mSD->Draw("p same");

    c1.cd(2);

    THStack *hs1 = new THStack("hs1"," stacked");
    ttbar_pt->SetFillColor(kRed);
    hs1->Add(ttbar_pt);
    wjets_pt->SetFillColor(kGreen);
    hs1->Add(wjets_pt);
    ST_pt->SetFillColor(kBlue);
    hs1->Add(ST_pt);
    QCD_pt->SetFillColor(kYellow);
    hs1->Add(QCD_pt);
    DY_pt->SetFillColor(kOrange);
    hs1->Add(DY_pt);
    hs1->Draw("HIST");
    DATA_pt->SetMarkerStyle(21);
    DATA_pt->Draw("p same");

/*
    c1.cd(3);

    THStack *hs2 = new THStack("hs2"," stacked");
    ttbar_eta->SetFillColor(kRed);
    hs2->Add(ttbar_eta);
    wjets_eta->SetFillColor(kGreen);
    hs2->Add(wjets_eta);
    ST_eta->SetFillColor(kBlue);
    hs2->Add(ST_eta);
    QCD_eta->SetFillColor(kYellow);
    hs2->Add(QCD_eta);
    DY_eta->SetFillColor(kOrange);
    hs2->Add(DY_eta);
    hs2->Draw("HIST");
    DATA_eta->SetMarkerStyle(21);
    DATA_eta->Draw("p same");
*/

    if(top == 0) c1.Print("mistoptag.pdf");
    if(top == 1) c1.Print("mistoptag_toptagged.pdf");

    Double_t a;
    cout << "DATA: " << DATA_pt->IntegralAndError(1,20,a) << endl;
    cout << a << endl;
    cout << "ttbar: " << ttbar_pt->IntegralAndError(1,20,a) << endl; 
    cout << a << endl;
    cout << "wjets: " << wjets_pt->IntegralAndError(1,20,a) << endl;
    cout << a << endl;
    cout << "ST: " << ST_pt->IntegralAndError(1,20,a) << endl;
    cout << a << endl;
    cout << "DY: " << DY_pt->IntegralAndError(1,20,a) << endl;
    cout << a << endl;
    cout << "QCD: " << QCD_pt->IntegralAndError(1,20,a) << endl;
    cout << a << endl;
}







