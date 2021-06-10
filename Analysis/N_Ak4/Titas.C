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
//#include "sigma.h"
//#include "mean.h"
#include "TRandom3.h"

void Titas(string var_name = "", string var_gen = "", string region = "", string year = "")
{

//----obetener_toda_la_informacion_de_entrada--------??
/*
    gStyle->SetOptStat(0);
    TChain *chreco_data_puppi = new TChain("AnalysisTree","");
    chreco_data_puppi->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/uhh2.AnalysisModuleRunner.DATA.DATA*.root/AnalysisTree");
    TTree *treereco_data_puppi = (TTree*) chreco_data_puppi;

    TChain *chreco_ttbar_puppi = new TChain("AnalysisTree","");
    chreco_ttbar_puppi->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root/AnalysisTree");
    TTree *treereco_ttbar_puppi = (TTree*) chreco_ttbar_puppi;

    TChain *chreco_wjets_puppi = new TChain("AnalysisTree","");
    chreco_wjets_puppi->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2018.root/AnalysisTree");
    TTree *treereco_wjets_puppi = (TTree*) chreco_wjets_puppi;

    TChain *chreco_ST_puppi = new TChain("AnalysisTree","");
    chreco_ST_puppi->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/uhh2.AnalysisModuleRunner.MC.ST_2018.root/AnalysisTree");
    TTree *treereco_ST_puppi = (TTree*) chreco_ST_puppi;

    TChain *chreco_DY_puppi = new TChain("AnalysisTree","");
    chreco_DY_puppi->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2018.root/AnalysisTree");
    TTree *treereco_DY_puppi = (TTree*) chreco_DY_puppi;

    TChain *chreco_QCD_puppi = new TChain("AnalysisTree","");
    chreco_QCD_puppi->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018/muon/uhh2.AnalysisModuleRunner.MC.QCD_HT_2018.root/AnalysisTree");
    TTree *treereco_QCD_puppi = (TTree*) chreco_QCD_puppi;

*/
    TChain *chreco_ttbar_chs = new TChain("AnalysisTree","");
    chreco_ttbar_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree");
    TTree *treereco_ttbar_chs = (TTree*) chreco_ttbar_chs;

    TChain *chreco_ttbarh_chs = new TChain("AnalysisTree","");
    chreco_ttbarh_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.TTToH*.root/AnalysisTree");
    TTree *treereco_ttbarh_chs = (TTree*) chreco_ttbarh_chs;

    TChain *chreco_ttbar2l_chs = new TChain("AnalysisTree","");
    chreco_ttbar2l_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.TTTo2*.root/AnalysisTree");
    TTree *treereco_ttbar2l_chs = (TTree*) chreco_ttbar2l_chs;

    TChain *chreco_wjets_chs = new TChain("AnalysisTree","");
    chreco_wjets_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.WJ*.root/AnalysisTree");
    TTree *treereco_wjets_chs = (TTree*) chreco_wjets_chs;

    TChain *chreco_ST_chs = new TChain("AnalysisTree","");
    chreco_ST_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.ST*.root/AnalysisTree");
    TTree *treereco_ST_chs = (TTree*) chreco_ST_chs;

    TChain *chreco_DY_chs = new TChain("AnalysisTree","");
    chreco_DY_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.DYJets*.root/AnalysisTree");
    TTree *treereco_DY_chs = (TTree*) chreco_DY_chs;

    TChain *chreco_QCD_chs = new TChain("AnalysisTree","");
    chreco_QCD_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.MC.QCD*.root/AnalysisTree");
    TTree *treereco_QCD_chs = (TTree*) chreco_QCD_chs;

    TChain *chreco_data_chs = new TChain("AnalysisTree","");
    chreco_data_chs->Add("/nfs/dust/cms/user/titasroy/Run2_analysis_DNN/electron/2018/workdir_eleNNimpl/uhh2.AnalysisModuleRunner.DATA.DATA*.root/AnalysisTree");
    TTree *treereco_data_chs = (TTree*) chreco_data_chs;

//array for variable 

//-----Bacgrounds------??
    TH1F *Data_boosted_puppi = new TH1F("Data_boosted_puppi","",10,-3,3);
    TH1F *TTbar_boosted_puppi  = new TH1F("TTbar_boosted_puppi","",10,-3,3);
    TH1F *WJets_boosted_puppi  = new TH1F("WJets_boosted_puppi","",10,-3,3);
    TH1F *ST_boosted_puppi  = new TH1F("ST_boosted_puppi","",10,-3,3);
    TH1F *DY_boosted_puppi  = new TH1F("DY_boosted_puppi","",10,-3,3);
    TH1F *QCD_boosted_puppi  = new TH1F("QCD_boosted_puppi","",10,-3,3);

    TH1F *Data_resolved_puppi  = new TH1F("Data_resolved_puppi","",10,-3,3);
    TH1F *TTbar_resolved_puppi  = new TH1F("TTbar_resolved_puppi","",10,-3,3);
    TH1F *WJets_resolved_puppi  = new TH1F("WJets_resolved_puppi","",10,-3,3);
    TH1F *ST_resolved_puppi  = new TH1F("ST_resolved_puppi","",10,-3,3);
    TH1F *DY_resolved_puppi  = new TH1F("DY_resolved_puppi","",10,-3,3);
    TH1F *QCD_resolved_puppi  = new TH1F("QCD_resolved_puppi","",10,-3,3);

    TH1F *Data_semiresolved_puppi  = new TH1F("Data_semiresolved_puppi","",10,-3,3);
    TH1F *TTbar_semiresolved_puppi  = new TH1F("TTbar_semiresolved_puppi","",10,-3,3);
    TH1F *WJets_semiresolved_puppi  = new TH1F("WJets_semiresolved_puppi","",10,-3,3);
    TH1F *ST_semiresolved_puppi  = new TH1F("ST_semiresolved_puppi","",10,-3,3);
    TH1F *DY_semiresolved_puppi  = new TH1F("DY_semiresolved_puppi","",10,-3,3);
    TH1F *QCD_semiresolved_puppi  = new TH1F("QCD_semiresolved_puppi","",10,-3,3);

    TH1F *Data_boosted_chs = new TH1F("Data_boosted_chs","",10,-3,3);
    TH1F *TTbar_boosted_chs  = new TH1F("TTbar_boosted_chs","",10,-3,3);
    TH1F *WJets_boosted_chs  = new TH1F("WJets_boosted_chs","",10,-3,3);
    TH1F *ST_boosted_chs  = new TH1F("ST_boosted_chs","",10,-3,3);
    TH1F *DY_boosted_chs  = new TH1F("DY_boosted_chs","",10,-3,3);
    TH1F *QCD_boosted_chs  = new TH1F("QCD_boosted_chs","",10,-3,3);

    TH1F *Data_resolved_chs  = new TH1F("Data_resolved_chs","",10,-3,3);
    TH1F *TTbar_resolved_chs  = new TH1F("TTbar_resolved_chs","",10,-3,3);
    TH1F *TTbar_resolvedh_chs  = new TH1F("TTbar_resolvedh_chs","",10,-3,3);
    TH1F *TTbar_resolved2l_chs  = new TH1F("TTbar_resolved2l_chs","",10,-3,3);
    TH1F *WJets_resolved_chs  = new TH1F("WJets_resolved_chs","",10,-3,3);
    TH1F *ST_resolved_chs  = new TH1F("ST_resolved_chs","",10,-3,3);
    TH1F *DY_resolved_chs  = new TH1F("DY_resolved_chs","",10,-3,3);
    TH1F *QCD_resolved_chs  = new TH1F("QCD_resolved_chs","",10,-3,3);

    TH1F *Data_semiresolved_chs  = new TH1F("Data_semiresolved_chs","",10,-3,3);
    TH1F *TTbar_semiresolved_chs  = new TH1F("TTbar_semiresolved_chs","",10,-3,3);
    TH1F *WJets_semiresolved_chs  = new TH1F("WJets_semiresolved_chs","",10,-3,3);
    TH1F *ST_semiresolved_chs  = new TH1F("ST_semiresolved_chs","",10,-3,3);
    TH1F *DY_semiresolved_chs  = new TH1F("DY_semiresolved_chs","",10,-3,3);
    TH1F *QCD_semiresolved_chs  = new TH1F("QCD_semiresolved_chs","",10,-3,3);

//---------selection_cuts && weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*s --------??

    Float_t mistag_boosted = 0.77;

    Float_t mistag_semiresolved = 0.79;

    Float_t mistag_resolved = 1.;

    string selcuts_boosted_central = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_boosted);

    string selcuts_semiresolved_central = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)*%f",region.c_str(),mistag_semiresolved);

    string selcuts_resolved_central = Form("(ttagN == 0 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_resolved);

    string selcuts_data_boosted = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)",region.c_str());  
    string selcuts_data_semiresolved = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)",region.c_str());
    string selcuts_data_resolved = Form("(ttagN == 0 && btagN >= 1 && wtagN == 0 && %s)",region.c_str());

    Float_t mistag_boosted_chs = 0.76;

    Float_t mistag_semiresolved_chs = 0.78;

    Float_t mistag_resolved_chs = 1.;

    string selcuts_boosted_chs_central = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)*%f",region.c_str(),mistag_boosted);

    string selcuts_semiresolved_chs_central = Form("(ttagN == 0 && btagN >= 1 && wtagN == 1 && %s)*%f",region.c_str(),mistag_semiresolved);

    string selcuts_resolved_chs_central = Form("(%s)*%f",region.c_str(),mistag_resolved);

    string selcuts_data_boosted_chs = Form("(ttagN == 1 && btagN >= 1 && wtagN == 0 && %s)",region.c_str());


