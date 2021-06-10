
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

void unfold_susan(Float_t maxi = 0.0)
{
      if(gRandom) delete gRandom;
      gRandom = new TRandom3(0);
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

      cout << gen_bin << endl;
//minimization based on Rho
      Int_t nScan1 = 100;
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
           double rhoaverage = Rhoi_rebinnedA->Integral()/8;
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

  tauMinOpt = 1;
   
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

      totUnc->GetXaxis()->SetTitle("DeltaY [GeV]");
      totUnc->GetYaxis()->SetTitle("Uncertainty [%]");
      totUnc->GetYaxis()->SetRangeUser(0.0,1.0);


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

      for(int i=1;i<=histMunfold->GetNbinsX();i++){
        cout << totUnc->GetBinContent(i) << endl;
        histMunfold->SetBinError(i,histMunfold->GetBinContent(i)*totUnc->GetBinContent(i));
      }


      TH1 *ratio =  (TH1*) DeltaY_gen->Clone("ratio");
      ratio->SetName("ratio");
      ratio->GetXaxis()->SetTitle("DeltaY [GeV]");
      ratio->GetYaxis()->SetTitle("MC/Data");
      ratio->Divide(histMunfold);
      for(int jj =1;jj<8;jj++){
      cout << ratio->GetBinContent(jj) << " ";
      }
      cout << "" << endl;

      // Convert total, statistical uncertainty into error bands

      for (int i = 1; i <= DeltaY_gen->GetNbinsX()+1;i++) {
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
      DeltaY->SetMarkerStyle(25);
      DeltaY_gen->SetLineColor(4);
      DeltaY_gen->GetYaxis()->SetTitleSize(25);
      DeltaY_gen->GetXaxis()->SetLabelSize(0);

      histMunfold->SetTitle(";;Events");
      histMunfold->GetYaxis()->SetTitleOffset(1.2);
      histMunfold->SetMinimum(0.0);
      histMunfold->SetAxisRange(0,max(DeltaY_gen->GetMaximum(),histMunfold->GetMaximum())*1.15,"Y");
      histMunfold->Draw();
      DeltaY_gen->Draw("histsame");
      DeltaY->Draw("same");

      auto leg4 = new TLegend(0.6, 0.6, 0.9, 0.85);
      leg4->SetFillStyle(0);
      leg4->SetTextFont(42);
      leg4->SetTextSize(0.045);
      leg4->SetBorderSize(0);

      leg4->AddEntry(histMunfold,"Unfolded data","p");
      leg4->AddEntry(DeltaY_gen, "Generator prediction","l");
      leg4->AddEntry(DeltaY, "Reconstructed events","p");
      leg4->AddEntry(inputUnc, "Stat. uncertainty","f");
      leg4->AddEntry(totUnc, "Stat. #oplus syst. uncertainties","f");
      leg4->Draw();


      c4->cd();
      auto pad2 = new TPad("pad2","pad2",0,0.0,1,0.28);
      pad2->SetTopMargin(0.05);
      pad2->SetBottomMargin(0.3);
      pad2->Draw();

      pad2->cd();
      pad2->SetGridy();

      ratio->SetMaximum(1.3);
      ratio->SetMinimum(0.7);
      ratio->UseCurrentStyle();
      //ratio->GetYaxis()->SetTitleSize(100);
      ratio->GetYaxis()->SetTitleOffset(1.0);
      ratio->GetXaxis()->SetTitleOffset(1.0);
      ratio->GetXaxis()->SetLabelSize(50);
      ratio->GetYaxis()->SetNdivisions(4,4,0,"False");
      ratio->Draw("hist");
      totUnc->Draw("samee2"); 
      inputUnc->Draw("samee2");
      ratio->Draw("samehist");

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
      TH1 *histMunfold_L = unfold.GetOutput("Unfolded_L");

      TH1 *ratio_L =  (TH1*) DeltaY_gen->Clone("ratio");
      ratio_L->SetName("ratio");
      ratio_L->GetXaxis()->SetTitle("DeltaY [GeV]");
      ratio_L->GetYaxis()->SetTitle("MC/Data");
      ratio_L->Divide(histMunfold_L);

      TCanvas *c5 = new TCanvas("c5","c5");
      auto pad1L =  new TPad("pad1L","pad1L",0,0.3,1,1);
      pad1L->SetBottomMargin(0.05);
      pad1L->Draw();
      pad1L->cd();

      histMunfold_L->SetMarkerStyle(21);
      DeltaY->SetMarkerStyle(25);
      DeltaY_gen->SetLineColor(4);
      DeltaY_gen->GetYaxis()->SetTitleSize(25);
      DeltaY_gen->GetXaxis()->SetLabelSize(0);

      histMunfold_L->SetTitle(";;Events");
      histMunfold_L->GetYaxis()->SetTitleOffset(1.2);
      histMunfold_L->SetMinimum(0.0);
      histMunfold_L->SetAxisRange(0,max(DeltaY_gen->GetMaximum(),histMunfold->GetMaximum())*1.15,"Y");
      histMunfold_L->Draw();
      DeltaY_gen->Draw("histsame");
      DeltaY->Draw("same");

      auto leg4L = new TLegend(0.6, 0.6, 0.9, 0.85);
      leg4L->SetFillStyle(0);
      leg4L->SetTextFont(42);
      leg4L->SetTextSize(0.045);
      leg4L->SetBorderSize(0);

      leg4L->AddEntry(histMunfold_L,"Unfolded data","p");
      leg4L->AddEntry(DeltaY_gen, "Generator prediction","l");
      leg4L->AddEntry(DeltaY, "Reconstructed events","p");
      leg4L->AddEntry(inputUnc, "Stat. uncertainty","f");
      leg4L->AddEntry(totUnc, "Stat. #oplus syst. uncertainties","f");
      leg4L->Draw();


      c5->cd();
      auto pad2L = new TPad("pad2L","pad2L",0,0.0,1,0.28);
      pad2L->SetTopMargin(0.05);
      pad2L->SetBottomMargin(0.3);
      pad2L->Draw();

      pad2L->cd();
      pad2L->SetGridy();

      ratio_L->SetMaximum(3);
      ratio_L->SetMinimum(-1);
      ratio_L->UseCurrentStyle();
      ratio_L->GetYaxis()->SetTitleOffset(1.0);
      ratio_L->GetXaxis()->SetTitleOffset(1.0);
      ratio_L->GetXaxis()->SetLabelSize(50);
      ratio_L->GetYaxis()->SetNdivisions(4,4,0,"False");
      ratio_L->Draw("hist");
      totUnc->Draw("samee2");
      inputUnc->Draw("samee2");
      ratio_L->Draw("samehist");

      c5->Update();
      c5->Draw();
      c5->Print("Closure_L.pdf");

      TCanvas *C3 = new TCanvas("C3","C3");
      C3->SetGridy();

      Float_t recA2[] = {-2,-1.5,-1.25,-1.,-.75,-.5,-.25,0.,.25,0.5,.75,1,1.25,1.5,2};
      Int_t  rec2 = sizeof(recA2)/sizeof(Float_t) - 1;

      Float_t recA[] = {-1.75,-1.25,-.75,-.25,.25,.75,1.25,1.75};
      Int_t  rec = sizeof(rec)/sizeof(Float_t) - 1;

      Int_t Bin_1[1000], Bin_1R[1000];
      Int_t Bin_2[1000], Bin_2R[1000];
      Int_t Bin_3[1000], Bin_3R[1000];
      Int_t Bin_4[1000], Bin_4R[1000];
      Int_t Bin_5[1000], Bin_5R[1000];
      Int_t Bin_6[1000], Bin_6R[1000];
      Int_t Bin_7[1000], Bin_7R[1000];
      Int_t Bin_8[1000], Bin_8R[1000];

      Int_t count = 0;
      Int_t Integral = DeltaY->Integral();

      for(int bb=0;bb<1000;bb++){
        TH1F *Bias = new TH1F("Bias","",rec2,recA2);
        gRandom->SetSeed(bb);
        Bias->FillRandom(DeltaY,Integral);
        cout << Bias->GetBinContent(1) << endl;
        cout << Bias->GetBinContent(2) << endl;
        cout << Bias->GetBinContent(0) << endl;
        unfold.SetInput(Bias);
        unfold.DoUnfold(tauMinL);
        TH1 *Biasunfold_L = unfold.GetOutput("Biasunfolded_L");
        Bin_1[count] = Biasunfold_L->GetBinContent(1);
        Bin_2[count] = Biasunfold_L->GetBinContent(2);
        Bin_3[count] = Biasunfold_L->GetBinContent(3);
        Bin_4[count] = Biasunfold_L->GetBinContent(4);
        Bin_5[count] = Biasunfold_L->GetBinContent(5);
        Bin_6[count] = Biasunfold_L->GetBinContent(6);
        Bin_7[count] = Biasunfold_L->GetBinContent(7);
        Bin_8[count] = Biasunfold_L->GetBinContent(8);
        unfold.DoUnfold(0);
        TH1 *Biasunfold_R = unfold.GetOutput("Biasunfolded_R");
        Bin_1R[count] = Biasunfold_R->GetBinContent(1);
        cout << Biasunfold_R->GetBinContent(1) << endl;
        Bin_2R[count] = Biasunfold_R->GetBinContent(2);
        Bin_3R[count] = Biasunfold_R->GetBinContent(3);
        Bin_4R[count] = Biasunfold_R->GetBinContent(4);
        Bin_5R[count] = Biasunfold_R->GetBinContent(5);
        Bin_6R[count] = Biasunfold_R->GetBinContent(6);
        Bin_7R[count] = Biasunfold_R->GetBinContent(7);
        Bin_8R[count] = Biasunfold_R->GetBinContent(8);

        count = count+1;

        delete Biasunfold_L;
        delete Biasunfold_R;
        delete Bias;
      }

     Float_t bias[8];
     bias[0] = (mean(Bin_1) - DeltaY_gen->GetBinContent(1))/DeltaY_gen->GetBinContent(1);
     bias[1] = (mean(Bin_2) - DeltaY_gen->GetBinContent(2))/DeltaY_gen->GetBinContent(2);
     bias[2] = (mean(Bin_3) - DeltaY_gen->GetBinContent(3))/DeltaY_gen->GetBinContent(3);
     bias[3] = (mean(Bin_4) - DeltaY_gen->GetBinContent(4))/DeltaY_gen->GetBinContent(4);
     bias[4] = (mean(Bin_5) - DeltaY_gen->GetBinContent(5))/DeltaY_gen->GetBinContent(5);
     bias[5] = (mean(Bin_6) - DeltaY_gen->GetBinContent(6))/DeltaY_gen->GetBinContent(6);
     bias[6] = (mean(Bin_7) - DeltaY_gen->GetBinContent(7))/DeltaY_gen->GetBinContent(7);
     bias[7] = (mean(Bin_8) - DeltaY_gen->GetBinContent(8))/DeltaY_gen->GetBinContent(8);

     Float_t bias_R[8];
     bias_R[0] = (mean(Bin_1R) - DeltaY_gen->GetBinContent(1))/DeltaY_gen->GetBinContent(1);
     bias_R[1] = (mean(Bin_2R) - DeltaY_gen->GetBinContent(2))/DeltaY_gen->GetBinContent(2);
     bias_R[2] = (mean(Bin_3R) - DeltaY_gen->GetBinContent(3))/DeltaY_gen->GetBinContent(3);
     bias_R[3] = (mean(Bin_4R) - DeltaY_gen->GetBinContent(4))/DeltaY_gen->GetBinContent(4);
     bias_R[4] = (mean(Bin_5R) - DeltaY_gen->GetBinContent(5))/DeltaY_gen->GetBinContent(5);
     bias_R[5] = (mean(Bin_6R) - DeltaY_gen->GetBinContent(6))/DeltaY_gen->GetBinContent(6);
     bias_R[6] = (mean(Bin_7R) - DeltaY_gen->GetBinContent(7))/DeltaY_gen->GetBinContent(7);
     bias_R[7] = (mean(Bin_8R) - DeltaY_gen->GetBinContent(8))/DeltaY_gen->GetBinContent(8);

     Float_t xx[8] = {1,2,3,4,5,6,7,8};

     Float_t error[8], error_R[8];

     error[0] = (sigma(Bin_1)+DeltaY_gen->GetBinError(1))/abs(DeltaY_gen->GetBinContent(1)-mean(Bin_1));
     error[1] = (sigma(Bin_2)+DeltaY_gen->GetBinError(2))/abs(DeltaY_gen->GetBinContent(2)-mean(Bin_2));
     error[2] = (sigma(Bin_3)+DeltaY_gen->GetBinError(3))/abs(DeltaY_gen->GetBinContent(3)-mean(Bin_3));
     error[3] = (sigma(Bin_4)+DeltaY_gen->GetBinError(4))/abs(DeltaY_gen->GetBinContent(4)-mean(Bin_4));
     error[4] = (sigma(Bin_5)+DeltaY_gen->GetBinError(5))/abs(DeltaY_gen->GetBinContent(5)-mean(Bin_5));
     error[5] = (sigma(Bin_6)+DeltaY_gen->GetBinError(6))/abs(DeltaY_gen->GetBinContent(6)-mean(Bin_6));
     error[6] = (sigma(Bin_7)+DeltaY_gen->GetBinError(7))/abs(DeltaY_gen->GetBinContent(7)-mean(Bin_7));
     error[7] = (sigma(Bin_8)+DeltaY_gen->GetBinError(8))/abs(DeltaY_gen->GetBinContent(8)-mean(Bin_8));

     error_R[0] = (sigma(Bin_1R)+DeltaY_gen->GetBinError(1))/abs(DeltaY_gen->GetBinContent(1)-mean(Bin_1R));
     error_R[1] = (sigma(Bin_2R)+DeltaY_gen->GetBinError(2))/abs(DeltaY_gen->GetBinContent(2)-mean(Bin_2R));
     error_R[2] = (sigma(Bin_3R)+DeltaY_gen->GetBinError(3))/abs(DeltaY_gen->GetBinContent(3)-mean(Bin_3R));
     error_R[3] = (sigma(Bin_4R)+DeltaY_gen->GetBinError(4))/abs(DeltaY_gen->GetBinContent(4)-mean(Bin_4R));
     error_R[4] = (sigma(Bin_5R)+DeltaY_gen->GetBinError(5))/abs(DeltaY_gen->GetBinContent(5)-mean(Bin_5R));
     error_R[5] = (sigma(Bin_6R)+DeltaY_gen->GetBinError(6))/abs(DeltaY_gen->GetBinContent(6)-mean(Bin_6R));
     error_R[6] = (sigma(Bin_7R)+DeltaY_gen->GetBinError(7))/abs(DeltaY_gen->GetBinContent(7)-mean(Bin_7R));
     error_R[7] = (sigma(Bin_8R)+DeltaY_gen->GetBinError(8))/abs(DeltaY_gen->GetBinContent(8)-mean(Bin_8R));

     Float_t error_gen[8];

     error_gen[0] = DeltaY_gen->GetBinError(1)/DeltaY_gen->GetBinContent(1);
     error_gen[1] = DeltaY_gen->GetBinError(2)/DeltaY_gen->GetBinContent(2);
     error_gen[2] = DeltaY_gen->GetBinError(3)/DeltaY_gen->GetBinContent(3);
     error_gen[3] = DeltaY_gen->GetBinError(4)/DeltaY_gen->GetBinContent(4);
     error_gen[4] = DeltaY_gen->GetBinError(5)/DeltaY_gen->GetBinContent(5);
     error_gen[5] = DeltaY_gen->GetBinError(6)/DeltaY_gen->GetBinContent(6);
     error_gen[6] = DeltaY_gen->GetBinError(7)/DeltaY_gen->GetBinContent(7);
     error_gen[7] = DeltaY_gen->GetBinError(8)/DeltaY_gen->GetBinContent(8);

     Float_t Final_error[8];

     Final_error[0] = abs(bias[0])*(error[0]+error_gen[0]);
     Final_error[1] = abs(bias[1])*(error[1]+error_gen[1]);
     Final_error[2] = abs(bias[2])*(error[2]+error_gen[2]);
     Final_error[3] = abs(bias[3])*(error[3]+error_gen[3]);
     Final_error[4] = abs(bias[4])*(error[4]+error_gen[4]);
     Final_error[5] = abs(bias[5])*(error[5]+error_gen[5]);
     Final_error[6] = abs(bias[6])*(error[6]+error_gen[6]);
     Final_error[7] = abs(bias[7])*(error[7]+error_gen[7]);

     Float_t Final_error_R[8];

     Final_error_R[0] = abs(bias_R[0])*(error_R[0]+error_gen[0]);
     Final_error_R[1] = abs(bias_R[1])*(error_R[1]+error_gen[1]);
     Final_error_R[2] = abs(bias_R[2])*(error_R[2]+error_gen[2]);
     Final_error_R[3] = abs(bias_R[3])*(error_R[3]+error_gen[3]);
     Final_error_R[4] = abs(bias_R[4])*(error_R[4]+error_gen[4]);
     Final_error_R[5] = abs(bias_R[5])*(error_R[5]+error_gen[5]);
     Final_error_R[6] = abs(bias_R[6])*(error_R[6]+error_gen[6]);
     Final_error_R[7] = abs(bias_R[7])*(error_R[7]+error_gen[7]);

     Float_t ex[8] = {0,0,0,0,0,0,0,0};

     TGraphErrors *gr = new TGraphErrors(8,recA,bias,ex,Final_error);
     TGraphErrors *gr_R = new TGraphErrors(8,recA,bias_R,ex,Final_error_R);
     C3->SetGrid();
//     C3->cd(1);
//     C3->SetGrid();
//     gr->SetTitle("L-curve scan");
 //    gr->GetYaxis()->SetRangeUser(-1., 1.);
//     gr->GetXaxis()->SetTitle("DeltaY");
//     gr->GetYaxis()->SetTitle("Bias");
//     gr->Draw();
//     C3->cd(2);
     gr_R->GetXaxis()->SetTitle("DeltaY");
     gr_R->GetYaxis()->SetTitle("Bias");
    // gr_R->GetYaxis()->SetRangeUser(-0.3,0.3);
//     Float_t limit = gr_R->GetMaximum();
//     cout << limit << endl;
     gr_R->GetYaxis()->SetRangeUser(-0.7,0.7);
//     gr_R->GetYaxis()->SetRangeUser(-1.25*TMath::Max(TMath::Abs(gr_R->GetMaximum()),TMath::Abs(gr_R->GetMinimum())), 1.25*TMath::Max(TMath::Abs(gr_R->GetMaximum()),TMath::Abs(gr_R->GetMinimum())));
     gr_R->SetTitle(Form("#rho minimization (#tau = %0.3f)",tauMinOpt));
     gr_R->GetYaxis()->SetNdivisions(20,"False");
     gr_R->Draw("ap");

     C3->Print("Bias.pdf");

     TCanvas *C4 = new TCanvas("C4","C4");
     C4->SetGrid();
     gr->GetYaxis()->SetRangeUser(-0.5,0.5);
     gr->GetXaxis()->SetTitle("DeltaY");
     gr->GetYaxis()->SetTitle("Bias");
     gr->SetTitle(Form("L-curve scan (#tau = %0.3f)",tauMinL));
     gr->GetYaxis()->SetNdivisions(20,"False");
     gr->Draw("ap");

     C4->Print("Bias_L.pdf");


for(int j=0;j<=7;j++){
cout << bias_R[j] << " +/- " << Final_error_R[j] << endl;}

}
