#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TMath.h"
using namespace RooFit ;

void Mass_6bins(Float_t max = 0.0) 

{

    gStyle->SetOptStat(0);
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection//uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*) chreco;

//    TChain *chreco1 = new TChain("AnalysisTree","");
//    chreco1->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root/AnalysisTree");
//    TTree *treereco1 = (TTree*) chreco1;

    TChain *chreco2 = new TChain("AnalysisTree","");
    chreco2->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullVisPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root");
    TTree *treereco2 = (TTree*) chreco2;

//Copiando de aqui para 7 bins
//    Float_t bins_gen[] = {880,1064,1298,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {880,1064,1298,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {880,982,1064,1200,1298,1400,1504,1650,1800,2000,2200,2600,3000,4500,6000};

//    Float_t bins_gen[] = {880,1064,1170,1298,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {880,1064,1170,1298,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {880,981,1064,1110,1170,1210,1298,1400,1504,1650,1800,2000,2200,2600,3000,4500,6000};

//    Float_t bins_gen[] = {880,1052,1190,1310,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {880,1052,1190,1310,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {880,981,1052,1110,1190,1210,1310,1400,1502,1650,1800,2000,2200,2600,3000,4500,6000};

//    Float_t bins_gen[] = {880,1064,1298,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {880,1064,1298,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {880,909,1064,1206,1298,1400,1502,1650,1800,2000,2200,2400,2600,4500,6000};

//    Float_t bins_gen[] = {880,1064,1298,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {880,1064,1298,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {880,909,1064,1206,1298,1400,1502,1650,1800,2000,2200,2400,2600,4500,6000};

//tau = 0.6515
    Float_t bins_gen[] = {880,1050,1300,1500,1800,2200,2600,4000};
    Float_t bins_rec[] = {880,1050,1300,1500,1800,2200,2600,4000};
    Float_t new_rec[] = {880,1050,1175,1300,1400,1500,1650,1800,2000,2200,2400,2600,4000};

//    Float_t bins_gen[] = {880,1064,1298,1502,1800,2200,3000,7000};
//    Float_t bins_rec[] = {880,1064,1298,1502,1800,2200,3000,7000};
//    Float_t new_rec[] = {880,978,1064,1208,1298,1382,1502,1676,1800,2050,2200,2390,3000,4300,7000};

//    Float_t bins_gen[] = {880,1064,1298,1502,1800,2200,3000,7000};
//    Float_t bins_rec[] = {880,1064,1298,1502,1800,2200,3000,7000};
//    Float_t new_rec[] = {00,880,986,1064,1120,1298,1382,1502,1650,1800,2100,2200,2600,3000,4300,7000};

//    Float_t bins_gen[] = {880,1064,1298,1502,1800,2100,3000,7000};
//    Float_t bins_rec[] = {880,1064,1298,1502,1800,2100,3000,7000};
//    Float_t new_rec[] = {880,978,1064,1208,1298,1382,1502,1676,1800,1950,2100,2600,3000,4300,7000};


//    Float_t bins_gen[] = {930,1064,1298,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {930,1064,1298,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {930,1000,1064,1206,1298,1382,1502,1676,1800,2050,2200,2390,2600,4230,6000};

//    Float_t bins_gen[] = {943,1064,1294,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {943,1064,1294,1450,1800,2200,2600,6000};
//    Float_t new_rec[] = {943,969,1064,1110,1170,1294,1382,1502,1800,2050,2200,2390,2600,4230,6000};

//Ultimo 8 bins
//    Float_t bins_gen[] = {900,1068,1260,1455,1700,2000,2350,3000,6000};
//    Float_t bins_rec[] = {900,1068,1260,1455,1700,2000,2350,3000,6000};
//    Float_t new_rec[] = {900,950,1068,1195,1260,1382,1470,1526,1700,1780,2000,2150,2350,2450,3000,3450,6000};

//    Float_t bins_gen[] = {1000,1298,1502,1800,2200,2600,6000};
//    Float_t bins_rec[] = {1000,1298,1502,1800,2200,2600,6000};
//    Float_t new_rec[] = {1000,1185,1298,1430,1502,max,1800,2050,2200,2390,2600,4230,6000};

//    Float_t bins_gen[] = {900,1070,1455,1700,2000,2350,3000,5500};
//    Float_t bins_rec[] = {900,1070,1455,1700,2000,2350,3000,5500};
//    Float_t new_rec[] = {900,985,1070,1260,1455,1575,1700,1850,2000,2175,2350,2650,3000,4250,5500};

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    Int_t  binnum_rec = sizeof(bins_rec)/sizeof(Float_t) - 1;

//For closure test

    TH1F *Mttbar_rec_closure = new TH1F("Mttbar_rec_closure","",newrec,new_rec);
    TH1F *Mttbar_gen_closure = new TH1F("Mttbar_gen_closure","",binnum_gen,bins_gen);
    TH2F *Smearing_Matrix_closure = new TH2F("Smearing_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Closure_Matrix = new TH2F("Closure_Matrix","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Migration_Matrix_closure = new TH2F("Migration_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);

//optimization
    TH1F *Mttbar_FullPS = new TH1F("Mttbar_FullPS","",binnum_rec,bins_rec);
    TH2F *Smearing_Matrix = new TH2F("Smearing_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *Mttbar_rec = new TH1F("Mttbar_rec","",binnum_rec,bins_rec);
    TH1F *Mttbar_gen_rec = new TH1F("Mttbar_gen_rec","",binnum_rec,bins_rec);
    TH1F *Mttbar_Visgen = new TH1F("Mttbar_Visgen","",binnum_rec,bins_rec);
    TH1F *Eff_Vis = new TH1F("Eff_Vis","",binnum_rec,bins_rec);
//    TH1F *Acceptance = new TH1F("Acceptance","",binnum_rec,bins_rec);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Response_Matrix = new TH2F("Response_Matrix","",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","Transition Probability",binnum_gen,bins_gen,binnum_rec,bins_rec);
    TH1F *EfficiencyxAcceptance = new TH1F("Efficiency*Acceptance","",binnum_rec,bins_rec);
    TH1F *Stability = new TH1F("Stability","",binnum_rec,bins_rec);
    TH1F *Purity = new TH1F("Purity","",binnum_rec,bins_rec);

//    treereco1->Project("Mttbar_FullPS","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Mttbar_gen_rec","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Mttbar_rec","Mttbar");
    treereco2->Project("Mttbar_Visgen","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
    treereco->Project("Smearing_Matrix","Mttbar:TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");

//Llenando histogramas para closure test


      string InvMass = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";
      treereco->Project("Smearing_Matrix_closure",Form("%s < 880. ? TMath::Max(881,%s): (%s > 4000. ? TMath::Min(3999.99,%s) : %s):%s < 880. ? TMath::Max(881,%s): (%s > 4000 ? TMath::Min(3999.99,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),"Mttbar","Mttbar","Mttbar","Mttbar","Mttbar"));
      treereco->Project("Mttbar_gen_closure",Form("%s < 880. ? TMath::Max(881,%s): (%s > 4000. ? TMath::Min(3999.99,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str()));
      treereco->Project("Mttbar_rec_closure",Form("%s < 880. ? TMath::Max(881,%s): (%s > 4000. ? TMath::Min(3999.99,%s) : %s)","Mttbar","Mttbar","Mttbar","Mttbar","Mttbar"));

    for (int i=1;i<=binnum_gen;i++){
	Eff_Vis->SetBinContent(i,Mttbar_rec->GetBinContent(i)/Mttbar_Visgen->GetBinContent(i));
//        Acceptance->SetBinContent(i,Mttbar_Visgen->GetBinContent(i)/Mttbar_FullPS->GetBinContent(i));
    }
   
    for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
        Response_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Mttbar_Visgen->GetBinContent(b));
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
 //        EfficiencyxAcceptance->SetBinContent(m,Eff_Vis->GetBinContent(m)*Acceptance->GetBinContent(m));
    }

    Purity->GetYaxis()->SetRangeUser(0,1.1);
    Purity->GetXaxis()->SetTitle("Mttbar [GeV]");
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

    TFile out("Data_unfolding_6bins.root","recreate");
    Mttbar_rec_closure->Write();
    Mttbar_gen_closure->Write();
    Migration_Matrix_closure->Write();
    Mttbar_rec->Write();
    Mttbar_gen_rec->Write();
    Mttbar_Visgen->Write();
    Eff_Vis->Write();
//    Acceptance->Write();
    Smearing_Matrix_closure->Write();

    Purity_Matrix->Write();
    Migration_Matrix->Write();
    Response_Matrix->Write();
    Stability->Write();
    Purity->Write();
    EfficiencyxAcceptance->Write();

    TCanvas* cc = new TCanvas("Scatter","Scatter",2400,1200);

    cc->Divide(1,1);
    cc->cd(1);

    Purity->Draw();
    Stability->Draw("same");
//    Acceptance->Draw("same");
    Eff_Vis->Draw("same");

    Double_t Res_gauss[] = {83,130,164,191,220,307,526,1600};
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



    cc->Print("P&S_6bins.pdf");

    TCanvas* dd = new TCanvas("dd","dd",2400,1200);
    dd->Divide(1,1);
    dd->cd(1);

    Migration_Matrix->GetXaxis()->SetTitle("Mttbar_rec [GeV]");
    Migration_Matrix->GetYaxis()->SetTitle("Mttbar_gen [GeV]");
    Migration_Matrix->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix->Draw("text colz");
    dd->Print("Migration_Matrix_6bins.pdf");


    TCanvas* ee = new TCanvas("ee","ee",2400,1200);
    ee->Divide(1,1);
    ee->cd(1);

    Migration_Matrix_closure->GetXaxis()->SetTitle("Mttbar_gen [GeV]");
    Migration_Matrix_closure->GetYaxis()->SetTitle("Mttbar_rec [GeV]");
    Migration_Matrix_closure->GetZaxis()->SetRangeUser(0,1);
    Migration_Matrix_closure->Draw("text2 colz");
    ee->Print("Closure_Matrix_6bins.pdf");


    auto ProY1 = (TH1*) Smearing_Matrix->ProjectionY("ProY1",1,1);
    auto ProY2 = (TH1*)Smearing_Matrix->ProjectionY("ProY2",2,2);
    auto ProY3 = (TH1*)Smearing_Matrix->ProjectionY("ProY3",3,3);
    auto ProY4 = (TH1*)Smearing_Matrix->ProjectionY("ProY4",4,4);
    auto ProY5 = (TH1*)Smearing_Matrix->ProjectionY("ProY5",5,5);
    auto ProY6 = (TH1*)Smearing_Matrix->ProjectionY("ProY6",6,6);
    auto ProY7 = (TH1*)Smearing_Matrix->ProjectionY("ProY7",7,7);
    TH1* hh1 = (TH1*) gDirectory->Get("ProY1");
    TH1* hh2 = (TH1*) gDirectory->Get("ProY2");
    TH1* hh3 = (TH1*) gDirectory->Get("ProY3");
    TH1* hh4 = (TH1*) gDirectory->Get("ProY4");
    TH1* hh5 = (TH1*) gDirectory->Get("ProY5");
    TH1* hh6 = (TH1*) gDirectory->Get("ProY6");
    TH1* hh7 = (TH1*) gDirectory->Get("ProY7");
    TFile *MyFile2 = new TFile("Gauss.root","recreate");
    gDirectory->WriteObject(hh1,"ProY1");
    gDirectory->WriteObject(hh2,"ProY2");
    gDirectory->WriteObject(hh3,"ProY3");
    gDirectory->WriteObject(hh4,"ProY4");
    gDirectory->WriteObject(hh5,"ProY5");
    gDirectory->WriteObject(hh6,"ProY6");
    gDirectory->WriteObject(hh7,"ProY7");


}





/*
    Int_t nentries = treereco->GetEntries();
    TH1F *hpx   = new TH1F("hpx","px distribution",100,0,1000);
    Float_t Hola;
    treereco->SetBranchAddress("GenParticles.m_pt[2]",&Hola);
    for(Long64_t t=0;t<nentries;t++){
    treereco->GetEntry(t);
    hpx->Fill(Hola);
    }
    TChain *chreco = new TChain("AnalysisTree","");
    chreco->Add("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_muon/");
    TTree *treereco = (TTree*) chreco;
    Float_t bins_gen[] = {350,820,1158,1660,2350,3955};
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    TH1F *hb0 = new TH1F("hb0","",binnum_gen,bins_gen);
    TH1F *hb2 = new TH1F("hb2","top",50,0,300);
    TH1F *hb3 = new TH1F("hb3","antitop",50,0,300);
    treereco->Project("hb2","TMath::Sqrt(GenParticles.m_energy[2]*GenParticles.m_energy[2] - GenParticles.m_pt[2]*GenParticles.m_pt[2]*TMath::CosH(GenParticles.m_eta[2])*TMath::CosH(GenParticles.m_eta[2]))");
    treereco->Project("hb3","TMath::Sqrt(GenParticles.m_energy[3]*GenParticles.m_energy[3] - GenParticles.m_pt[3]*GenParticles.m_pt[3]*TMath::CosH(GenParticles.m_eta[3])*TMath::CosH(GenParticles.m_eta[3]))");
// Variables
//  Px_1 + Px_2 = GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3])
//  Py_1 + Py_2 = GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3])
//  Pz_1 + Pz_2 = GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_phi[3])
//  E_1 + E_2 = GenParticles.m_energy[2] + GenParticles.m_energy[3]
    treereco->Project("hb0","TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))");
*/   
//    TFile out("out_Visible_O7.root","recreate");
//      hpx->Write();
//    hb2->Write();
//    hb3->Write();
//    hb0->Write();
//}
/*
    TFile *f = new TFile("/nfs/dust/cms/user/hugobg/ZPrimeSemi/Preselection_2016/workdir_Preselection/workdir_Selection//uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root");
    TTree *treereco = (TTree*)f->Get("AnalysisTree");
    treereco->SetMakeClass(1);
    Int_t ntracks;
    Float_t pt[1000];
    TBranch *bntrack = treereco->GetBranch("GenParticles");
    TBranch *bpx = treereco->GetBranch("GenParticles.m_pt");
    bntrack->SetAddress(&ntracks);
    bpx->SetAddress(pt);
    Int_t nevent = (Int_t)treereco->GetEntries();
    for(Int_t i=0;i<nevent;i++){
//	 bntrack->GetEntry(i);
       bpx->GetEntry(i);
       cout << pt[2] << endl;
    }
*/
