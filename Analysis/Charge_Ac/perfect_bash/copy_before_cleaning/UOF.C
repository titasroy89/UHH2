
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void UOF(Int_t max = 2) 

{

    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection/ptmuon50/uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*) chreco;

    cout << treereco->GetEntries() << endl;

    Float_t bins_gen[] = {-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.};
    Float_t bins_rec[] = {-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.};
    Float_t new_rec[] = {-2.,-1.5,-1.25,-1.,-0.75,-0.5,-0.25,0.,0.25,0.5,0.75,1.,1.25,1.5,2.};

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    Int_t  binnum_rec = sizeof(bins_rec)/sizeof(Float_t) - 1;

//For closure test

    TH1F *DeltaY_rec = new TH1F("DeltaY_rec","",newrec,new_rec);
    TH1F *DeltaY_gen = new TH1F("DeltaY_gen","",newrec,new_rec);
    TH2F *Smearing_Matrix_test = new TH2F("Smearing_Matrix_test","",newrec,new_rec,newrec,new_rec);

    string rap_diff = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

//Llenando histogramas para closure test

//    treereco->Project("Smearing_Matrix_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",1,0);
    treereco->Project("Smearing_Matrix_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),"DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",1,0);
    treereco->Project("DeltaY_gen",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",1,0);
    treereco->Project("DeltaY_rec",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",1,0);

    auto DeltaY_gen_closure = (TH1*) Smearing_Matrix_test->ProjectionY("DeltaY_gen_closure",1,newrec);
    auto DeltaY_rec_closure = (TH1*) Smearing_Matrix_test->ProjectionX("DeltaY_rec_closure",1,newrec);

    TFile out("UOF.root","recreate");

    Smearing_Matrix_test->Write();
    DeltaY_rec_closure->Write();
    DeltaY_rec->Write();
    DeltaY_gen_closure->Write();
    DeltaY_gen->Write();

}

