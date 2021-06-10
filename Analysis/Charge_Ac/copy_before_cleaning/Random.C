
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
#include "sigma.h"
#include "mean.h"
void unfold_susan(Float_t maxi = 0.0)
{

      gStyle->SetOptStat(0);
      TFile* file = TFile::Open("Data_unfolding_6bins.root");
      TH2F *response = (TH2F*)file->Get("Smearing_Matrix_closure");
      TH1 *DeltaY = (TH1*)file->Get("DeltaY_rec_closure");
      TH1 *DeltaY_gen = (TH1*)file->Get("DeltaY_gen_closure");
      Int_t gen_bin = DeltaY_gen->GetNbinsX();



      TUnfoldDensity unfold(response,TUnfold::kHistMapOutputVert,
                                TUnfold::kRegModeCurvature,
                                TUnfold::kEConstraintArea,
                                TUnfoldDensity::kDensityModeBinWidth
                                );

      if(unfold.SetInput(DeltaY)>=10000) {
         std::cout<<"Unfolding histMunfold may be wrong\n";
      }

      for(int bb=0;bb<1000;bb++){
        TH1F *Bias = new TH1F("Bias","",newrec,new_rec);
        Bias->FillRandom(DeltaY,Integral);
        if(unfold.SetInput(Bias)>=10000) {
           std::cout<<"Unfolding histMunfold may be wrong\n";
        }

}
