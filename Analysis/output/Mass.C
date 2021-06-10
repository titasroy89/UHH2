
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
#include <TROOT.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TRandom.h"
#include "TUnfoldDensity.h"

using namespace RooFit ;

void Mass() 

{
    gStyle->SetOptStat(0);
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection//uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*) chreco;

    TChain *chreco1 = new TChain("AnalysisTree","");
    chreco1->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3_350GeV.root/AnalysisTree");
    TTree *treereco1 = (TTree*) chreco1;

    TChain *chreco2 = new TChain("AnalysisTree","");
    chreco2->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3_350GeV.root");
    TTree *treereco2 = (TTree*) chreco2;

    Float_t bins_gen[] = {300,950,1400,1800,2600,4000};
    Float_t bins_rec[] = {300,950,1400,1800,2600,4000};
    Float_t new_rec[] = {300,625,950,1175,1400,1600,1800,2200,2600,3300,4000};

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    Int_t  binnum_rec = sizeof(bins_rec)/sizeof(Float_t) - 1;

//For closure test

    TH1F *Mttbar_rec_closure = new TH1F("Mttbar_rec_closure","",newrec,new_rec);
    TH1F *Mttbar_gen_closure = new TH1F("Mttbar_gen_closure","",binnum_gen,bins_gen);
    TH2F *Smearing_Matrix_closure = new TH2F("Smearing_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Migration_Matrix_closure = new TH2F("Migration_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);

//optimization
    TH1F *Mttbar_FullPS = new TH1F("Mttbar_FullPS","",binnum_rec,bins_rec);
    TH2F *Smearing_Matrix = new TH2F("Smearing_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *Mttbar_rec = new TH1F("Mttbar_rec","",binnum_rec,bins_rec);
    TH1F *Mttbar_gen_rec = new TH1F("Mttbar_gen_rec","",binnum_rec,bins_rec);
    TH1F *Mttbar_Visgen = new TH1F("Mttbar_Visgen","",binnum_rec,bins_rec);
    TH1F *Eff_Vis = new TH1F("Eff_Vis","",binnum_rec,bins_rec);
    TH1F *Acceptance = new TH1F("Acceptance","",binnum_rec,bins_rec);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Response_Matrix = new TH2F("Response_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","Transition Probability",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *EfficiencyxAcceptance = new TH1F("Efficiency*Acceptance","",binnum_rec,bins_rec);
    TH1F *Stability = new TH1F("Stability","",binnum_rec,bins_rec);
    TH1F *Purity = new TH1F("Purity","",binnum_rec,bins_rec);

    treereco1->Project("Mttbar_FullPS","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Mttbar_gen_rec","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Mttbar_rec","Mttbar");
    treereco2->Project("Mttbar_Visgen","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Smearing_Matrix","Mttbar:TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");

//Llenando histogramas para closure test
     
    treereco->Project("Smearing_Matrix_closure","Mttbar:TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))","","",5925,17776);   
    treereco->Project("Mttbar_gen_closure","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))","","",17775,1);
    treereco->Project("Mttbar_rec_closure","Mttbar","","",17775,1);

    for (int i=1;i<=5;i++){
	Eff_Vis->SetBinContent(i,Mttbar_rec->GetBinContent(i)/Mttbar_Visgen->GetBinContent(i));
        Acceptance->SetBinContent(i,Mttbar_Visgen->GetBinContent(i)/Mttbar_FullPS->GetBinContent(i));
    }
   
    for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
        Response_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Mttbar_Visgen->GetBinContent(b));
        Migration_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Smearing_Matrix->Integral(1,binnum_gen,b,b));

        //solo los elementos en la diagonal importan
        Purity_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Smearing_Matrix->Integral(a,a,1,binnum_gen));

       }
    }

   //fill migration matrix for colsure

    for(int a=1;a<=newrec;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
        Migration_Matrix_closure->SetBinContent(a,b,Smearing_Matrix_closure->GetBinContent(a,b)/Smearing_Matrix_closure->Integral(1,newrec,b,b));
       }
    }

   // Purity && Stability
    for(Int_t m=1;m<=binnum_gen;m++){
         Stability->SetBinContent(m,Migration_Matrix->GetBinContent(m,m));
         Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
         EfficiencyxAcceptance->SetBinContent(m,Eff_Vis->GetBinContent(m)*Acceptance->GetBinContent(m));
    }

    Purity->GetYaxis()->SetRangeUser(0,1.1);
    Purity->GetXaxis()->SetTitle("Mttbar [GeV]");
    Purity->SetLineColor(kRed);
    Purity->SetLineWidth(3);
    Stability->SetLineColor(kBlue);
    Stability->SetLineWidth(3);
    Eff_Vis->SetLineColor(kGreen+1);
    Eff_Vis->SetLineStyle(9);
    Eff_Vis->SetLineWidth(3);
    Acceptance->SetLineColor(kViolet);    
    Acceptance->SetLineStyle(9);
    Acceptance->SetLineWidth(3);

    TFile out("Data_unfolding.root","recreate");
    Mttbar_rec_closure->Write();
    Mttbar_gen_closure->Write();
    Migration_Matrix_closure->Write();
    Mttbar_rec->Write();
    Mttbar_gen_rec->Write();
    Mttbar_Visgen->Write();
    Eff_Vis->Write();
    Acceptance->Write();
    Smearing_Matrix->Write();
    Purity_Matrix->Write();
    Migration_Matrix->Write();
    Response_Matrix->Write();
    Stability->Write();
    Purity->Write();
    EfficiencyxAcceptance->Write();

    TCanvas* cc = new TCanvas("cc","cc",2400,1200);
    
    cc->Divide(1,1);
    cc->cd(1);
 
    Purity->Draw();
    Stability->Draw("same");   
    Acceptance->Draw("same");
    Eff_Vis->Draw("same");
    TLegend leg(.65, .65, .85, .85, "");
    leg.SetFillColor(0); 
    leg.AddEntry(Purity, "Purity");
    leg.AddEntry(Stability, "Stability");
    leg.AddEntry(Eff_Vis,"Eff_Vis");
    leg.AddEntry(Acceptance,"Acceptance");
    leg.SetBorderSize(0);
    leg.Draw("Same");

    TLegend leg2(.15, .75, .35, .85, "");
    leg2.AddEntry((TObject*)0, "#mu + jets", "");
    leg2.SetBorderSize(0);
    leg2.Draw("same");

    cc->Print("P&S.pdf");

    TCanvas* dd = new TCanvas("dd","dd",2400,1200);
    dd->Divide(1,1);
    dd->cd(1);

    Migration_Matrix->GetXaxis()->SetTitle("Mttbar_rec [GeV]");
    Migration_Matrix->GetYaxis()->SetTitle("Mttbar_gen [GeV]"); 
    Migration_Matrix->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix->Draw("text colz");
    dd->Print("Migration_Matrix.pdf");


    TCanvas* ee = new TCanvas("ee","ee",2400,1200);
    ee->Divide(1,1);
    ee->cd(1);

    Migration_Matrix_closure->GetXaxis()->SetTitle("Mttbar_rec [GeV]");
    Migration_Matrix_closure->GetYaxis()->SetTitle("Mttbar_gen [GeV]");	
    Migration_Matrix_closure->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix_closure->Draw("text colz");
    ee->Print("Closure_Matrix.pdf");

}  


