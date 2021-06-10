\
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Extract(Float_t max = 0.0) 

{

    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection//uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*) chreco;

    cout << treereco->GetEntries() << endl;

//Copiando de aqui para 7 bins

    Float_t bins_gen[] = {880,1064,1298,1502,1800,2200,3000,7000};
    Float_t bins_rec[] = {880,1064,1298,1502,1800,2200,3000,7000};
    Float_t new_rec[] = {880,978,1064,1208,1298,1382,1502,1676,1800,2050,2200,2600,3000,4300,7000};

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    Int_t  binnum_rec = sizeof(bins_rec)/sizeof(Float_t) - 1;

//For closure test

    TH2F *Smearing_Matrix_closure = new TH2F("Smearing_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Closure_Matrix = new TH2F("Closure_Matrix","",newrec,new_rec,binnum_rec,bins_rec);
    TH1F *Mttbar = new TH1F("Mttbar","",10,0,7000);

//    treereco->Project("Smearing_Matrix_closure","TMath::Max(Mttbar,900):TMath::Max(900,TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2)));  
//    treereco->Project("Smearing_Matrix_closure","Mttbar:TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Smearing_Matrix_closure","TMath::Max(900,Mttbar):TMath::Max(Mttbar,900)");
    treereco->Project("Mttbar","Mttbar");


    TH1D *Mttbar_gen_closure = Smearing_Matrix_closure->ProjectionY("Mttbar_gen_closure", 1, 16);
    TH1D *Mttbar_rec_closure = Smearing_Matrix_closure->ProjectionY("Mttbar_rec_closure", 0, 16);

    TFile out("UOB.root","recreate");
    Smearing_Matrix_closure->Write();
    Mttbar_gen_closure->Write();
    Mttbar_rec_closure->Write();
    Mttbar->Write();

    cout << Mttbar->GetBinContent(0) << endl;
}



