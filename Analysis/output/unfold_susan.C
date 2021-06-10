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
//#include "sigma.h"
//#include "mean.h"
void unfold_susan()
{
      gStyle->SetOptStat(0);
      TFile* file = TFile::Open("Data_unfolding_6bins.root");
      TH2F *response = (TH2F*)file->Get("Migration_Matrix_closure");
      TH1 *Mttbar = (TH1*)file->Get("Mttbar_rec_closure");
      TH1 *Mttbar_gen = (TH1*)file->Get("Mttbar_gen_closure");
//      Mttbar->GetYaxis()->SetRangeUser(0,10000);
      Int_t gen_bin = Mttbar_gen->GetNbinsX();

      TUnfoldDensity unfold(response,TUnfold::kHistMapOutputVert,
                                TUnfold::kRegModeCurvature,
                                TUnfold::kEConstraintArea,
                                TUnfoldDensity::kDensityModeBinWidth
                                );

      if(unfold.SetInput(Mttbar)>=10000) {
         std::cout<<"Unfolding histMunfold may be wrong\n";
      }

      cout << gen_bin << endl;
//minimization based on Rho
      Int_t nScan1 = 1000;
      double logtaustart = -6.;
      Double_t tauMinOpt=1;
      Double_t rhoAvgMinOpt=999;
      Double_t RhoAvg[nScan1];
      Double_t lg10tau[nScan1];

      TH1D *Rhoi_rebinnedA = new TH1D("Rhoi_rebinnedA","Rhoi_rebinnedA",gen_bin,0,gen_bin);
      for (Int_t i=0;i<nScan1;i++) {
           Double_t logtau = logtaustart*(1.-i/double(nScan1-1));
           Double_t tauReg=TMath::Power(10,logtau);
           unfold.DoUnfold(tauReg);
           unfold.GetRhoI(Rhoi_rebinnedA,0);
           double rhoaverage = Rhoi_rebinnedA->Integral()/7;
           RhoAvg[i] = rhoaverage;
           lg10tau[i] = tauReg;
           if(rhoaverage>0 && rhoaverage<rhoAvgMinOpt){
               rhoAvgMinOpt = rhoaverage;
               tauMinOpt = tauReg;
           }
//           cout << tauMinOpt << endl;
      }

      Double_t Vec_Rho_min[1] = {rhoAvgMinOpt};
      Double_t Vec_tau_min[1] = {tauMinOpt};

      TGraph *RhoAvg_plot = new TGraph(nScan1,lg10tau,RhoAvg);
      TGraph *Minimum = new TGraph(1,Vec_tau_min,Vec_Rho_min);
      TCanvas *c = new TCanvas("c","C");
      c->Divide(2,1);
      c->cd(1);
      RhoAvg_plot->SetTitle("Correlation Coefficients");
      RhoAvg_plot->GetXaxis()->SetTitle("#tau");
      RhoAvg_plot->GetYaxis()->SetTitle("#rho_{avg}");
      RhoAvg_plot->Draw("aLp");
      gPad->SetLogx();
      c->Update();
      Minimum->SetMarkerStyle(23);
      Minimum->SetMarkerColor(2);
      Minimum->Draw("psame");

//minimization based on L curve

  Double_t tauMin=0.0;
  Double_t tauMax=0.0;
  Int_t nScan=100;
  Int_t iBest;
  TSpline *logTauX,*logTauY;
  TGraph *lCurve;
  // this method scans the parameter tau and finds the kink in the L curve
  // finally, the unfolding is done for the "best" choice of tau
  iBest=unfold.ScanLcurve(nScan,tauMin,tauMax,&lCurve,&logTauX,&logTauY);
  std::cout<<"tau_l="<<unfold.GetTau()<<"\n";
//  std::cout<<"chi**2="<<unfold.GetChi2A()<<"+"<<unfold.GetChi2L()
//           <<" / "<<unfold.GetNdf()<<"\n";
  std::cout << "tau_rho: " << tauMinOpt << endl;
  Double_t tauMinL = unfold.GetTau();
  Double_t t[1],x[1],y[1];
  logTauX->GetKnot(iBest,t[0],x[0]);
  logTauY->GetKnot(iBest,t[0],y[0]);
  TGraph *bestLcurve=new TGraph(1,x,y);
  c->cd(2);
  lCurve->GetXaxis()->SetTitle("log_{10}(#it{L_{1}})");
  lCurve->GetYaxis()->SetTitle("log_{10}(#it{L_{2}/#tau^{2}})");
  lCurve->Draw("AL");
  bestLcurve->SetMarkerColor(kRed);
  bestLcurve->Draw("*");

  c->Print("Rho.pdf");

  unfold.DoUnfold(tauMinOpt);
  TH1 *histMunfold = unfold.GetOutput("Unfolded");
  histMunfold->Sumw2();

  TH2 *Ematrix_Input = unfold.GetEmatrixInput("Ematrix_Input");
  TH2 *Ematrix_Response =  unfold.GetEmatrixSysUncorr("Ematrix_Response");
  TH2 *Ematrix_Total = unfold.GetEmatrixTotal("Ematrix_Total");

  TH1 *tem =  (TH1*) histMunfold->Clone("tem");
  tem->Reset();

  TH1 *inputUnc =  (TH1*) tem->Clone("input");
  TH1 *matrixUnc =  (TH1*) tem->Clone("matrixUnc");
  TH1 *totUnc =  (TH1*) tem->Clone("totUnc");

      for (int i=1;i <= tem->GetNbinsX()+1;i++) {
      inputUnc->SetBinContent(i,sqrt(Ematrix_Input->GetBinContent(i,i))/histMunfold->GetBinContent(i));
      matrixUnc->SetBinContent(i,sqrt(Ematrix_Response->GetBinContent(i,i))/histMunfold->GetBinContent(i));
      totUnc->SetBinContent(i,sqrt(Ematrix_Total->GetBinContent(i,i))/histMunfold->GetBinContent(i));
      }

      TCanvas *Unc = new TCanvas("Unc","Unc");
      Unc->SetTopMargin(0.08);
      Unc->SetRightMargin(0.05);
      Unc->SetBottomMargin(0.14);
      Unc->SetLeftMargin(0.16);

      totUnc->GetXaxis()->SetTitle("Mttbar [GeV]");
      totUnc->GetYaxis()->SetTitle("Uncertainty [%]");
      totUnc->GetYaxis()->SetRangeUser(0.0,50.0);


      Unc->cd();

      totUnc->SetFillColor(17);
      totUnc->SetFillStyle(3344);
      totUnc->SetLineColor(16);
      totUnc->SetLineWidth(2);

      inputUnc->SetLineColor(1);
      inputUnc->SetLineWidth(2);
      inputUnc->SetMarkerColor(1);
      inputUnc->SetMarkerStyle(20);

      matrixUnc->SetLineColor(2);
      matrixUnc->SetLineWidth(2);
      matrixUnc->SetMarkerColor(2);
      matrixUnc->SetMarkerStyle(34);

      auto leg2 = new TLegend(0.2,0.39,0.45,0.88);
      leg2->AddEntry(totUnc,   "Total uncertainty","f");
      leg2->AddEntry(inputUnc, "Input stat. unc.","lp");
      leg2->AddEntry(matrixUnc,"Matrix stat. unc.","lp");

      leg2->SetFillStyle(0);
      leg2->SetBorderSize(0);
      leg2->SetTextSize(0.04);
      leg2->SetTextFont(42);

      totUnc->Draw("hist");
      inputUnc->Draw("ep,same");
      matrixUnc->Draw("ep,same");

      leg2->Draw();

      Unc->Draw();
      Unc->Print("Unc.pdf");

//Closure_test

      TH1 *ratio =  (TH1*) Mttbar_gen->Clone("ratio");
      ratio->SetName("ratio");
      ratio->GetXaxis()->SetTitle("Mttbar [GeV]");
      ratio->GetYaxis()->SetTitle("MC/Data");
      ratio->Divide(histMunfold);


      // Convert total, statistical uncertainty into error bands

      for (int i = 1; i <= Mttbar_gen->GetNbinsX()+1;i++) {
          totUnc->SetBinError(i,totUnc->GetBinContent(i));
          totUnc->SetBinContent(i,1.0);
          inputUnc->SetBinError(i,inputUnc->GetBinContent(i));
          inputUnc->SetBinContent(i,1.0);
      }

      totUnc->SetMarkerSize(0);
      totUnc->SetLineColor(0);
      totUnc->SetFillColor(860-9);
      totUnc->SetFillStyle(1001);

      inputUnc->SetMarkerSize(0);
      inputUnc->SetLineColor(0);
      inputUnc->SetFillColor(18);
      inputUnc->SetFillStyle(1001);

      // Plot

      TCanvas *c4 = new TCanvas("c4","c4");
      auto pad1 =  new TPad("pad1","pad1",0,0.3,1,1);
      pad1->SetBottomMargin(0.05);
      pad1->Draw();
      pad1->cd();

      histMunfold->SetMarkerStyle(21);
      Mttbar->SetMarkerStyle(25);
      Mttbar_gen->SetLineColor(4);
      Mttbar_gen->GetYaxis()->SetTitleSize(25);
      Mttbar_gen->GetXaxis()->SetLabelSize(0);

      histMunfold->SetTitle(";;Events");
      histMunfold->GetYaxis()->SetTitleOffset(1.2);
      histMunfold->SetMinimum(0.0);
      histMunfold->SetAxisRange(0,max(Mttbar_gen->GetMaximum(),histMunfold->GetMaximum())*1.15,"Y");
      histMunfold->Draw();
      Mttbar_gen->Draw("histsame");
      Mttbar->Draw("same");

      auto leg4 = new TLegend(0.5, 0.5, 0.9, 0.75);
      leg4->SetFillStyle(0);
      leg4->SetTextFont(42);
      leg4->SetTextSize(0.045);
      leg4->SetBorderSize(0);

      leg4->AddEntry(histMunfold,"Unfolded data","p");
      leg4->AddEntry(Mttbar_gen, "Generator prediction","l");
      leg4->AddEntry(Mttbar, "Reconstructed events","p");
//	leg4.AddEntry(inputUnc, "Stat. uncertainty","f");
//	leg4.AddEntry(totUnc, "Stat. #oplus syst. uncertainties","f");
      leg4->Draw();


      c4->cd();
      auto pad2 = new TPad("pad2","pad2",0,0.0,1,0.28);
      pad2->SetTopMargin(0.05);
      pad2->SetBottomMargin(0.3);
      pad2->Draw();

      pad2->cd();
      pad2->SetGridy();

      ratio->SetMaximum(1.5);
      ratio->SetMinimum(0.5);
      ratio->UseCurrentStyle();
//	ratio->GetYaxis()->SetTitleSize(100);
      ratio->GetYaxis()->SetTitleOffset(1.0);
      ratio->GetXaxis()->SetTitleOffset(1.0);
      ratio->GetXaxis()->SetLabelSize(50);
      ratio->GetYaxis()->SetNdivisions(4,4,0,"False");
      ratio->Draw("hist");
//	totUnc->Draw("samee2");
//	inputUnc->Draw("samee2");
//	ratio->Draw("samehist");

      c4->Update();
      c4->Draw();
      c4->Print("Closure.pdf");


// Closure Test LCurve_min

      TH2D *Ematrix_L = new TH2D("Ematrix_L","Covariance Matrix",6,0,6,6,0,6);
      unfold.DoUnfold(tauMinL);
      unfold.GetEmatrix(Ematrix_L,0);
      TCanvas *EL = new TCanvas("EL","EL");
      Ematrix_L->Draw("COLZ");
      EL->Print("Error_Matrix_(Lscan).pdf");

      TCanvas *C2 = new TCanvas("C2","C2");
      TH1 *histMunfold_L = unfold.GetOutput("Unfolded_L");
      TPad *pad1_L = new TPad("pad1_L", "pad1_L", 0, 0.3, 1, 1.0);
      pad1_L->SetBottomMargin(5);
      pad1_L->SetGridx();
      pad1_L->Draw();
      pad1_L->cd();

      histMunfold_L->SetLineColor(1);
      histMunfold_L->SetMarkerStyle(21);
      histMunfold_L->GetYaxis()->SetTitle("Events");
      histMunfold_L->SetTitle("");
      for (Int_t cmi = 0; cmi < 6; cmi++) {

           histMunfold_L->SetBinError(cmi + 1, sqrt( Ematrix_L->GetBinContent(cmi + 1, cmi + 1) ) );
      }
      histMunfold_L->GetXaxis()->SetRange(0, histMunfold_L->GetNbinsX() + 1);
      histMunfold_L->Draw("pE");
      Mttbar_gen->SetLineColor(2);
      Mttbar_gen->Draw("same");
      Mttbar->SetLineColor(4);
      Mttbar->Draw("same");
      TLegend leg_L(.5, .7, .8, .9, "");
      leg_L.SetFillColor(0);
      leg_L.AddEntry(Mttbar_gen, "Mttbar_gen");
      leg_L.AddEntry(histMunfold_L, "histMunfold");
      leg_L.AddEntry(Mttbar,"Mttbar");
      leg_L.Draw("Same");

      C2->cd();
      TPad *pad2_L = new TPad("pad2_L", "pad2_L", 0, 0.05, 1, 0.3);
      pad2_L->SetTopMargin(5);
      pad2_L->SetBottomMargin(0.9);
      pad2_L->SetGridx();
      pad2_L->Draw();
      pad2_L->cd();

      TH1F *Ratio_L = (TH1F*) histMunfold_L->Clone();
      Ratio_L->Divide(Mttbar_gen);
      Ratio_L->GetYaxis()->SetRangeUser(0.5,1.5);
      Ratio_L->GetYaxis()->SetNdivisions(5,5,0);
      Ratio_L->GetYaxis()->SetLabelSize(0.07);
      Ratio_L->GetYaxis()->SetTitleOffset(0.4);
      Ratio_L->GetYaxis()->SetTitleSize(0.1);
      Ratio_L->GetYaxis()->SetTitle("Unfolded/True");
      Ratio_L->GetXaxis()->SetTitleSize(0.12);
      Ratio_L->GetXaxis()->SetTitleOffset(0.2);
      Ratio_L->GetXaxis()->SetTitle("");
      Ratio_L->SetMarkerStyle(1);
      Ratio_L->SetTitle("");
      Ratio_L->Draw("le");
      C2->Print("Closure_test_L.pdf");


}
