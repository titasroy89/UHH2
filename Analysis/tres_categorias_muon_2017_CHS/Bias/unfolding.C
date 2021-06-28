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

void unfolding(string pdf_name, Int_t N = 100000,Int_t bin = 2)
{
      if(gRandom) delete gRandom;
      gRandom = new TRandom3(0);
      gStyle->SetOptStat(0);
      TFile* file = TFile::Open("Data_unfolding_.root");

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
           double rhoaverage = Rhoi_rebinnedA->Integral()/gen_bin;
           RhoAvg[i] = rhoaverage;
           lg10tau[i] = tauReg;
           if(rhoaverage>0 && rhoaverage<rhoAvgMinOpt){
               rhoAvgMinOpt = rhoaverage;
               tauMinOpt = tauReg;
           }
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

//  c->Print(Form("Rho_%s.pdf",pdf_name.c_str()));

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
//      totUnc->GetYaxis()->SetRangeUser(0.0,1.0);


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
//      Unc->Print(Form("Unc_%s.pdf",pdf_name.c_str()));

//Closure_test

      TH1 *ratio =  (TH1*) DeltaY_gen->Clone("ratio");
      ratio->SetName("ratio");
      ratio->GetXaxis()->SetTitle("DeltaY [GeV]");
      ratio->GetYaxis()->SetTitle("MC/Data");
      ratio->Divide(histMunfold);
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
//      c4->Print(Form("Closure_%s.pdf",pdf_name.c_str()));


// Closure Test LCurve_min

      TH2D *Ematrix_L = new TH2D("Ematrix_L","Covariance Matrix",gen_bin,0,gen_bin,gen_bin,0,gen_bin);
      unfold.DoUnfold(tauMinL);
      unfold.GetEmatrix(Ematrix_L,0);
      TCanvas *EL = new TCanvas("EL","EL");
      Ematrix_L->Draw("COLZ");
//      EL->Print(Form("Error_Matrix_(Lscan)_%s.pdf",pdf_name.c_str()));
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
      leg4L->AddEntry(totUnc, "Stat. #oplus Mtx. stat. uncertainty","f");
      leg4L->Draw();

      TLatex latex2;
      latex2.SetTextSize(0.049);
      latex2.SetTextAlign(11);
      latex2.DrawLatex(-1.9,histMunfold_L->GetMaximum()*1.01,"Work in progress");
      TLatex latex3;      
      latex3.SetTextSize(0.049);
      latex3.SetTextAlign(11);
      latex3.DrawLatex(1.1,histMunfold_L->GetMaximum()*1.01,"41.55 fb^{-1} (13 TeV)");


      c5->cd();
      auto pad2L = new TPad("pad2L","pad2L",0,0.0,1,0.28);
      pad2L->SetTopMargin(0.05);
      pad2L->SetBottomMargin(0.3);
      pad2L->Draw();

      pad2L->cd();
      pad2L->SetGridy();

      ratio_L->SetMaximum(1.4);
      ratio_L->SetMinimum(0.6);
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
      c5->Print(Form("Closure_muon_2017.pdf",pdf_name.c_str()));

      TCanvas *C3 = new TCanvas("C3","C3");
      C3->SetGridy();


//      Bias Measurement 
      

      Float_t genA2[] = {-2,-1.5,-1.,-.5,0.,0.5,1,1.5,2};
      Int_t gen2 = sizeof(genA2)/sizeof(Float_t) - 1;
      Float_t recA2[] = {-2,-1.5,-1.25,-1.,-.75,-.5,-.25,0.,.25,0.5,.75,1,1.25,1.5,2}; 
      Int_t rec2 = sizeof(recA2)/sizeof(Float_t) - 1;
      Float_t recA[] = {-1.75,-1.25,-.75,-.25,.25,.75,1.25,1.75}; 
      Int_t rec = sizeof(rec)/sizeof(Float_t) - 1;  


//      Float_t recA2[] = {880,1060,1180,1300,1410,1520,1710,1900,2100,2300,2650,3000,7000};
//      Int_t rec2 = sizeof(recA2)/sizeof(Float_t) - 1;
//      Float_t recA[] = {970,1180,1410,1710,2100,2650,4500};
//      Int_t rec = sizeof(rec)/sizeof(Float_t) - 1;

      Int_t Bin_1[gen_bin][N], Bin_1R[gen_bin][N];
      Float_t bias[gen_bin];
      Float_t bias_R[gen_bin];
      Float_t Final_error[gen_bin];
      Float_t Final_error_R[gen_bin];
      Float_t Input_error_bias[gen_bin]; 

      Float_t ex[8]= {0,0,0,0,0,0,0,0};
      Float_t Integral = DeltaY->Integral();
      Float_t Integral_gen = DeltaY_gen->Integral();      

//      cout << DeltaY->Integral() << endl;

      TCanvas *Nominal = new TCanvas("Nominal","Nominal");
      Nominal->Divide(1,1);   
      Nominal->cd(1);
      DeltaY->GetXaxis()->SetTitle("DaltaY");
      DeltaY->GetYaxis()->SetTitle("Events");
      DeltaY->Draw();
//      Nominal->Print("Nominal.pdf"); 

      TCanvas *Cien = new TCanvas("Cien","Cien");
      Cien->cd();  
      DeltaY->Scale(10000/Integral);
      DeltaY->GetXaxis()->SetTitle("DaltaY");
      DeltaY->GetYaxis()->SetTitle("Events");      
      DeltaY->Draw();
//      Cien->Print("Scaled_Nominal.pdf"); 


      TH1F *Bias_1 = new TH1F("Bias_1","",rec2,recA2);
      TH1F *Bias_2 = new TH1F("Bias_2","",rec2,recA2);
      TH1F *Bias_3 = new TH1F("Bias_3","",rec2,recA2); 
 
      TH1F *Unfolded_1 = new TH1F("Unfolded_1","",gen2,genA2);
      TH1F *Unfolded_2 = new TH1F("Unfolded_2","",gen2,genA2);
      TH1F *Unfolded_3 = new TH1F("Unfolded_3","",gen2,genA2);    

      TH1 *tem_bias =  (TH1*) histMunfold->Clone("tem_bias");
      tem_bias->Reset();
      TH1 *totUnc_bias =  (TH1*) tem_bias->Clone("totUnc");

      for(int bb=0;bb<N;bb++){
         TH1F *Bias = new TH1F("Bias","",rec2,recA2);
         gRandom->SetSeed(0);
         
         for(int jj=1;jj<=rec2;jj++){
  	 	Bias->SetBinContent(jj,gRandom->Poisson(DeltaY->GetBinContent(jj)));	
//                if(Bias->GetBinContent(jj) == 0) Bias->SetBinError(jj,0.001); 
//                cout << Bias->GetBinContent(jj) << " " << ";" ;
         }

         Bias->Scale(10000/Bias->Integral());

//         cout << endl;

         for(int cc=1;cc<=rec2;cc++){
              if(bb==1)  Bias_1->SetBinContent(cc,Bias->GetBinContent(cc));
              if(bb==2)  Bias_2->SetBinContent(cc,Bias->GetBinContent(cc));
              if(bb==3)  Bias_3->SetBinContent(cc,Bias->GetBinContent(cc));
         }

         unfold.SetInput(Bias);

         unfold.DoUnfold(tauMinL);
         TH1 *Biasunfold_L = unfold.GetOutput("Biasunfolded_L");

         for(int cc=1;cc<=gen_bin;cc++){
             Bin_1[cc-1][bb] = Biasunfold_L->GetBinContent(cc);
              if(bb==1)  Unfolded_1->SetBinContent(cc,Biasunfold_L->GetBinContent(cc));
              if(bb==2)  Unfolded_2->SetBinContent(cc,Biasunfold_L->GetBinContent(cc));
              if(bb==3)  Unfolded_3->SetBinContent(cc,Biasunfold_L->GetBinContent(cc));                                
         }

         if (bb==1){
 
             unfold.SetInput(DeltaY);
             unfold.DoUnfold(0);
             TH2 *Ematrix_Total_bias = unfold.GetEmatrixTotal("Ematrix_Total_bias");
             for (int i=1;i <= tem_bias->GetNbinsX()+1;i++) {
                 totUnc_bias->SetBinContent(i,sqrt(Ematrix_Total_bias->GetBinContent(i,i))/Biasunfold_L->GetBinContent(i));
             }
         }

         unfold.DoUnfold(tauMinOpt);
         TH1 *Biasunfold_R = unfold.GetOutput("Biasunfolded_R");

         for(int cc=1;cc<=gen_bin;cc++){
             Bin_1R[cc-1][bb] = Biasunfold_R->GetBinContent(cc);
         }

         delete Biasunfold_L;
         delete Biasunfold_R;
         delete Bias;
     }

      TCanvas *Random_Bias = new TCanvas("Random_Bias","Random_Bias");
      Random_Bias->Divide(1,1);
      Random_Bias->cd(1);
      DeltaY->GetYaxis()->SetRangeUser(0,50);
      DeltaY->GetXaxis()->SetTitle("DeltaY");
      DeltaY->GetYaxis()->SetTitle("Events"); 
      DeltaY->Draw();      
      Bias_1->SetLineColor(kOrange);
      Bias_1->Draw("same");
      Bias_2->SetLineColor(kGreen);
      Bias_2->Draw("same");
      Bias_3->SetLineColor(kRed);
      Bias_3->Draw("same");
//      Random_Bias->Print("Random_Bias.pdf");   
       
      for(int cc=1;cc<=gen_bin;cc++){
          cout << DeltaY->GetBinContent(cc) << " ";
      }
  
      cout << endl;    
 
      DeltaY_gen->Scale(10000/Integral_gen);


      TCanvas *Random_Unfolded = new TCanvas("Random_Unfolded","Random_Unfolded");
      Random_Unfolded->Divide(1,1);
      Random_Unfolded->cd(1);
      DeltaY_gen->GetYaxis()->SetRangeUser(0,90);
      DeltaY_gen->GetXaxis()->SetTitle("DeltaY");
      DeltaY_gen->GetYaxis()->SetTitle("Events");      
      DeltaY_gen->Draw();
      Unfolded_1->SetLineColor(kOrange);
      Unfolded_1->Draw("same");
      Unfolded_2->SetLineColor(kGreen);
      Unfolded_2->Draw("same");
      Unfolded_3->SetLineColor(kRed);
      Unfolded_3->Draw("same");
//      Random_Unfolded->Print("Random_Unfolded.pdf");

 
      for(int cc=1;cc<=gen_bin;cc++){
        bias[cc-1] = (mean(Bin_1[cc-1],N,DeltaY_gen->GetBinContent(cc)))/DeltaY_gen->GetBinContent(cc);
        bias_R[cc-1] = (mean(Bin_1R[cc-1],N,DeltaY_gen->GetBinContent(cc)))/DeltaY_gen->GetBinContent(cc);
//        Final_error[cc-1] = (sigma(Bin_1[cc-1],N,DeltaY_gen->GetBinContent(cc)))/(sqrt(N)*DeltaY_gen->GetBinContent(cc));
//        Final_error_R[cc-1] = (sigma(Bin_1R[cc-1],N,DeltaY_gen->GetBinContent(cc)))/(sqrt(N)*DeltaY_gen->GetBinContent(cc));
        Final_error[cc-1] = (sigma(Bin_1[cc-1],N,DeltaY_gen->GetBinContent(cc)))/(DeltaY_gen->GetBinContent(cc));
        Final_error_R[cc-1] = (sigma(Bin_1R[cc-1],N,DeltaY_gen->GetBinContent(cc)))/(DeltaY_gen->GetBinContent(cc));
        Input_error_bias[cc-1] = totUnc_bias->GetBinContent(cc);

    }



     for(int i=0;i<=7;i++){
//        cout << bias[i] << endl;
        cout << Final_error[i] << endl;
        cout << totUnc_bias->GetBinContent(i+1) << endl;
     }

     TGraphErrors *gr = new TGraphErrors(gen_bin,recA,bias,ex,Final_error);
     TGraphErrors *gr_R = new TGraphErrors(gen_bin,recA,bias_R,ex,Final_error_R);
     TGraphErrors *gr_bias = new TGraphErrors(gen_bin,recA,bias,ex,Input_error_bias);

     C3->SetGrid();
     gr_R->GetXaxis()->SetTitle("DeltaY");
     gr_R->GetYaxis()->SetTitle("Bias");
     gr_R->SetMarkerStyle(21);
     gr_R->SetMarkerSize(1);
//     gr_R->GetYaxis()->SetRangeUser(-0.3,0.3);
     gr_R->SetTitle(Form("#rho minimization (#tau = %0.3f)",tauMinOpt));
     gr_R->GetYaxis()->SetNdivisions(20,"False");
     gr_R->Draw("ap");
//     C3->Print(Form("Bias_%s.pdf",pdf_name.c_str()));

     TCanvas *C4 = new TCanvas("C4","C4");
     C4->SetGrid();
//     gr->GetYaxis()->SetRangeUser(-0.1,0.1);
     gr->GetXaxis()->SetTitle("DeltaY");
     gr->GetYaxis()->SetTitle("Bias");
     gr->SetMarkerStyle(21);
     gr->SetMarkerSize(1);
     gr->GetYaxis()->SetRangeUser(-0.5,0.5);
//     gr->SetTitle(Form("L-curve scan (#tau = %0.3f)",tauMinL));
     gr->SetTitle("");
     gr->GetYaxis()->SetNdivisions(20,"False");
     gr->Draw("ap");
     gr_bias->SetLineColor(2);
     gr_bias->SetMarkerStyle(24);
     gr_bias->SetMarkerColor(kBlack);
//     gr_bias->Draw("same p");

     cout << gr->GetMaximum() << endl;

     TLatex latex5;
     latex5.SetTextSize(0.042);
     latex5.SetTextAlign(11);
     latex5.DrawLatex(-1.9,0.5*1.01,"Work in progress");
     TLatex latex6;
     latex6.SetTextSize(0.042);
     latex6.SetTextAlign(11);
     latex6.DrawLatex(0.8,0.5*1.01,"41.55 fb^{-1} (13 TeV)");

     C4->Print(Form("Bias_muon_2017.pdf",pdf_name.c_str()));



}
