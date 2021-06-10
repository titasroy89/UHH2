
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Ac(string pdf_name, Int_t max = 0) 

{

    gStyle->SetOptStat(0);
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection/uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*) chreco;

//    TChain *chreco1 = new TChain("AnalysisTree","");
//    chreco1->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root/AnalysisTree");
//    TTree *treereco1 = (TTree*) chreco1;

    cout << treereco->GetEntries() << endl;

    TChain *chreco2 = new TChain("AnalysisTree","");
    chreco2->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullVisPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root");
    TTree *treereco2 = (TTree*) chreco2;

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
    TH2F *Closure_Matrix = new TH2F("Closure_Matrix","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Migration_Matrix_closure = new TH2F("Migration_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);

//optimization

    //rapidity 
    TH1F *DeltaY_FullPS = new TH1F("DeltaY_FullPS","",binnum_rec,bins_rec);
    TH2F *Smearing_Matrix = new TH2F("Smearing_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *DeltaY_rec = new TH1F("DeltaY_rec","",binnum_rec,bins_rec);
    TH1F *DeltaY_gen_rec = new TH1F("DeltaY_gen_rec","",binnum_rec,bins_rec);
    TH1F *DeltaY_Visgen = new TH1F("DeltaY_Visgen","",binnum_rec,bins_rec);
    TH1F *Eff_Vis = new TH1F("Eff_Vis","",binnum_rec,bins_rec);
//    TH1F *Acceptance = new TH1F("Acceptance","",binnum_rec,bins_rec);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Response_Matrix = new TH2F("Response_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","Transition Probability",binnum_gen,bins_gen,binnum_rec,bins_rec);
//    TH1F *EfficiencyxAcceptance = new TH1F("Efficiency*Acceptance","",binnum_rec,bins_rec);
    TH1F *Stability = new TH1F("Stability","",binnum_rec,bins_rec);
    TH1F *Purity = new TH1F("Purity","",binnum_rec,bins_rec);


    string rap_diff = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";
    string InvMass = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";

//    treereco1->Project("DeltaY_FullPS",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("DeltaY_gen_rec",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("DeltaY_rec",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"));
    treereco2->Project("DeltaY_Visgen",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("Smearing_Matrix",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s):%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),"DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"));

//Llenando histogramas para closure test


//rapidity
      treereco->Project("Smearing_Matrix_closure",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s):%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),"DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",8444,8491);
      treereco->Project("DeltaY_gen_closure",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",7990,500);
      treereco->Project("DeltaY_rec_closure",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",7990,500);

    for (int i=1;i<=binnum_gen;i++){
	Eff_Vis->SetBinContent(i,DeltaY_rec->GetBinContent(i)/DeltaY_Visgen->GetBinContent(i));
//        Acceptance->SetBinContent(i,DeltaY_Visgen->GetBinContent(i)/DeltaY_FullPS->GetBinContent(i));
    }
   
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
        Migration_Matrix_closure->SetBinContent(a,b,Smearing_Matrix_closure->GetBinContent(a,b)/Smearing_Matrix_closure->Integral(1,newrec,b,b));
       }
    }

   // Purity && Stability
    for(Int_t m=1;m<=binnum_gen;m++){
         Stability->SetBinContent(m,Migration_Matrix->GetBinContent(m,m));
         Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
//         EfficiencyxAcceptance->SetBinContent(m,Eff_Vis->GetBinContent(m)*Acceptance->GetBinContent(m));
    }

    Purity->GetYaxis()->SetRangeUser(0,1.3);
    Purity->GetXaxis()->SetTitle("DeltaY [GeV]");
    Purity->SetLineColor(kRed);
    Purity->SetLineWidth(2);
    Stability->SetLineColor(kBlue);
    Stability->SetLineWidth(2);
    Eff_Vis->SetLineColor(kGreen+1);
    Eff_Vis->SetLineStyle(9);
    Eff_Vis->SetLineWidth(2);
//    Acceptance->SetLineColor(kViolet);
//    Acceptance->SetLineStyle(9);
//    Acceptance->SetLineWidth(2);
//    EfficiencyxAcceptance->SetLineColor(kViolet);
//    EfficiencyxAcceptance->SetLineStyle(9);
//    EfficiencyxAcceptance->SetLineWidth(2);

    TFile out("Data_unfolding_.root","recreate");
    DeltaY_rec_closure->Write();
    DeltaY_gen_closure->Write();
    Migration_Matrix_closure->Write();
    DeltaY_rec->Write();
    DeltaY_gen_rec->Write();
    DeltaY_Visgen->Write();
    Eff_Vis->Write();