/*
    Int_t nentries = treereco->GetEntries();
    TH1F *hpx   = new TH1F("hpx","px distribution",100,0,1000);
    Float_t Hola;
    treereco->SetBranchAddress("GenParticles.m_pt[2]",&Hola);
    for(Long64_t t=0;t<nentries;t++){
    treereco->GetEntry(t);
    hpx->Fill(Hola);
    }
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_muon/");
    TTree *treereco = (TTree*) chreco;
    Float_t bins_gen[] = {350,820,1158,1660,2350,3955};
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    TH1F *hb0 = new TH1F("hb0","",binnum_gen,bins_gen);
    TH1F *hb2 = new TH1F("hb2","top",50,0,300);
    TH1F *hb3 = new TH1F("hb3","antitop",50,0,300);
    treereco->Project("hb2","TMath::Sqrt(GenParticles.m_energy[2]*GenParticles.m_energy[2] - GenParticles.m_pt[2]*GenParticles.m_pt[2]*TMath::CosH(GenParticles.m_eta[2])*TMath::CosH(GenParticles.m_eta[2]))");
    treereco->Project("hb3","TMath::Sqrt(GenParticles.m_energy[3]*GenParticles.m_energy[3] - GenParticles.m_pt[3]*GenParticles.m_pt[3]*TMath::CosH(GenParticles.m_eta[3])*TMath::CosH(GenParticles.m_eta[3]))");
// Variables
//  Px_1 + Px_2 = GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3])
//  Py_1 + Py_2 = GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3])
//  Pz_1 + Pz_2 = GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_phi[3])
//  E_1 + E_2 = GenParticles.m_energy[2] + GenParticles.m_energy[3]
    treereco->Project("hb0","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
*/   
//    TFile out("out_Visible_O7.root","recreate");
//      hpx->Write();
//    hb2->Write();
//    hb3->Write();
//    hb0->Write();
//}
/*
    TFile *f = new TFile("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection//uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*)f->Get("AnalysisTree");
    treereco->SetMakeClass(1);
    Int_t ntracks;
    Float_t pt[1000];
    TBranch *bntrack = treereco->GetBranch("GenParticles");
    TBranch *bpx = treereco->GetBranch("GenParticles.m_pt");
    bntrack->SetAddress(&ntracks);
    bpx->SetAddress(pt);
    Int_t nevent = (Int_t)treereco->GetEntries();
    for(Int_t i=0;i<nevent;i++){
//	 bntrack->GetEntry(i);
       bpx->GetEntry(i);
       cout << pt[2] << endl;
    }
*/
