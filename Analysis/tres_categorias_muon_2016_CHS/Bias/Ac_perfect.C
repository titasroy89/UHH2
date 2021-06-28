
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Ac_perfect(string pdf_name, Int_t max = 0) 

{

    gStyle->SetOptStat(0);
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2016_CHS/muon/all/uhh2.AnalysisModuleRunner.MC.TTToS*.root");
    TTree *treereco = (TTree*) chreco;

    cout << treereco->GetEntries() << endl;

    //Rapidity
    Float_t bins_gen[] = {-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.};
    Float_t bins_rec[] = {-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.};
    Float_t new_rec[] = {-2.,-1.5,-1.25,-1.,-0.75,-0.5,-0.25,0.,0.25,0.5,0.75,1.,1.25,1.5,2.};

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    Int_t  binnum_rec = sizeof(bins_rec)/sizeof(Float_t) - 1;


//For closure test


//rapidity
    TH1F *DeltaY_rec_closure = new TH1F("DeltaY_rec_closure","",newrec,new_rec);
    TH1F *DeltaY_gen_closure = new TH1F("DeltaY_gen_closure","",binnum_gen,bins_gen);
    TH2F *Smearing_Matrix_closure = new TH2F("Smearing_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);

    string rap_diff = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

//Llenando histogramas para closure test


//rapidity
    treereco->Project("Smearing_Matrix_closure",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),"DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",500000,1);
    treereco->Project("DeltaY_gen_closure",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",500000,500001);
    treereco->Project("DeltaY_rec_closure",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",500000,500001);

    TFile out("Data_unfolding_.root","recreate");
    DeltaY_rec_closure->Write();
    DeltaY_gen_closure->Write();
    Smearing_Matrix_closure->Write();


}

