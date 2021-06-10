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

void btag(string var_name = "", string var_gen = "", string region = "", string year = "2018", float_t eta_min = -2.5, float_t eta_max = 2.5, float_t pt_min = 0, float_t pt_max = 2000)
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

//-----Bacgrounds------??

    Float_t Bins_eta[] = {-2.5,-1.6,-0.8,0.,0.8,1.6,2.5};
    Float_t Bins_pt[] = {40,70,100,140,200,300,600,1000,2000};

    Int_t  bins_eta = sizeof(Bins_eta)/sizeof(Float_t) - 1;
    Int_t  bins_pt = sizeof(Bins_pt)/sizeof(Float_t) - 1;

    TH2F *TTbar_AK4_1 = new TH2F("TTbar_AK4_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4_1 = new TH2F("WJets_AK4_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4_1 = new TH2F("ST_AK4_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4_1 = new TH2F("DY_AK4_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4_1 = new TH2F("QCD_AK4_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4_2 = new TH2F("TTbar_AK4_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4_2 = new TH2F("WJets_AK4_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4_2 = new TH2F("ST_AK4_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4_2 = new TH2F("DY_AK4_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4_2 = new TH2F("QCD_AK4_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4_3 = new TH2F("TTbar_AK4_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4_3 = new TH2F("WJets_AK4_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4_3 = new TH2F("ST_AK4_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4_3 = new TH2F("DY_AK4_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4_3 = new TH2F("QCD_AK4_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4_4 = new TH2F("TTbar_AK4_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4_4 = new TH2F("WJets_AK4_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4_4 = new TH2F("ST_AK4_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4_4 = new TH2F("DY_AK4_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4_4 = new TH2F("QCD_AK4_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4_5 = new TH2F("TTbar_AK4_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4_5 = new TH2F("WJets_AK4_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4_5 = new TH2F("ST_AK4_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4_5 = new TH2F("DY_AK4_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4_5 = new TH2F("QCD_AK4_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4_6 = new TH2F("TTbar_AK4_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4_6 = new TH2F("WJets_AK4_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4_6 = new TH2F("ST_AK4_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4_6 = new TH2F("DY_AK4_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4_6 = new TH2F("QCD_AK4_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4btagged_1 = new TH2F("TTbar_AK4btagged_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4btagged_1 = new TH2F("WJets_AK4btagged_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4btagged_1 = new TH2F("ST_AK4btagged_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4btagged_1 = new TH2F("DY_AK4btagged_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4btagged_1 = new TH2F("QCD_AK4btagged_1","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4btagged_2 = new TH2F("TTbar_AK4btagged_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4btagged_2 = new TH2F("WJets_AK4btagged_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4btagged_2 = new TH2F("ST_AK4btagged_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4btagged_2 = new TH2F("DY_AK4btagged_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4btagged_2 = new TH2F("QCD_AK4btagged_2","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4btagged_3 = new TH2F("TTbar_AK4btagged_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4btagged_3 = new TH2F("WJets_AK4btagged_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4btagged_3 = new TH2F("ST_AK4btagged_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4btagged_3 = new TH2F("DY_AK4btagged_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4btagged_3 = new TH2F("QCD_AK4btagged_3","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4btagged_4 = new TH2F("TTbar_AK4btagged_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4btagged_4 = new TH2F("WJets_AK4btagged_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4btagged_4 = new TH2F("ST_AK4btagged_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4btagged_4 = new TH2F("DY_AK4btagged_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4btagged_4 = new TH2F("QCD_AK4btagged_4","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4btagged_5 = new TH2F("TTbar_AK4btagged_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4btagged_5 = new TH2F("WJets_AK4btagged_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4btagged_5 = new TH2F("ST_AK4btagged_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4btagged_5 = new TH2F("DY_AK4btagged_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4btagged_5 = new TH2F("QCD_AK4btagged_5","",bins_pt,Bins_pt,bins_eta,Bins_eta);

    TH2F *TTbar_AK4btagged_6 = new TH2F("TTbar_AK4btagged_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *WJets_AK4btagged_6 = new TH2F("WJets_AK4btagged_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *ST_AK4btagged_6 = new TH2F("ST_AK4btagged_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *DY_AK4btagged_6 = new TH2F("DY_AK4btagged_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);
    TH2F *QCD_AK4btagged_6 = new TH2F("QCD_AK4btagged_6","",bins_pt,Bins_pt,bins_eta,Bins_eta);

//-------Syst----------??

//    treereco_ttbar->Project("TTbar_AK4_1","Ak4_j1_eta:Ak4_j1_pt","weight");

    treereco_ttbar->Project("TTbar_AK4_1","Ak4_j1_eta:Ak4_j1_pt","weight*(jetsAk4Puppi.m_hadronFlavour[0] == 5)");
//    treereco_wjets->Project("WJets_AK4_1","Ak4_j1_eta:Ak4_j1_pt","weight*(jetsAk4Puppi.m_hadronFlavour[0] == 5)");
//    treereco_ST->Project("ST_AK4_1","Ak4_j1_eta:Ak4_j1_pt","weight*(jetsAk4Puppi.m_hadronFlavour[0] == 5)");
//    treereco_DY->Project("DY_AK4_1","Ak4_j1_eta:Ak4_j1_pt","weight*(jetsAk4Puppi.m_hadronFlavour[0] == 5)");
//    treereco_QCD->Project("QCD_AK4_1","Ak4_j1_eta:Ak4_j1_pt","weight*(jetsAk4Puppi.m_hadronFlavour[0] == 5)");

    treereco_ttbar->Project("TTbar_AK4_2","Ak4_j2_eta:Ak4_j2_pt","weight*(jetsAk4Puppi.m_hadronFlavour[1] == 5)");
//    treereco_wjets->Project("WJets_AK4_2","Ak4_j2_eta:Ak4_j2_pt","weight*(jetsAk4Puppi.m_hadronFlavour[1] == 5)");
//    treereco_ST->Project("ST_AK4_2","Ak4_j2_eta:Ak4_j2_pt","weight*(jetsAk4Puppi.m_hadronFlavour[1] == 5)");
//    treereco_DY->Project("DY_AK4_2","Ak4_j2_eta:Ak4_j2_pt","weight*(jetsAk4Puppi.m_hadronFlavour[1] == 5)");
//    treereco_QCD->Project("QCD_AK4_2","Ak4_j2_eta:Ak4_j2_pt","weight*(jetsAk4Puppi.m_hadronFlavour[1] == 5)");
/*
    treereco_ttbar->Project("TTbar_AK4_3","Ak4_j3_pt:Ak4_j3_eta","weight*(Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_wjets->Project("WJets_AK4_3","Ak4_j3_pt:Ak4_j3_eta","weight*(Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_ST->Project("ST_AK4_3","Ak4_j3_pt:Ak4_j3_eta","weight*(Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_DY->Project("DY_AK4_3","Ak4_j3_pt:Ak4_j3_eta","weight*(Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_QCD->Project("QCD_AK4_3","Ak4_j3_pt:Ak4_j3_eta","weight*(Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4_4","Ak4_j4_pt:Ak4_j4_eta","weight*(Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_wjets->Project("WJets_AK4_4","Ak4_j4_pt:Ak4_j4_eta","weight*(Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_ST->Project("ST_AK4_4","Ak4_j4_pt:Ak4_j4_eta","weight*(Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_DY->Project("DY_AK4_4","Ak4_j4_pt:Ak4_j4_eta","weight*(Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_QCD->Project("QCD_AK4_4","Ak4_j4_pt:Ak4_j4_eta","weight*(Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4_5","Ak4_j5_pt:Ak4_j5_eta","weight*(Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_wjets->Project("WJets_AK4_5","Ak4_j5_pt:Ak4_j5_eta","weight*(Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_ST->Project("ST_AK4_5","Ak4_j5_pt:Ak4_j5_eta","weight*(Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_DY->Project("DY_AK4_5","Ak4_j5_pt:Ak4_j5_eta","weight*(Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_QCD->Project("QCD_AK4_5","Ak4_j5_pt:Ak4_j5_eta","weight*(Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4_6","Ak4_j6_pt:Ak4_j6_eta","weight*(Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_wjets->Project("WJets_AK4_6","Ak4_j6_pt:Ak4_j6_eta","weight*(Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_ST->Project("ST_AK4_6","Ak4_j6_pt:Ak4_j6_eta","weight*(Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_DY->Project("DY_AK4_6","Ak4_j6_pt:Ak4_j6_eta","weight*(Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_QCD->Project("QCD_AK4_6","Ak4_j6_pt:Ak4_j6_eta","weight*(Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
*/

    treereco_ttbar->Project("TTbar_AK4btagged_1","Ak4_j1_eta:Ak4_j1_pt","(weight)*(Ak4_j1_deepjetbscore > 0.7264 && jetsAk4Puppi.m_hadronFlavour[0] == 5)");

/*    treereco_wjets->Project("WJets_AK4btagged_1","Ak4_j1_pt:Ak4_j1_eta","(weight)*(Ak4_j1_deepjetbscore > 0.7264  && Ak4_j1_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[0] == 5 : (Ak4_j1_pt >  100000))");
    treereco_ST->Project("ST_AK4btagged_1","Ak4_j1_pt:Ak4_j1_eta","(weight)*(Ak4_j1_deepjetbscore > 0.7264 && Ak4_j1_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[0] == 5 : (Ak4_j1_pt >  100000))");
    treereco_DY->Project("DY_AK4btagged_1","Ak4_j1_pt:Ak4_j1_eta","(weight)*(Ak4_j1_deepjetbscore > 0.7264 && Ak4_j1_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[0] == 5 : (Ak4_j1_pt >  100000))");
    treereco_QCD->Project("QCD_AK4btagged_1","Ak4_j1_pt:Ak4_j1_eta","(weight)*(Ak4_j1_deepjetbscore > 0.7264 && Ak4_j1_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[0] == 5 : (Ak4_j1_pt >  100000))");
*/
    treereco_ttbar->Project("TTbar_AK4btagged_2","Ak4_j2_eta:Ak4_j2_pt","(weight)*(Ak4_j2_deepjetbscore > 0.7264 && jetsAk4Puppi.m_hadronFlavour[1] == 5)");
/*
    treereco_wjets->Project("WJets_AK4btagged_2","Ak4_j2_pt:Ak4_j2_eta","(weight)*(Ak4_j2_deepjetbscore > 0.7264 && Ak4_j2_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[1] == 5 : (Ak4_j2_pt >  100000))");
    treereco_ST->Project("ST_AK4btagged_2","Ak4_j2_pt:Ak4_j2_eta","(weight)*(Ak4_j2_deepjetbscore > 0.7264 && Ak4_j2_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[1] == 5 : (Ak4_j2_pt >  100000))");
    treereco_DY->Project("DY_AK4btagged_2","Ak4_j2_pt:Ak4_j2_eta","(weight)*(Ak4_j2_deepjetbscore > 0.7264 && Ak4_j2_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[1] == 5 : (Ak4_j2_pt >  100000))");
    treereco_QCD->Project("QCD_AK4btagged_2","Ak4_j2_pt:Ak4_j2_eta","(weight)*(Ak4_j2_deepjetbscore > 0.7264 && Ak4_j2_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[1] == 5 : (Ak4_j2_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4btagged_3","Ak4_j3_pt:Ak4_j3_eta","(weight)*(Ak4_j3_deepjetbscore > 0.7264 && Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_wjets->Project("WJets_AK4btagged_3","Ak4_j3_pt:Ak4_j3_eta","(weight)*(Ak4_j3_deepjetbscore > 0.7264 && Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_ST->Project("ST_AK4btagged_3","Ak4_j3_pt:Ak4_j3_eta","(weight)*(Ak4_j3_deepjetbscore > 0.7264 && Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_DY->Project("DY_AK4btagged_3","Ak4_j3_pt:Ak4_j3_eta","(weight)*(Ak4_j3_deepjetbscore > 0.7264 && Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");
    treereco_QCD->Project("QCD_AK4btagged_3","Ak4_j3_pt:Ak4_j3_eta","(weight)*(Ak4_j3_deepjetbscore > 0.7264 && Ak4_j3_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[2] == 5 : (Ak4_j3_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4btagged_4","Ak4_j4_pt:Ak4_j4_eta","(weight)*(Ak4_j4_deepjetbscore > 0.7264 && Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_wjets->Project("WJets_AK4btagged_4","Ak4_j4_pt:Ak4_j4_eta","(weight)*(Ak4_j4_deepjetbscore > 0.7264 && Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_ST->Project("ST_AK4btagged_4","Ak4_j4_pt:Ak4_j4_eta","(weight)*(Ak4_j4_deepjetbscore > 0.7264 && Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_DY->Project("DY_AK4btagged_4","Ak4_j4_pt:Ak4_j4_eta","(weight)*(Ak4_j4_deepjetbscore > 0.7264 && Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");
    treereco_QCD->Project("QCD_AK4btagged_4","Ak4_j4_pt:Ak4_j4_eta","(weight)*(Ak4_j4_deepjetbscore > 0.7264 && Ak4_j4_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[3] == 5 : (Ak4_j4_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4btagged_5","Ak4_j5_pt:Ak4_j5_eta","(weight)*(Ak4_j5_deepjetbscore > 0.7264 && Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_wjets->Project("WJets_AK4btagged_5","Ak4_j5_pt:Ak4_j5_eta","(weight)*(Ak4_j5_deepjetbscore > 0.7264 && Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_ST->Project("ST_AK4btagged_5","Ak4_j5_pt:Ak4_j5_eta","(weight)*(Ak4_j5_deepjetbscore > 0.7264 && Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_DY->Project("DY_AK4btagged_5","Ak4_j5_pt:Ak4_j5_eta","(weight)*(Ak4_j5_deepjetbscore > 0.7264 && Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");
    treereco_QCD->Project("QCD_AK4btagged_5","Ak4_j5_pt:Ak4_j5_eta","(weight)*(Ak4_j5_deepjetbscore > 0.7264 && Ak4_j5_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[4] == 5 : (Ak4_j5_pt >  100000))");

    treereco_ttbar->Project("TTbar_AK4btagged_6","Ak4_j6_pt:Ak4_j6_eta","(weight)*(Ak4_j6_deepjetbscore > 0.7264 && Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_wjets->Project("WJets_AK4btagged_6","Ak4_j6_pt:Ak4_j6_eta","(weight)*(Ak4_j6_deepjetbscore > 0.7264 && Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_ST->Project("ST_AK4btagged_6","Ak4_j6_pt:Ak4_j6_eta","(weight)*(Ak4_j6_deepjetbscore > 0.7264 && Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_DY->Project("DY_AK4btagged_6","Ak4_j6_pt:Ak4_j6_eta","(weight)*(Ak4_j6_deepjetbscore > 0.7264 && Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
    treereco_QCD->Project("QCD_AK4btagged_6","Ak4_j6_pt:Ak4_j6_eta","(weight)*(Ak4_j6_deepjetbscore > 0.7264 && Ak4_j6_pt > 0 ? jetsAk4Puppi.m_hadronFlavour[5] == 5 : (Ak4_j6_pt >  100000))");
*/
    TTbar_AK4_1->Add(TTbar_AK4_2,1);   
/*    TTbar_AK4_1->Add(TTbar_AK4_3,1);
    TTbar_AK4_1->Add(TTbar_AK4_4,1);
    TTbar_AK4_1->Add(TTbar_AK4_5,1);
    TTbar_AK4_1->Add(TTbar_AK4_6,1);

    WJets_AK4_1->Add(WJets_AK4_2,1);
    WJets_AK4_1->Add(WJets_AK4_3,1);
    WJets_AK4_1->Add(WJets_AK4_4,1);
    WJets_AK4_1->Add(WJets_AK4_5,1);
    WJets_AK4_1->Add(WJets_AK4_6,1);

    ST_AK4_1->Add(ST_AK4_2,1);
    ST_AK4_1->Add(ST_AK4_3,1);
    ST_AK4_1->Add(ST_AK4_4,1);
    ST_AK4_1->Add(ST_AK4_5,1);
    ST_AK4_1->Add(ST_AK4_6,1);

    DY_AK4_1->Add(DY_AK4_2,1);
    DY_AK4_1->Add(DY_AK4_3,1);
    DY_AK4_1->Add(DY_AK4_4,1);
    DY_AK4_1->Add(DY_AK4_5,1);
    DY_AK4_1->Add(DY_AK4_6,1);

    QCD_AK4_1->Add(QCD_AK4_2,1);
    QCD_AK4_1->Add(QCD_AK4_3,1);
    QCD_AK4_1->Add(QCD_AK4_4,1);
    QCD_AK4_1->Add(QCD_AK4_5,1);
    QCD_AK4_1->Add(QCD_AK4_6,1);
*/
    TTbar_AK4btagged_1->Add(TTbar_AK4btagged_2,1);
/*
    TTbar_AK4btagged_1->Add(TTbar_AK4btagged_3,1);
    TTbar_AK4btagged_1->Add(TTbar_AK4btagged_4,1);
    TTbar_AK4btagged_1->Add(TTbar_AK4btagged_5,1);
    TTbar_AK4btagged_1->Add(TTbar_AK4btagged_6,1);

    WJets_AK4btagged_1->Add(WJets_AK4btagged_2,1);
    WJets_AK4btagged_1->Add(WJets_AK4btagged_3,1);
    WJets_AK4btagged_1->Add(WJets_AK4btagged_4,1);
    WJets_AK4btagged_1->Add(WJets_AK4btagged_5,1);
    WJets_AK4btagged_1->Add(WJets_AK4btagged_6,1);

    ST_AK4btagged_1->Add(ST_AK4btagged_2,1);
    ST_AK4btagged_1->Add(ST_AK4btagged_3,1);
    ST_AK4btagged_1->Add(ST_AK4btagged_4,1);
    ST_AK4btagged_1->Add(ST_AK4btagged_5,1);
    ST_AK4btagged_1->Add(ST_AK4btagged_6,1);

    DY_AK4btagged_1->Add(DY_AK4btagged_2,1);
    DY_AK4btagged_1->Add(DY_AK4btagged_3,1);
    DY_AK4btagged_1->Add(DY_AK4btagged_4,1);
    DY_AK4btagged_1->Add(DY_AK4btagged_5,1);
    DY_AK4btagged_1->Add(DY_AK4btagged_6,1);

    QCD_AK4btagged_1->Add(QCD_AK4btagged_2,1);
    QCD_AK4btagged_1->Add(QCD_AK4btagged_3,1);
    QCD_AK4btagged_1->Add(QCD_AK4btagged_4,1);
    QCD_AK4btagged_1->Add(QCD_AK4btagged_5,1);
    QCD_AK4btagged_1->Add(QCD_AK4btagged_6,1);
*/
    TFile out("btag_eff_.root","recreate");
    TTbar_AK4_1->Write();
/*
    WJets_AK4_1->Write();
    ST_AK4_1->Write();
    DY_AK4_1->Write();
    QCD_AK4_1->Write();
*/
    TTbar_AK4btagged_1->Write();
/*
    WJets_AK4btagged_1->Write();
    ST_AK4btagged_1->Write();
    DY_AK4btagged_1->Write();
    QCD_AK4btagged_1->Write();
*/


}



