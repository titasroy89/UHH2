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
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"

void Gen_Ac()
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
//    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/presel_output/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root/AnalysisTree");
    chreco_ttbar->Add("/pnfs/desy.de/cms/tier2/store/user/akaravdi/RunII_102X_v1_TEST/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/crab_TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/190327_085021/0000/Ntuple_1*.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

//array for variable 

    Float_t bins_gen[] = {-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.};

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Var_gen = new TH1F("Var_gen","",binnum_gen,bins_gen);

    string InvMass = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";

    string var_gen = "";
    var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    treereco_ttbar->Project("Var_gen",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),Form("%s >= 0  && %s < 500",InvMass.c_str(),InvMass.c_str())); 

    for(int i=1;i<=binnum_gen;i++){
         cout << Var_gen->GetBinContent(i) << endl; //     " << Var_gen->GetBinError(i) << endl;
    }


}
 
