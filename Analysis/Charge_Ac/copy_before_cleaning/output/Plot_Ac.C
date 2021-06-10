#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGaussian.h"
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TRandom.h"
#include "TFile.h"
using namespace RooFit ;


void Plot_Ac(){

      gStyle->SetOptStat(0);
      TFile* file = TFile::Open("output/Ac_Preselection.root");

      TH1F *Mttbar_500 = (TH1F*)file->Get("Mttbar_500");      
      TH1F *Mttbar_500to750 = (TH1F*)file->Get("Mttbar_500to750"); 
      TH1F *Mttbar_750to1000 = (TH1F*)file->Get("Mttbar_750to1000"); 
      TH1F *Mttbar_1000to1500 = (TH1F*)file->Get("Mttbar_1000to1500"); 
      TH1F *Mttbar_1500 = (TH1F*)file->Get("Mttbar_1500"); 
      TH1F *Mttbar_ALL = (TH1F*)file->Get("Mttbar_ALL");

      TFile* file2 = TFile::Open("output/Ac_Preselection.root");

      TH1F *Mttbar_500_Visible = (TH1F*)file2->Get("Mttbar_500");
      TH1F *Mttbar_500to750_Visible = (TH1F*)file2->Get("Mttbar_500to750");
      TH1F *Mttbar_750to1000_Visible = (TH1F*)file2->Get("Mttbar_750to1000");
      TH1F *Mttbar_1000to1500_Visible = (TH1F*)file2->Get("Mttbar_1000to1500");
      TH1F *Mttbar_1500_Visible = (TH1F*)file2->Get("Mttbar_1500");
      TH1F *Mttbar_ALL_Visible = (TH1F*)file2->Get("Mttbar_ALL");

      Float_t bins_gen[] = {0,500,750,1000,1500,2000};
      Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

      TH1F *hb_MC = new TH1F("hb_MC","",binnum_gen,bins_gen);      
      TH1F *hb_Pre = new TH1F("hb_Pre","",binnum_gen,bins_gen);
 
      std::vector <TH1F*> MC;
      MC.push_back(Mttbar_500);
      MC.push_back(Mttbar_500to750);
      MC.push_back(Mttbar_750to1000);
      MC.push_back(Mttbar_1000to1500);
      MC.push_back(Mttbar_1500);
      MC.push_back(Mttbar_ALL);

      std::vector <TH1F*> Preselection;
      Preselection.push_back(Mttbar_500_Visible);
      Preselection.push_back(Mttbar_500to750_Visible);
      Preselection.push_back(Mttbar_750to1000_Visible);
      Preselection.push_back(Mttbar_1000to1500_Visible);
      Preselection.push_back(Mttbar_1500_Visible);
      Preselection.push_back(Mttbar_ALL_Visible);

      for (Int_t t=0; t<6; ++t) 
      {
          hb_MC->SetBinContent(t+1,(MC[t]->Integral(5,8) - MC[t]->Integral(1,4)) / (MC[t]->Integral(5,8) + MC[t]->Integral(1,4)));
          MC[t]->GetXaxis()->SetTitle("#Delta|y|");
          MC[t]->GetYaxis()->SetTitle("Events");

          hb_Pre->SetBinContent(t+1,(Preselection[t]->Integral(5,8) - Preselection[t]->Integral(1,4)) / (Preselection[t]->Integral(5,8) + Preselection[t]->Integral(1,4)));
          Preselection[t]->GetXaxis()->SetTitle("#Delta|y|");
          Preselection[t]->GetYaxis()->SetTitle("Events");

      }

      hb_MC->GetXaxis()->SetTitle("Mttbar [GeV]");
      hb_MC->GetYaxis()->SetTitle("A_{C}");  
      hb_MC->GetYaxis()->SetRangeUser(-0.02,0.02);    
      hb_MC->GetXaxis()->SetBinLabel(1,"<500");
      hb_MC->GetXaxis()->SetBinLabel(2,"[500,750]");
      hb_MC->GetXaxis()->SetBinLabel(3,"[750,1000]");
      hb_MC->GetXaxis()->SetBinLabel(4,"[1000,1500]");
      hb_MC->GetXaxis()->SetBinLabel(5,">1500");

      hb_Pre->GetXaxis()->SetTitle("Mttbar [GeV]");
      hb_Pre->GetYaxis()->SetTitle("A_{C}");
      hb_Pre->GetYaxis()->SetRangeUser(-0.02,0.02);
      hb_Pre->GetXaxis()->SetBinLabel(1,"<500");
      hb_Pre->GetXaxis()->SetBinLabel(2,"[500,750]");
      hb_Pre->GetXaxis()->SetBinLabel(3,"[750,1000]");
      hb_Pre->GetXaxis()->SetBinLabel(4,"[1000,1500]");
      hb_Pre->GetXaxis()->SetBinLabel(5,">1500");

      TFile out("Plot_Ac.root","recreate");
      hb_MC->Write();  
      hb_Pre->Write();
}
