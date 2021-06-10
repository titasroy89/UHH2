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

void N_Ak4(string var_name = "", string var_gen = "", string region = "", string year = "")
{

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar2l_chs = new TChain("AnalysisTree","");
    chreco_ttbar2l_chs->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTTo2*.root/AnalysisTree");
    TTree *treereco_ttbar2l_chs = (TTree*) chreco_ttbar2l_chs;


//array for variable 

//-----Bacgrounds------??
    TH1F *Data = new TH1F("Data","",10,-3,3);

//---------selection_cuts && weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*s --------??

//------Filling_bkgs---------??
    treereco_ttbar2l_chs->Project("Data",,GenParticles.

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
    Data_chs->Add(Data_boosted_chs);
    Data_chs->Add(Data_semiresolved_chs);
    Data_chs->Add(Data_resolved_chs);

    TTbar_chs->Sumw2();
    TTbar_chs->Add(TTbar_boosted_chs);
    TTbar_chs->Add(TTbar_semiresolved_chs);
    TTbar_chs->Add(TTbar_resolved_chs);

    TTbarh_chs->Sumw2();
    TTbar_chs->Add(TTbar_boosted_chs);
    TTbar_chs->Add(TTbar_semiresolved_chs);
    TTbarh_chs->Add(TTbar_resolvedh_chs);

    TTbar2l_chs->Sumw2();
    TTbar_chs->Add(TTbar_boosted_chs);
    TTbar_chs->Add(TTbar_semiresolved_chs);
    TTbar2l_chs->Add(TTbar_resolved2l_chs);

    WJets_chs->Sumw2();
    WJets_chs->Add(WJets_boosted_chs);
    WJets_chs->Add(WJets_semiresolved_chs);
    WJets_chs->Add(WJets_resolved_chs);

    ST_chs->Sumw2();
    ST_chs->Add(ST_boosted_chs);
    ST_chs->Add(ST_semiresolved_chs);
    ST_chs->Add(ST_resolved_chs);

    DY_chs->Sumw2();
    DY_chs->Add(DY_boosted_chs);
    DY_chs->Add(DY_semiresolved_chs);
    DY_chs->Add(DY_resolved_chs);

//    QCD_chs->Sumw2();
//    QCD_chs->Add(QCD_boosted_chs);
//    QCD_chs->Add(QCD_semiresolved_chs);
//    QCD_chs->Add(QCD_resolved_chs);

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


