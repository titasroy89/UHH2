#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Ac_Acceptance() 

{

    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root/AnalysisTree");
    TTree *treereco = (TTree*) chreco;

    Float_t bins_gen[] = {-2,-1.5,-1,-0.5,0,0.5,1,1.5,2};
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Mttbar_500 = new TH1F("Mttbar_500","",binnum_gen,bins_gen);
    TH1F *Mttbar_500to750 = new TH1F("Mttbar_500to750","",binnum_gen,bins_gen);
    TH1F *Mttbar_750to1000 = new TH1F("Mttbar_750to1000","",binnum_gen,bins_gen);
    TH1F *Mttbar_1000to1500 = new TH1F("Mttbar_1000to1500","",binnum_gen,bins_gen);
    TH1F *Mttbar_1500 = new TH1F("Mttbar_1500","",binnum_gen,bins_gen);
    TH1F *Mttbar_ALL = new TH1F("Mttbar_ALL","",binnum_gen,bins_gen);


    string Mass = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_eta[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_eta[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";
    string rap_diff = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    treereco->Project("Mttbar_500",rap_diff.c_str(),Form("(%s) <= 500",Mass.c_str()));
    treereco->Project("Mttbar_500to750",rap_diff.c_str(),Form("(%s) > 500 && (%s) <= 750",Mass.c_str(),Mass.c_str()));
    treereco->Project("Mttbar_750to1000",rap_diff.c_str(),Form("(%s) > 750 && (%s) <= 1000",Mass.c_str(),Mass.c_str()));
    treereco->Project("Mttbar_1000to1500",rap_diff.c_str(),Form("(%s) > 1000 && (%s) <= 1500",Mass.c_str(),Mass.c_str()));
    treereco->Project("Mttbar_1500",rap_diff.c_str(),Form("(%s) > 1500",Mass.c_str()));
    treereco->Project("Mttbar_ALL",rap_diff.c_str());

    TFile out("output/Acc_Acceptance.root","recreate");

    Mttbar_500->Write();
    Mttbar_500to750->Write();
    Mttbar_750to1000->Write();
    Mttbar_1000to1500->Write();
    Mttbar_1500->Write();
    Mttbar_ALL->Write();
   
    TChain *chreco_Visible = new TChain("AnalysisTree","");
    chreco_Visible->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullVisPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root/AnalysisTree");
    TTree *treereco_Visible = (TTree*) chreco_Visible;

    TH1F *Mttbar_500_Visible = new TH1F("Mttbar_500_Visible","",binnum_gen,bins_gen);
    TH1F *Mttbar_500to750_Visible = new TH1F("Mttbar_500to750_Visible","",binnum_gen,bins_gen);
    TH1F *Mttbar_750to1000_Visible = new TH1F("Mttbar_750to1000_Visible","",binnum_gen,bins_gen);
    TH1F *Mttbar_1000to1500_Visible = new TH1F("Mttbar_1000to1500_Visible","",binnum_gen,bins_gen);
    TH1F *Mttbar_1500_Visible = new TH1F("Mttbar_1500_Visible","",binnum_gen,bins_gen);
    TH1F *Mttbar_ALL_Visible = new TH1F("Mttbar_ALL_Visible","",binnum_gen,bins_gen);


    treereco_Visible->Project("Mttbar_500_Visible",rap_diff.c_str(),Form("(%s) <= 500",Mass.c_str()));
    treereco_Visible->Project("Mttbar_500to750_Visible",rap_diff.c_str(),Form("(%s) > 500 && (%s) <= 750",Mass.c_str(),Mass.c_str()));
    treereco_Visible->Project("Mttbar_750to1000_Visible",rap_diff.c_str(),Form("(%s) > 750 && (%s) <= 1000",Mass.c_str(),Mass.c_str()));
    treereco_Visible->Project("Mttbar_1000to1500_Visible",rap_diff.c_str(),Form("(%s) > 1000 && (%s) <= 1500",Mass.c_str(),Mass.c_str()));
    treereco_Visible->Project("Mttbar_1500_Visible",rap_diff.c_str(),Form("(%s) > 1500",Mass.c_str()));
    treereco_Visible->Project("Mttbar_ALL_Visible",rap_diff.c_str());

    Mttbar_500_Visible->Write();
    Mttbar_500to750_Visible->Write();
    Mttbar_750to1000_Visible->Write();
    Mttbar_1000to1500_Visible->Write();
    Mttbar_1500_Visible->Write();
    Mttbar_ALL_Visible->Write();


    TH1F *Acc_500_Visible = new TH1F("Acc_500_Visible","",binnum_gen,bins_gen);
    TH1F *Acc_500to750_Visible = new TH1F("Acc_500to750_Visible","",binnum_gen,bins_gen);
    TH1F *Acc_750to1000_Visible = new TH1F("Acc_750to1000_Visible","",binnum_gen,bins_gen);
    TH1F *Acc_1000to1500_Visible = new TH1F("Acc_1000to1500_Visible","",binnum_gen,bins_gen);
    TH1F *Acc_1500_Visible = new TH1F("Acc_1500_Visible","",binnum_gen,bins_gen);
    TH1F *Acc_ALL_Visible = new TH1F("Acc_ALL_Visible","",binnum_gen,bins_gen);

    for(int i=1;i<=binnum_gen;i++){
		Acc_500_Visible->SetBinContent(i,Mttbar_500_Visible->GetBinContent(i)/Mttbar_500->GetBinContent(i));
		Acc_500to750_Visible->SetBinContent(i,Mttbar_500to750_Visible->GetBinContent(i)/Mttbar_500to750->GetBinContent(i));
		Acc_750to1000_Visible->SetBinContent(i,Mttbar_750to1000_Visible->GetBinContent(i)/Mttbar_750to1000->GetBinContent(i));
		Acc_1000to1500_Visible->SetBinContent(i,Mttbar_1000to1500_Visible->GetBinContent(i)/Mttbar_1000to1500->GetBinContent(i));
		Acc_1500_Visible->SetBinContent(i,Mttbar_1500_Visible->GetBinContent(i)/Mttbar_1500->GetBinContent(i));
		Acc_ALL_Visible->SetBinContent(i,Mttbar_ALL_Visible->GetBinContent(i)/Mttbar_ALL->GetBinContent(i));
    } 

    Acc_500_Visible->Write();
    Acc_500to750_Visible->Write(); 
    Acc_750to1000_Visible->Write();
    Acc_1000to1500_Visible->Write();
    Acc_1500_Visible->Write();
    Acc_ALL_Visible->Write();


    TCanvas* f = new TCanvas("Response","Response",2000,1000);
    f->Divide(2,3);
    f->cd(1);

    Acc_500_Visible->GetXaxis()->SetTitle("#Delta |y|");
    Acc_500_Visible->GetYaxis()->SetTitle("Events");
    Acc_500_Visible->SetFillColor(kRed+1);
    Acc_500_Visible->SetMarkerStyle(33);
    Acc_500_Visible->SetMarkerSize(3);
    Acc_500_Visible->Draw();

    f->cd(2);
    Acc_750to1000_Visible->GetXaxis()->SetTitle("#Delta |y|");
    Acc_750to1000_Visible->GetYaxis()->SetTitle("Events");
    Acc_750to1000_Visible->SetFillColor(kRed+1);
    Acc_750to1000_Visible->SetMarkerStyle(33);
    Acc_750to1000_Visible->SetMarkerSize(3);
    Acc_750to1000_Visible->Draw();

    f->cd(3);
    Acc_500to750_Visible->GetXaxis()->SetTitle("#Delta |y|");
    Acc_500to750_Visible->GetYaxis()->SetTitle("Events");
    Acc_500to750_Visible->SetFillColor(kRed+1);
    Acc_500to750_Visible->SetMarkerStyle(33);
    Acc_500to750_Visible->SetMarkerSize(3);
    Acc_500to750_Visible->Draw();

    f->cd(4);
    Acc_1000to1500_Visible->GetXaxis()->SetTitle("#Delta |y|");
    Acc_1000to1500_Visible->GetYaxis()->SetTitle("Events");
    Acc_1000to1500_Visible->SetFillColor(kRed+1);
    Acc_1000to1500_Visible->SetMarkerStyle(33);
    Acc_1000to1500_Visible->SetMarkerSize(3);
    Acc_1000to1500_Visible->Draw();

    f->cd(5);
    Acc_1500_Visible->GetXaxis()->SetTitle("#Delta |y|");
    Acc_1500_Visible->GetYaxis()->SetTitle("Events");
    Acc_1500_Visible->SetFillColor(kRed+1);
    Acc_1500_Visible->SetMarkerStyle(33);
    Acc_1500_Visible->SetMarkerSize(3);
    Acc_1500_Visible->Draw();

    f->cd(6);
    Acc_ALL_Visible->GetXaxis()->SetTitle("#Delta |y|");
    Acc_ALL_Visible->GetYaxis()->SetTitle("Events");
    Acc_ALL_Visible->SetFillColor(kRed+1);
    Acc_ALL_Visible->SetMarkerStyle(33);
    Acc_ALL_Visible->SetMarkerSize(3);
    Acc_ALL_Visible->Draw();

    f->Print("Acceptance_Ac.pdf");
}