//    Acceptance->Write();
    Smearing_Matrix_closure->Write();
    Purity_Matrix->Write();
    Migration_Matrix->Write();
    Response_Matrix->Write();
    Stability->Write();
    Purity->Write();
//    EfficiencyxAcceptance->Write();

    TCanvas* cc = new TCanvas("Scatter","Scatter",2400,1200);

    cc->Divide(1,1);
    cc->cd(1);

    Purity->Draw();
    Stability->Draw("same");
//    Acceptance->Draw("same");
    Eff_Vis->Draw("same");

    Double_t Res_gauss[] = {0.475,.278,.294,.29,.292,.277,.280,.408};
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
    leg.AddEntry(Eff_Vis,"Eff_Vis");
//    leg.AddEntry(Acceptance,"Acceptance");
    leg.AddEntry(Ratio_res,"Resolution (Gauss)");
    leg.SetBorderSize(0);
    leg.Draw("Same");

    TLegend leg2(.20, .75, .35, .85, "");
    leg2.AddEntry((TObject*)0, "#mu + jets", "");
    leg2.SetBorderSize(0);
    leg2.Draw("same");

    cc->Print(Form("P&S_%s.pdf",pdf_name.c_str()));

    TCanvas* dd = new TCanvas("dd","dd",2400,1200);
    dd->Divide(1,1);
    dd->cd(1);

    Migration_Matrix->GetXaxis()->SetTitle("DeltaY_rec [GeV]");
    Migration_Matrix->GetYaxis()->SetTitle("DeltaY_gen [GeV]");
    Migration_Matrix->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix->Draw("text colz");
    dd->Print(Form("Migration_matrix_%s.pdf",pdf_name.c_str()));


    TCanvas* ee = new TCanvas("ee","ee",2400,1200);
    ee->Divide(1,1);
    ee->cd(1);

    Migration_Matrix_closure->GetXaxis()->SetTitle("DeltaY_rec [GeV]");
    Migration_Matrix_closure->GetYaxis()->SetTitle("DeltaY_gen [GeV]");
    Migration_Matrix_closure->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix_closure->Draw("text2 colz");
    ee->Print(Form("Closure_Matrix_%s.pdf",pdf_name.c_str()));

    //uncomment only to create projections
//    #define TEST0
     
    #ifdef TEST0

    auto ProY1 = (TH1*) Smearing_Matrix->ProjectionY("ProY1",1,1);
    auto ProY2 = (TH1*)Smearing_Matrix->ProjectionY("ProY2",2,2);
    auto ProY3 = (TH1*)Smearing_Matrix->ProjectionY("ProY3",3,3);
    auto ProY4 = (TH1*)Smearing_Matrix->ProjectionY("ProY4",4,4);
    auto ProY5 = (TH1*)Smearing_Matrix->ProjectionY("ProY5",5,5);
    auto ProY6 = (TH1*)Smearing_Matrix->ProjectionY("ProY6",6,6);
    auto ProY7 = (TH1*)Smearing_Matrix->ProjectionY("ProY7",7,7);
    auto ProY8 = (TH1*)Smearing_Matrix->ProjectionY("ProY8",8,8);

    TH1* hh1 = (TH1*) gDirectory->Get("ProY1");
    TH1* hh2 = (TH1*) gDirectory->Get("ProY2");
    TH1* hh3 = (TH1*) gDirectory->Get("ProY3");
    TH1* hh4 = (TH1*) gDirectory->Get("ProY4");
    TH1* hh5 = (TH1*) gDirectory->Get("ProY5");
    TH1* hh6 = (TH1*) gDirectory->Get("ProY6");
    TH1* hh7 = (TH1*) gDirectory->Get("ProY7");
    TH1* hh8 = (TH1*) gDirectory->Get("ProY8");

    TFile *MyFile2 = new TFile("Gauss.root","recreate");
    gDirectory->WriteObject(hh1,"ProY1");
    gDirectory->WriteObject(hh2,"ProY2");
    gDirectory->WriteObject(hh3,"ProY3");
    gDirectory->WriteObject(hh4,"ProY4");
    gDirectory->WriteObject(hh5,"ProY5");
    gDirectory->WriteObject(hh6,"ProY6");
    gDirectory->WriteObject(hh7,"ProY7");
    gDirectory->WriteObject(hh8,"ProY8");

    #endif

}

