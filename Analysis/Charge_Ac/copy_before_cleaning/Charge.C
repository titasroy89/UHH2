
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Charge(Int_t max = 19960) 

{

    gStyle->SetOptStat(0);
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

    TH1F *DeltaY_rec_test = new TH1F("DeltaY_rec_test","",newrec,new_rec);
    TH1F *DeltaY_gen_test = new TH1F("DeltaY_gen_test","",binnum_gen,bins_gen);
    TH2F *Smearing_Matrix_closure = new TH2F("Smearing_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Smearing_Matrix_test = new TH2F("Smearing_Matrix_test","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Closure_Matrix = new TH2F("Closure_Matrix","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Migration_Matrix_closure = new TH2F("Migration_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);

//optimization

    TH1F *DeltaY_FullPS = new TH1F("DeltaY_FullPS","",binnum_rec,bins_rec);
    TH2F *Smearing_Matrix = new TH2F("Smearing_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *DeltaY_rec = new TH1F("DeltaY_rec","",binnum_rec,bins_rec);
    TH1F *DeltaY_gen_rec = new TH1F("DeltaY_gen_rec","",binnum_rec,bins_rec);
    TH1F *DeltaY_Visgen = new TH1F("DeltaY_Visgen","",binnum_rec,bins_rec);
    TH1F *Eff_Vis = new TH1F("Eff_Vis","",binnum_rec,bins_rec);
    TH1F *Acceptance = new TH1F("Acceptance","",binnum_rec,bins_rec);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Response_Matrix = new TH2F("Response_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","Transition Probability",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *EfficiencyxAcceptance = new TH1F("Efficiency*Acceptance","",binnum_rec,bins_rec);
    TH1F *Stability = new TH1F("Stability","",binnum_rec,bins_rec);
    TH1F *Purity = new TH1F("Purity","",binnum_rec,bins_rec);

    string rap_diff = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    treereco->Project("DeltaY_gen_rec",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("DeltaY_rec",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"));
    treereco->Project("Smearing_Matrix",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));

//Llenando histogramas para closure test

//    treereco->Project("Smearing_Matrix_closure",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",19960,0);
//    treereco->Project("Smearing_Matrix_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",24090-19960,19960+1);
//    auto DeltaY_gen_closure = (TH1*) Smearing_Matrix_test->ProjectionY("DeltaY_gen_closure",1,newrec);
//    auto DeltaY_rec_closure = (TH1*) Smearing_Matrix_test->ProjectionX("DeltaY_rec_closure",1,binnum_rec);

//    treereco->Project("Smearing_Matrix_closure",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",19960,0);
//    treereco->Project("Smearing_Matrix_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",24090-19960,19960+1);
//    auto DeltaY_gen_closure = (TH1*) Smearing_Matrix_test->ProjectionY("DeltaY_gen_closure",1,newrec);
//    auto DeltaY_rec_closure = (TH1*) Smearing_Matrix_test->ProjectionX("DeltaY_rec_closure",1,binnum_rec);

    treereco->Project("Smearing_Matrix_closure",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",19960,0);
    treereco->Project("Smearing_Matrix_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s):%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",24090-19960,19960+1);
    auto DeltaY_gen_closure = (TH1*) Smearing_Matrix_test->ProjectionY("DeltaY_gen_closure",1,newrec);
    auto DeltaY_rec_closure = (TH1*) Smearing_Matrix_test->ProjectionX("DeltaY_rec_closure",1,binnum_rec);

    treereco->Project("DeltaY_rec_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",24090-19960,19960+1);
    treereco->Project("DeltaY_gen_test",Form("%s < -2. ? TMath::Max(-1.99,%s): (%s > 2. ? TMath::Min(1.99,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",24090-19960,19960+1);
   
    for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
        Response_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/DeltaY_Visgen->GetBinContent(b));
        Migration_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Smearing_Matrix->Integral(1,binnum_gen,b,b));

        //solo los elementos en la diagonal importan
        Purity_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Smearing_Matrix->Integral(a,a,1,binnum_gen));

       }
    }


    //fill migration matrix for colsure

    for(int a=1;a<=newrec;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
        Migration_Matrix_closure->SetBinContent(a,b,Smearing_Matrix_closure->GetBinContent(a,b)/Smearing_Matrix_closure->Integral(0,newrec+1,b,b));
       }
    }

   // Purity && Stability
    for(Int_t m=1;m<=binnum_gen;m++){
         Stability->SetBinContent(m,Migration_Matrix->GetBinContent(m,m));
         Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
    }

    Purity->GetYaxis()->SetRangeUser(0,1.3);
    Purity->GetXaxis()->SetTitle("DeltaY [GeV]");
    Purity->SetLineColor(kRed);
    Purity->SetLineWidth(2);
    Stability->SetLineColor(kBlue);
    Stability->SetLineWidth(2);

    TFile out("Data_unfolding_6bins.root","recreate");
    DeltaY_rec_closure->Write();
    DeltaY_gen_closure->Write();
    DeltaY_rec_test->Write();
    DeltaY_gen_test->Write();
    Migration_Matrix_closure->Write();
    DeltaY_rec->Write();
    DeltaY_gen_rec->Write();
    DeltaY_Visgen->Write();
    Smearing_Matrix->Write();
    Purity_Matrix->Write();
    Migration_Matrix->Write();
    Response_Matrix->Write();
    Stability->Write();
    Purity->Write();

    TCanvas* cc = new TCanvas("Scatter","Scatter",2400,1200);

    cc->Divide(1,1);
    cc->cd(1);

    Purity->Draw();
    Stability->Draw("same");

    Double_t Res_gauss[] = {0.599,.278,.294,.29,.292,.277,.280,.569};
    Double_t Bin_size[binnum_gen];
    Double_t Relative_Resolution[binnum_gen];

    TH1F *Ratio_res = new TH1F("Ratio_res","",binnum_gen,bins_gen);

    for(int j=1;j<=binnum_gen;j++){
            Bin_size[j-1] = bins_gen[j] - bins_gen[j-1];
            Relative_Resolution[j-1]=Res_gauss[j-1]/Bin_size[j-1];
            Ratio_res->SetBinContent(j,Relative_Resolution[j-1]);
    }

    Ratio_res->SetLineColor(kYellow+4);
    Ratio_res->SetLineWidth(2);
    Ratio_res->SetLineStyle(9);
    Ratio_res->Draw("same");

    TLegend leg(.65, .65, .85, .85, "");
    leg.SetFillColor(0);
    leg.AddEntry(Purity, "Purity");
    leg.AddEntry(Stability, "Stability");
    leg.AddEntry(Ratio_res,"Resolution (Gauss)");
    leg.SetBorderSize(0);
    leg.Draw("Same");

    TLegend leg2(.20, .75, .35, .85, "");
    leg2.AddEntry((TObject*)0, "#mu + jets", "");
    leg2.SetBorderSize(0);
    leg2.Draw("same");

    cc->Print("P&S_6bins.pdf");

    TCanvas* dd = new TCanvas("dd","dd",2400,1200);
    dd->Divide(1,1);
    dd->cd(1);

    Migration_Matrix->GetXaxis()->SetTitle("DeltaY_rec [GeV]");
    Migration_Matrix->GetYaxis()->SetTitle("DeltaY_gen [GeV]");
    Migration_Matrix->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix->Draw("text colz");
    dd->Print("Migration_Matrix_6bins.pdf");


    TCanvas* ee = new TCanvas("ee","ee",2400,1200);
    ee->Divide(1,1);
    ee->cd(1);

    Migration_Matrix_closure->GetXaxis()->SetTitle("DeltaY_rec [GeV]");
    Migration_Matrix_closure->GetYaxis()->SetTitle("DeltaY_gen [GeV]");
    Migration_Matrix_closure->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix_closure->Draw("text2 colz");
    ee->Print("Closure_Matrix_6bins.pdf");


}