//------Filling_bkgs---------??
/*
    treereco_data_puppi->Project("Data_boosted_puppi","Ak4_j1_eta",Form("%s",selcuts_data_boosted.c_str()));
    treereco_ttbar_puppi->Project("TTbar_boosted_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_central.c_str()));
    treereco_wjets_puppi->Project("WJets_boosted_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_central.c_str()));
    treereco_ST_puppi->Project("ST_boosted_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_central.c_str()));
    treereco_DY_puppi->Project("DY_boosted_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_central.c_str()));
    treereco_QCD_puppi->Project("QCD_boosted_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_central.c_str()));

    treereco_data_puppi->Project("Data_semiresolved_puppi","Ak4_j1_eta",Form("%s",selcuts_data_semiresolved.c_str()));
    treereco_ttbar_puppi->Project("TTbar_semiresolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_central.c_str()));
    treereco_wjets_puppi->Project("WJets_semiresolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_central.c_str()));
    treereco_ST_puppi->Project("ST_semiresolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_central.c_str()));
    treereco_DY_puppi->Project("DY_semiresolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_central.c_str()));
    treereco_QCD_puppi->Project("QCD_semiresolved_puppi",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_central.c_str()));

    treereco_data_puppi->Project("Data_resolved_puppi","Ak4_j1_eta",Form("%s",selcuts_data_resolved.c_str()));
    treereco_ttbar_puppi->Project("TTbar_resolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_resolved_central.c_str()));
    treereco_wjets_puppi->Project("WJets_resolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_resolved_central.c_str()));
    treereco_ST_puppi->Project("ST_resolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_resolved_central.c_str()));
    treereco_DY_puppi->Project("DY_resolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_resolved_central.c_str()));
    treereco_QCD_puppi->Project("QCD_resolved_puppi","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_resolved_central.c_str()));

    treereco_data_chs->Project("Data_boosted_chs","Ak4_j1_eta",Form("%s",selcuts_data_boosted.c_str()));
    treereco_ttbar_chs->Project("TTbar_boosted_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_chs_central.c_str()));
    treereco_wjets_chs->Project("WJets_boosted_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_chs_central.c_str()));
    treereco_ST_chs->Project("ST_boosted_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_chs_central.c_str()));
    treereco_DY_chs->Project("DY_boosted_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_chs_central.c_str()));
    treereco_QCD_chs->Project("QCD_boosted_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_boosted_chs_central.c_str()));

    treereco_data_chs->Project("Data_semiresolved_chs","Ak4_j1_eta",Form("%s",selcuts_data_semiresolved.c_str()));
    treereco_ttbar_chs->Project("TTbar_semiresolved_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_chs_central.c_str()));
    treereco_wjets_chs->Project("WJets_semiresolved_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_chs_central.c_str()));
    treereco_ST_chs->Project("ST_semiresolved_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_chs_central.c_str()));
    treereco_DY_chs->Project("DY_semiresolved_chs","Ak4_j1_eta",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_chs_central.c_str()));
    treereco_QCD_chs->Project("QCD_semiresolved_chs",Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_pt_rew*weight_btagdisc_central",selcuts_semiresolved_chs_central.c_str()));
*/
    treereco_data_chs->Project("Data_resolved_chs","Ak4_j1_eta",Form("%s",selcuts_data_resolved.c_str()));
    treereco_ttbar_chs->Project("TTbar_resolved_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));
    treereco_ttbarh_chs->Project("TTbar_resolvedh_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));
    treereco_ttbar2l_chs->Project("TTbar_resolved2l_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));
    treereco_wjets_chs->Project("WJets_resolved_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));
    treereco_ST_chs->Project("ST_resolved_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));
    treereco_DY_chs->Project("DY_resolved_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));
    treereco_QCD_chs->Project("QCD_resolved_chs","Ak4_j1_eta",Form("%s*weight",selcuts_resolved_chs_central.c_str()));

//-----------Juntando todo en los viejos histogramas --------- ?? 

/*
    TH1F *Data_puppi = new TH1F("Data_puppi","",10,-3,3);
    TH1F *TTbar_puppi = new TH1F("TTbar_puppi","",10,-3,3);
    TH1F *WJets_puppi = new TH1F("WJets_puppi","",10,-3,3);
    TH1F *ST_puppi = new TH1F("ST_puppi","",10,-3,3);
    TH1F *DY_puppi = new TH1F("DY_puppi","",10,-3,3);
    TH1F *QCD_puppi = new TH1F("QCD_puppi","",10,-3,3);

    Data_puppi->Sumw2();
    Data_puppi->Add(Data_boosted_puppi);
    Data_puppi->Add(Data_semiresolved_puppi);
    Data_puppi->Add(Data_resolved_puppi);

    TTbar_puppi->Sumw2();
    TTbar_puppi->Add(TTbar_boosted_puppi);
    TTbar_puppi->Add(TTbar_semiresolved_puppi);
    TTbar_puppi->Add(TTbar_resolved_puppi);
  
    WJets_puppi->Sumw2(); 
    WJets_puppi->Add(WJets_boosted_puppi);
    WJets_puppi->Add(WJets_semiresolved_puppi);
    WJets_puppi->Add(WJets_resolved_puppi);

    ST_puppi->Sumw2(); 
    ST_puppi->Add(ST_boosted_puppi);
    ST_puppi->Add(ST_semiresolved_puppi);
    ST_puppi->Add(ST_resolved_puppi);

    DY_puppi->Sumw2();
    DY_puppi->Add(DY_boosted_puppi);
    DY_puppi->Add(DY_semiresolved_puppi);
    DY_puppi->Add(DY_resolved_puppi);

    QCD_puppi->Sumw2(); 
    QCD_puppi->Add(QCD_boosted_puppi);
    QCD_puppi->Add(QCD_semiresolved_puppi);
    QCD_puppi->Add(QCD_resolved_puppi);    
 */
    TH1F *Data_chs = new TH1F("Data_chs","",10,-3,3);
    TH1F *TTbar_chs = new TH1F("TTbar_chs","",10,-3,3);
    TH1F *TTbarh_chs = new TH1F("TTbarh_chs","",10,-3,3);
    TH1F *TTbar2l_chs = new TH1F("TTbar2l_chs","",10,-3,3);
    TH1F *WJets_chs = new TH1F("WJets_chs","",10,-3,3);
    TH1F *ST_chs = new TH1F("ST_chs","",10,-3,3);
    TH1F *DY_chs = new TH1F("DY_chs","",10,-3,3);
    TH1F *QCD_chs = new TH1F("QCD_chs","",10,-3,3);

    Data_chs->Sumw2();
//    Data_chs->Add(Data_boosted_chs);
//    Data_chs->Add(Data_semiresolved_chs);
    Data_chs->Add(Data_resolved_chs);

    TTbar_chs->Sumw2();
//    TTbar_chs->Add(TTbar_boosted_chs);
//    TTbar_chs->Add(TTbar_semiresolved_chs);
    TTbar_chs->Add(TTbar_resolved_chs);

    TTbarh_chs->Sumw2();
//    TTbar_chs->Add(TTbar_boosted_chs);
//    //    TTbar_chs->Add(TTbar_semiresolved_chs);
    TTbarh_chs->Add(TTbar_resolvedh_chs);

    TTbar2l_chs->Sumw2();
//    TTbar_chs->Add(TTbar_boosted_chs);
//    //    TTbar_chs->Add(TTbar_semiresolved_chs);
    TTbar2l_chs->Add(TTbar_resolved2l_chs);

    WJets_chs->Sumw2();
//    WJets_chs->Add(WJets_boosted_chs);
//    WJets_chs->Add(WJets_semiresolved_chs);
    WJets_chs->Add(WJets_resolved_chs);

    ST_chs->Sumw2();
//    ST_chs->Add(ST_boosted_chs);
//    ST_chs->Add(ST_semiresolved_chs);
    ST_chs->Add(ST_resolved_chs);

    DY_chs->Sumw2();
//    DY_chs->Add(DY_boosted_chs);
//    DY_chs->Add(DY_semiresolved_chs);
    DY_chs->Add(DY_resolved_chs);

    QCD_chs->Sumw2();
//    QCD_chs->Add(QCD_boosted_chs);
//    QCD_chs->Add(QCD_semiresolved_chs);
    QCD_chs->Add(QCD_resolved_chs);

//    QCD_puppi->SetBinContent(1,0);
    QCD_chs->SetBinContent(1,0);


//----------Making_input_root_file_for_unfolding-----------?

    TFile out("Input_undfolding_data_.root","recreate");
//    Data_puppi->Write();
//    TTbar_puppi->Write();
//    WJets_puppi->Write(); 
//    ST_puppi->Write(); 
//    DY_puppi->Write();
//    QCD_puppi->Write();

    Data_chs->Write();
    TTbar_chs->Write();
    TTbarh_chs->Write();
    TTbar2l_chs->Write();
    WJets_chs->Write(); 
    ST_chs->Write(); 
    DY_chs->Write();
    QCD_chs->Write();
/*
   TH1F *chs = new TH1F("chs","",10,-3,3);
   TH1F *puppi = new TH1F("puppi","",10,-3,3);

   chs->GetYaxis()->SetRangeUser(0,15000);

   for(int i = 1; i<=puppi->GetNbinsX();i++){

   chs->SetBinContent(i,Data_chs->GetBinContent(i));
   puppi->SetBinContent(i,Data_puppi->GetBinContent(i));

   }

   chs->GetXaxis()->SetTitle("Ak4_j1_eta");
   puppi->SetLineColor(kRed);
   puppi->SetLineWidth(2);
   chs->SetLineColor(kBlue);
   chs->SetLineWidth(2);


   TCanvas* cc = new TCanvas("cc","",2400,1200);
   cc->Divide(1,1);
   cc->cd(1);
   chs->Draw("same");
   puppi->Draw("same");

   TLegend leg(.65, .65, .85, .85, "");
   leg.SetFillColor(0);
   leg.AddEntry(puppi, "PUPPI_DATA");
   leg.AddEntry(chs, "CHS_DATA");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   cc->Print("PS.pdf");


   TH1F *chs_MC = new TH1F("chs_MC","",10,-3,3);
   TH1F *puppi_MC = new TH1F("puppi_MC","",10,-3,3);

   chs_MC->GetYaxis()->SetRangeUser(0,15000);

   for(int i = 1; i<=puppi_MC->GetNbinsX();i++){
   
   chs_MC->SetBinContent(i,TTbar_chs->GetBinContent(i)+WJets_chs->GetBinContent(i)+ST_chs->GetBinContent(i)+DY_chs->GetBinContent(i)+QCD_chs->GetBinContent(i));
   puppi_MC->SetBinContent(i,TTbar_puppi->GetBinContent(i)+WJets_puppi->GetBinContent(i)+ST_puppi->GetBinContent(i)+DY_puppi->GetBinContent(i)+QCD_puppi->GetBinContent(i));

   }

   chs_MC->GetXaxis()->SetTitle("Ak4_j1_eta");
   puppi_MC->SetLineColor(kRed);
   puppi_MC->SetLineWidth(2);
   chs_MC->SetLineColor(kBlue);
   chs_MC->SetLineWidth(2);


   TCanvas* cc_MC = new TCanvas("cc_MC","",2400,1200);
   cc_MC->Divide(1,1);
   cc_MC->cd(1);
   chs_MC->Draw("same");
   puppi_MC->Draw("same");

   TLegend leg_MC(.65, .65, .85, .85, "");
   leg_MC.SetFillColor(0);
   leg_MC.AddEntry(puppi_MC, "PUPPI_MC");
   leg_MC.AddEntry(chs_MC, "CHS_MC");
   leg_MC.SetBorderSize(0);
   leg_MC.Draw("Same");

   cc_MC->Print("PS_MC.pdf");
*/
}


