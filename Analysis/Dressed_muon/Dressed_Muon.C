#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Dressed_Muon() 

{
    TFile *f = new TFile("/nfs/dust/cms/user/hugobg/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root");
    TTree *treereco = (TTree*)f->Get("AnalysisTree");
    treereco->SetMakeClass(1);
    Int_t ntracks;
    TBranch *bntrack = treereco->GetBranch("GenParticles");
    bntrack->SetAddress(&ntracks);
    
    Float_t pt[404];
    Float_t eta[404];
    Float_t phi[404];
    Float_t energy[404];
    Int_t pdgId[404];
    Short_t index[404];
    UShort_t madre1[404];
    UShort_t madre2[404];
    UShort_t hija1[404];
    UShort_t hija2[404];
    
    TBranch *bpt = treereco->GetBranch("GenParticles.m_pt");
    TBranch *beta = treereco->GetBranch("GenParticles.m_eta");
    TBranch *bphi = treereco->GetBranch("GenParticles.m_phi");
    TBranch *benergy = treereco->GetBranch("GenParticles.m_energy");
    TBranch *bpdgId = treereco->GetBranch("GenParticles.m_pdgId");
    TBranch *bindex = treereco->GetBranch("GenParticles.m_index");
    TBranch *bmadre1 = treereco->GetBranch("GenParticles.m_mother1");
    TBranch *bmadre2 = treereco->GetBranch("GenParticles.m_mother2");
    TBranch *bhija1 = treereco->GetBranch("GenParticles.m_daughter1");
    TBranch *bhija2 = treereco->GetBranch("GenParticles.m_daughter2");
    
    bpt->SetAddress(pt);
    beta->SetAddress(eta);
    bphi->SetAddress(phi);
    benergy->SetAddress(energy);
    bpdgId->SetAddress(pdgId);
    bindex->SetAddress(index);
    bmadre1->SetAddress(madre1);
    bmadre2->SetAddress(madre2);
    bhija1->SetAddress(hija1);
    bhija2->SetAddress(hija2);
    
    Int_t nevent = (Int_t)treereco->GetEntries();

// loop para os eventos
    for(Int_t i=0;i<1;i++){
        bpt->GetEntry(i);
        beta->GetEntry(i);
        bphi->GetEntry(i);
        benergy->GetEntry(i);
        bpdgId->GetEntry(i);
        bindex->GetEntry(i);
        bmadre1->GetEntry(i);
        bmadre2->GetEntry(i);
        bhija1->GetEntry(i);
        bhija2->GetEntry(i);
        Int_t size (sizeof(pt)/sizeof(*pt));
        cout << size << endl;
        cout << "#########" << "Event : " << i << "############" << endl;
//       loop para todos las particulas en el evento
        for(Int_t j=0;j<size;j++){
           if ( abs(pdgId[j]) ==6 ){
           // j es el indice donde hay un top(antitop)
           //cout << "soy un top" << endl;
               Int_t W = (Int_t)hija1[j];
               Int_t b = (Int_t)hija2[j];
               
               if (abs(pdgId[W]) == 5 && abs(pdgId[b]) == 24){
                    b = (Int_t)hija1[j];
                    W = (Int_t)hija2[j];
               }
               
               if (abs(pdgId[W]) != 24){
                 
                   
                   
                   
                   
                   
               }
               
               
               
               
               
               
               
           }
           
         }

    }




}
