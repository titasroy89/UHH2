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

void nJets(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TT*.root/AnalysisTree",year.c_str()));
    TTree *treereco = (TTree*) chreco;

//-----Backgrounds------??

    TH2F *D_boosted = new TH2F("D_boosted","",10,2,12,50,50,1200);
    TH2F *D_boosted_btag = new TH2F("D_boosted_btag","",10,2,12,50,50,1200);

    string selcuts_boosted_central = "(ttagN >= 0 && btagN >= 1 && wtagN >= 0 && rec_chi2 < 30 && Mttbar > 900)";

    treereco->Project("D_boosted","(met_pt+lep1_pt):N_Ak4",Form("%s*weight",selcuts_boosted_central.c_str()));
    treereco->Project("D_boosted_btag","(met_pt+lep1_pt):N_Ak4",Form("%s*weight*weight_btagdisc_central",selcuts_boosted_central.c_str()));

    D_boosted->Divide(D_boosted_btag); 

    TFile out("HT_SF.root","recreate"); 
    D_boosted->Write();

    TH1F *HT_boosted = new TH1F("HT_boosted","",50,50,1200);
    TH1F *HT_boosted_btagged = new TH1F("HT_boosted_btagged","",50,50,1200);
    TH1F *HT_corrections_boosted = new TH1F("HT_corrections_boosted","",50,50,1200);

    TH1F *NJets_boosted = new TH1F("NJets_boosted","",12,0,12);
    TH1F *NJets_boosted_btagged = new TH1F("NJets_boosted_btagged","",12,0,12);
    TH1F *NJets_corrections_boosted = new TH1F("NJets_corrections_boosted","",12,0,12);

    Float_t lep1_pt;
    Float_t met_pt;
    Float_t N_Ak4;
    Float_t weight_btagdisc_central; 
    Float_t weight;
    Float_t Mttbar;
    Float_t rec_chi2;
    Int_t wtagN; Int_t ttagN; Int_t btagN;
    treereco->SetBranchAddress("lep1_pt",&lep1_pt);
    treereco->SetBranchAddress("met_pt",&met_pt);
    treereco->SetBranchAddress("N_Ak4",&N_Ak4);
    treereco->SetBranchAddress("weight_btagdisc_central",&weight_btagdisc_central);
    treereco->SetBranchAddress("weight",&weight);
    treereco->SetBranchAddress("ttagN",&ttagN);
    treereco->SetBranchAddress("btagN",&btagN);
    treereco->SetBranchAddress("wtagN",&wtagN);
    treereco->SetBranchAddress("rec_chi2",&rec_chi2);
    treereco->SetBranchAddress("Mttbar",&Mttbar);

    for(int i=0; i<1000000; i++){        
        treereco->GetEntry(i);
        if(ttagN >= 0 && btagN >= 1 && wtagN >= 0 && rec_chi2 < 30 && Mttbar > 900){
            HT_boosted->Fill(lep1_pt + met_pt,1);
            HT_boosted_btagged->Fill(lep1_pt + met_pt,1*weight_btagdisc_central);
            NJets_boosted->Fill(N_Ak4,1);
            NJets_boosted_btagged->Fill(N_Ak4,1*weight_btagdisc_central); 
            int bin = D_boosted->FindFixBin(N_Ak4, lep1_pt + met_pt);
            float w = D_boosted->GetBinContent(bin);
            //cout << w << endl;
            HT_corrections_boosted->Fill(lep1_pt + met_pt,1*weight_btagdisc_central*w);       
            NJets_corrections_boosted->Fill(N_Ak4,1*weight_btagdisc_central*w);            
        }
    }

   // Define the Canvas

   TCanvas *c = new TCanvas("c", "canvas", 800, 800);
   // Upper plot will be in pad1
   TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
   pad1->SetBottomMargin(0); // Upper and lower plot are joined
   pad1->SetGridx();         // Vertical grid
   pad1->Draw();             // Draw the upper pad: pad1
   pad1->cd();               // pad1 becomes the current pad
   HT_boosted->SetStats(0);          // No statistics on upper plot
   HT_boosted_btagged->Draw();
   HT_boosted->Draw("same");               // Draw h1
   HT_boosted_btagged->Draw("same");         // Draw h2 on top of h1
   HT_corrections_boosted->Draw("same");   // Draw h3 on top of h1 
 
   TAxis *axis = HT_boosted->GetYaxis();
   axis->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
   axis->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis->SetLabelSize(15);

   TLegend leg(.6,.7,.8,.9,"");
   leg.AddEntry(HT_boosted, "no b-tagging SFs","lp");
   leg.AddEntry(HT_boosted_btagged,"b-tagging SFs","lp");
   leg.AddEntry(HT_corrections_boosted,"SFs + corrections","lp");
   leg.SetFillStyle(0);
   leg.SetBorderSize(0);
   leg.SetTextSize(0.04);
   leg.SetTextFont(42);
   leg.Draw();   
 
   // lower plot will be in pad
   c->cd();          // Go back to the main canvas before defining pad2
   TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
   pad2->SetTopMargin(0);
   pad2->SetBottomMargin(0.2);
   pad2->SetGridx(); // vertical grid
   pad2->Draw();
   pad2->cd();       // pad2 becomes the current pad
 
   // Define the ratio plot
   TH1F *h3 = (TH1F*)HT_boosted->Clone("h3");
   TH1F *h5 = (TH1F*)HT_boosted->Clone("h5");
   h3->SetLineColor(kRed);
   h5->SetLineColor(kBlack);
   h3->SetMinimum(0.7);  // Define Y ..
   h3->SetMaximum(1.3); // .. range
   h3->Sumw2();
   h3->SetStats(0);      // No statistics on lower plot
   h3->Divide(HT_boosted_btagged);
   h5->Divide(HT_corrections_boosted);
   h3->SetMarkerStyle(21);
   h5->SetMarkerStyle(21);
   h3->SetMarkerColor(2);
   h5->SetMarkerColor(1);
   h3->Draw("ep");       // Draw the ratio plot
   h5->Draw("ep same");
 
   // h1 settings
   HT_boosted->SetLineColor(kBlue+1);
   HT_boosted->SetLineWidth(2);
 
   // Y axis h1 plot settings
   HT_boosted->GetYaxis()->SetTitleSize(20);
   HT_boosted->GetYaxis()->SetTitleFont(43);
   HT_boosted->GetYaxis()->SetTitleOffset(1.55);
 
   // h2 settings
   HT_boosted_btagged->SetLineColor(kRed);
   HT_boosted_btagged->SetLineWidth(2);

   HT_corrections_boosted->SetLineColor(kBlack);
   HT_corrections_boosted->SetLineWidth(2);   
 
   // Ratio plot (h3) settings
   h3->SetTitle(""); // Remove the ratio title
 
   // Y axis ratio plot settings
   h3->GetYaxis()->SetTitle("ratio");
   h3->GetYaxis()->SetNdivisions(505);
   h3->GetYaxis()->SetTitleSize(20);
   h3->GetYaxis()->SetTitleFont(43);
   h3->GetYaxis()->SetTitleOffset(1.55);
   h3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetYaxis()->SetLabelSize(15);
 
   // X axis ratio plot settings
   h3->GetXaxis()->SetTitle("HT [GeV]");
   h3->GetXaxis()->SetTitleSize(20);
   h3->GetXaxis()->SetTitleFont(43);
   h3->GetXaxis()->SetTitleOffset(1);
   h3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h3->GetXaxis()->SetLabelSize(15);

   c->Print("c.pdf");

   TCanvas *d = new TCanvas("d", "canvas", 800, 800);
   // Upper plot will be in pad1
   TPad *pad3 = new TPad("pad3", "pad3", 0, 0.3, 1, 1.0);
   pad3->SetBottomMargin(0); // Upper and lower plot are joined
   pad3->SetGridx();         // Vertical grid
   pad3->Draw();             // Draw the upper pad: pad1
   pad3->cd();               // pad1 becomes the current pad
   NJets_boosted->SetStats(0);          // No statistics on upper plot
   NJets_boosted_btagged->Draw();
   NJets_boosted->Draw("same");               // Draw h1
   NJets_boosted_btagged->Draw("same");         // Draw h2 on top of h1
   NJets_corrections_boosted->Draw("same");   // Draw h3 on top of h1 

   TAxis *axis2 = NJets_boosted->GetYaxis();
   axis2->ChangeLabel(1, -1, -1, -1, -1, -1, " ");
   axis2->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   axis2->SetLabelSize(15);

   TLegend leg2(.6,.7,.8,.9,"");
   leg2.AddEntry(NJets_boosted, "no b-tagging SFs","lp");
   leg2.AddEntry(NJets_boosted_btagged,"b-tagging SFs","lp");
   leg2.AddEntry(NJets_corrections_boosted,"SFs + corrections","lp");
   leg2.SetFillStyle(0);
   leg2.SetBorderSize(0);
   leg2.SetTextSize(0.04);
   leg2.SetTextFont(42);
   leg2.Draw();

   // lower plot will be in pad
   d->cd();          // Go back to the main canvas before defining pad2
   TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.3);
   pad4->SetTopMargin(0);
   pad4->SetBottomMargin(0.2);
   pad4->SetGridx(); // vertical grid
   pad4->Draw();
   pad4->cd();       // pad2 becomes the current pad

   // Define the ratio plot
   TH1F *h4 = (TH1F*)NJets_boosted->Clone("h4");
   TH1F *h6 = (TH1F*)NJets_boosted->Clone("h6");
   h4->SetLineColor(kRed);
   h6->SetLineColor(kBlack);
   h4->SetMinimum(0.7);  // Define Y ..
   h4->SetMaximum(1.3); // .. range
   h4->Sumw2();
   h4->SetStats(0);      // No statistics on lower plot
   h4->Divide(NJets_boosted_btagged);
   h6->Divide(NJets_corrections_boosted);
   h4->SetMarkerStyle(21);
   h6->SetMarkerStyle(21);
   h4->SetMarkerColor(2);
   h6->SetMarkerColor(1);
   h4->Draw("ep");       // Draw the ratio plot
   h6->Draw("ep same");
   // h1 settings
   NJets_boosted->SetLineColor(kBlue+1);
   NJets_boosted->SetLineWidth(2);

   // Y axis h1 plot settings
   NJets_boosted->GetYaxis()->SetTitleSize(20);
   NJets_boosted->GetYaxis()->SetTitleFont(43);
   NJets_boosted->GetYaxis()->SetTitleOffset(1.55);

   // h2 settings
   NJets_boosted_btagged->SetLineColor(kRed);
   NJets_boosted_btagged->SetLineWidth(2);

   NJets_corrections_boosted->SetLineColor(kBlack);
   NJets_corrections_boosted->SetLineWidth(2);

   // Ratio plot (h3) settings
   h4->SetTitle(""); // Remove the ratio title

   // Y axis ratio plot settings
   h4->GetYaxis()->SetTitle("ratio");
   h4->GetYaxis()->SetNdivisions(505);
   h4->GetYaxis()->SetTitleSize(20);
   h4->GetYaxis()->SetTitleFont(43);
   h4->GetYaxis()->SetTitleOffset(1.55);
   h4->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h4->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   h4->GetXaxis()->SetTitle("NJets");
   h4->GetXaxis()->SetTitleSize(20);
   h4->GetXaxis()->SetTitleFont(43);
   h4->GetXaxis()->SetTitleOffset(1);
   h4->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h4->GetXaxis()->SetLabelSize(15);

   d->Print("d.pdf");

}


