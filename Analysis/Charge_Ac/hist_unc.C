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
#include "sigma.h"
#include "mean.h"
#include "TRandom3.h"

void hist_unc(string var_name = "")

{

   TFile* file = TFile::Open("root/Input_undfolding_data_.root");
   TH1 *nominal = (TH2*)file->Get("TTbar");
   TH1 *up = (TH1*)file->Get(Form("%s_up",var_name.c_str()));
   TH1 *down = (TH1*)file->Get(Form("%s_down",var_name.c_str()));

   auto C = new TCanvas();
 
   gStyle->SetOptTitle(kFALSE);
   gStyle->SetOptStat(0);
  
   nominal->SetMarkerStyle(kFullCircle);
   up->SetMarkerStyle(kFullSquare);
   down->SetMarkerStyle(kFullTriangleUp);

   nominal->SetTitle(var_name.c_str());
   nominal->GetXaxis()->SetTitle("DeltaY");
   nominal->GetYaxis()->SetTitle("Events");  

   nominal->Draw("PLC PMC");
   up->Draw("SAME PLC PMC");
   down->Draw("SAME PLC PMC");
 
   gPad->BuildLegend();

   C->Print(Form("%s.pdf",var_name.c_str()));

   


}

