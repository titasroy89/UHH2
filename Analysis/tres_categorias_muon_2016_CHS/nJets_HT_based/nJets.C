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

void nJets(string var_name = "", string var_gen = "", string region = "", string year = "TTTo")
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/old_before_all_sys/uhh2.AnalysisModuleRunner.MC.*.root/AnalysisTree",year.c_str()));
    TTree *treereco = (TTree*) chreco;

//-----Bacgrounds------??

    TH2F *D_boosted = new TH2F("D_boosted","",10,2,12,10,50,1200);
    TH2F *D_resolved = new TH2F("D_resolved","",10,2,12,10,50,1200);
    TH2F *D_semiresolved = new TH2F("D_semiresolved","",10,2,12,10,50,1400);

    TH2F *D_boosted_btag = new TH2F("D_boosted_btag","",10,2,12,10,50,1200);
    TH2F *D_resolved_btag = new TH2F("D_resolved_btag","",10,2,12,10,50,1200);
    TH2F *D_semiresolved_btag = new TH2F("D_semiresolved_btag","",10,2,12,10,50,1400);

    TH1F *Btag_score_boosted = new TH1F("Btag_score_boosted","",10,0,1);
    TH1F *Btag_score_corrections_boosted = new TH1F("Btag_score_corrections_boosted","",10,0,1);

    TH1F *Btag_score_resolved = new TH1F("Btag_score_resolved","",10,0,1);
    TH1F *Btag_score_corrections_resolved = new TH1F("Btag_score_corrections_resolved","",10,0,1);

    TH1F *Btag_score_semiresolved = new TH1F("Btag_score_semiresolved","",10,0,1);
    TH1F *Btag_score_corrections_semiresolved = new TH1F("Btag_score_corrections_semiresolved","",10,0,1);

    string selcuts_boosted_central = "(ttagN >= 0 && btagN >= 1 && wtagN >= 0 && rec_chi2 < 30 && Mttbar > 900)";
    string selcuts_semiresolved_central = "(ttagN == 0 && btagN >= 1 && wtagN == 1 && rec_chi2 < 30 && Mttbar > 900)";
    string selcuts_resolved_central = "(ttagN == 0 && btagN >= 1 && wtagN == 0 && rec_chi2 < 30 && Mttbar > 900)";

    treereco->Project("D_boosted","met_pt:N_Ak4",Form("%s*weight",selcuts_boosted_central.c_str()));
    treereco->Project("D_semiresolved","met_pt:N_Ak4",Form("%s*weight",selcuts_semiresolved_central.c_str()));
    treereco->Project("D_resolved","met_pt:N_Ak4",Form("%s*weight",selcuts_resolved_central.c_str()));
 
    treereco->Project("D_boosted_btag","met_pt:N_Ak4",Form("%s*weight*weight_btagdisc_central",selcuts_boosted_central.c_str()));
    treereco->Project("D_semiresolved_btag","met_pt:N_Ak4",Form("%s*weight*weight_btagdisc_central",selcuts_semiresolved_central.c_str()));
    treereco->Project("D_resolved_btag","met_pt:N_Ak4",Form("%s*weight*weight_btagdisc_central",selcuts_resolved_central.c_str()));

    D_boosted->Divide(D_boosted_btag); 
    D_semiresolved->Divide(D_semiresolved_btag);
    D_resolved->Divide(D_resolved_btag);

    TFile out("HT_SF.root","recreate"); 
    D_boosted->Write();
    D_semiresolved->Write();
    D_resolved->Write();  

}


