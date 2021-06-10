
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

    //Mass
    Float_t bins_gen_Mass[] = {880,1060,1300,1520,1900,2300,3000,7000};
    Float_t bins_rec_Mass[] = {880,1060,1300,1520,1900,2300,3000,7000};
    Float_t new_rec_Mass[] = {880,1060,1180,1300,1410,1520,1710,1900,2100,2300,2650,3000,7000};

    Int_t  newrec_Mass = sizeof(new_rec_Mass)/sizeof(Float_t) - 1;
    Int_t  binnum_gen_Mass = sizeof(bins_gen_Mass)/sizeof(Float_t) - 1;
    Int_t  binnum_rec_Mass = sizeof(bins_rec_Mass)/sizeof(Float_t) - 1;

//For closure test


    //rapidity
    TH1F *DeltaY_rec_closure = new TH1F("DeltaY_rec_closure","",newrec,new_rec);
    TH1F *DeltaY_gen_closure = new TH1F("DeltaY_gen_closure","",binnum_gen,bins_gen);
    TH2F *Smearing_Matrix_closure = new TH2F("Smearing_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Closure_Matrix = new TH2F("Closure_Matrix","",newrec,new_rec,binnum_rec,bins_rec);
    TH2F *Migration_Matrix_closure = new TH2F("Migration_Matrix_closure","",newrec,new_rec,binnum_rec,bins_rec);

    //Mass
    TH1F *Mass_rec_closure = new TH1F("Mass_rec_closure","",newrec_Mass,new_rec_Mass);
    TH1F *Mass_gen_closure = new TH1F("Mass_gen_closure","",binnum_gen_Mass,bins_gen_Mass);
    TH2F *Mass_Smearing_Matrix_closure = new TH2F("Mass_Smearing_Matrix_closure","",newrec_Mass,new_rec_Mass,binnum_rec_Mass,bins_rec_Mass);
    TH2F *Mass_Closure_Matrix = new TH2F("Mass_Closure_Matrix","",newrec_Mass,new_rec_Mass,binnum_rec_Mass,bins_rec_Mass);
    TH2F *Mass_Migration_Matrix_closure = new TH2F("Mass_Migration_Matrix_closure","",newrec_Mass,new_rec_Mass,binnum_rec_Mass,bins_rec_Mass);

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

    //Mass
    TH1F *Mass_FullPS = new TH1F("Mass_FullPS","",binnum_rec_Mass,bins_rec_Mass);
    TH2F *Mass_Smearing_Matrix = new TH2F("Mass_Smearing_Matrix","",binnum_gen_Mass,bins_gen_Mass,binnum_rec_Mass,bins_rec_Mass);
    TH1F *Mass_rec = new TH1F("Mass_rec","",binnum_rec_Mass,bins_rec_Mass);
    TH1F *Mass_gen_rec = new TH1F("Mass_gen_rec","",binnum_rec_Mass,bins_rec_Mass);
    TH1F *Mass_Visgen = new TH1F("Mass_Visgen","",binnum_rec_Mass,bins_rec_Mass);
    TH1F *Mass_Eff_Vis = new TH1F("Mass_Eff_Vis","",binnum_rec_Mass,bins_rec_Mass);
//    TH1F *Mass_Acceptance = new TH1F("Mass_Acceptance","",binnum_rec_Mass,bins_rec_Mass);
    TH2F *Mass_Purity_Matrix = new TH2F("Mass_Purity_Matrix","",binnum_gen_Mass,bins_gen_Mass,binnum_rec_Mass,bins_rec_Mass);
    TH2F *Mass_Response_Matrix = new TH2F("Mass_Response_Matrix","",binnum_gen_Mass,bins_gen_Mass,binnum_rec_Mass,bins_rec_Mass);
    TH2F *Mass_Migration_Matrix = new TH2F("Mass_Migration_Matrix","Transition Probability",binnum_gen_Mass,bins_gen_Mass,binnum_rec_Mass,bins_rec_Mass);
//    TH1F *Mass_EfficiencyxAcceptance = new TH1F("Mass_Efficiency*Acceptance","",binnum_rec_Mass,bins_rec_Mass);
    TH1F *Mass_Stability = new TH1F("Mass_Stability","",binnum_rec_Mass,bins_rec_Mass);
    TH1F *Mass_Purity = new TH1F("Mass_Purity","",binnum_rec_Mass,bins_rec_Mass);


//Gen Variables 

    //Rapidity
    string rap_diff = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

    //Mass
    string InvMass = "TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))";


//Optimization Matrix


    //Rapidity 
//    treereco1->Project("DeltaY_FullPS",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("DeltaY_gen_rec",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("DeltaY_rec",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"));
    treereco2->Project("DeltaY_Visgen",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()));
    treereco->Project("Smearing_Matrix",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s):%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),"DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"));

     //Mass
//    treereco1->Project("Mass_FullPS",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str()));
    treereco->Project("Mass_gen_rec",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str()));
    treereco->Project("Mass_rec",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)","Mttbar","Mttbar","Mttbar","Mttbar","Mttbar"));
    treereco2->Project("Mass_Visgen",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str()));
    treereco->Project("Mass_Smearing_Matrix",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s):%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),"Mttbar","Mttbar","Mttbar","Mttbar","Mttbar"));



//Llenando histogramas para closure test


      //rapidity
      treereco->Project("Smearing_Matrix_closure",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s):%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),"DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",8444,8491);
      treereco->Project("DeltaY_gen_closure",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)",rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str(),rap_diff.c_str()),"","",7990,500);
      treereco->Project("DeltaY_rec_closure",Form("%s < -2. ? TMath::Max(-1.75,%s): (%s > 2. ? TMath::Min(1.75,%s) : %s)","DeltaY","DeltaY","DeltaY","DeltaY","DeltaY"),"","",7990,500);


      //Mass
      treereco->Project("Mass_Smearing_Matrix_closure",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s):%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),"Mttbar","Mttbar","Mttbar","Mttbar","Mttbar"),"","",8444,8491);
      treereco->Project("Mass_gen_closure",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)",InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str(),InvMass.c_str()),"","",7990,500);
      treereco->Project("Mass_rec_closure",Form("%s < 880. ? TMath::Max(880.001,%s): (%s > 7000. ? TMath::Min(6999.,%s) : %s)","Mttbar","Mttbar","Mttbar","Mttbar","Mttbar"),"","",7990,500);



//Calculando la optimizacion

    for (int i=1;i<=binnum_gen;i++){

        //rapidity
	Eff_Vis->SetBinContent(i,DeltaY_rec->GetBinContent(i)/DeltaY_Visgen->GetBinContent(i));
//        Acceptance->SetBinContent(i,DeltaY_Visgen->GetBinContent(i)/DeltaY_FullPS->GetBinContent(i));
    }

    for (int i=1;i<=binnum_gen_Mass;i++){
        //Mass
        Mass_Eff_Vis->SetBinContent(i,Mass_rec->GetBinContent(i)/Mass_Visgen->GetBinContent(i));
//        Mass_Acceptance->SetBinContent(i,Mass_Visgen->GetBinContent(i)/Mass_FullPS->GetBinContent(i));

    }

   
    for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){

        //rapidity
        Response_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/DeltaY_Visgen->GetBinContent(b));
        Migration_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Smearing_Matrix->Integral(1,binnum_gen,b,b));

        //solo los elementos en la diagonal importan
        Purity_Matrix->SetBinContent(a,b,Smearing_Matrix->GetBinContent(a,b)/Smearing_Matrix->Integral(a,a,1,binnum_gen));

       }
     }



    for(int a=1;a<=binnum_gen_Mass;a++){
       for(Int_t b=1;b<=binnum_gen_Mass;b++){
  
        //Mass
        Mass_Response_Matrix->SetBinContent(a,b,Mass_Smearing_Matrix->GetBinContent(a,b)/Mass_Visgen->GetBinContent(b));
        Mass_Migration_Matrix->SetBinContent(a,b,Mass_Smearing_Matrix->GetBinContent(a,b)/Mass_Smearing_Matrix->Integral(1,binnum_gen,b,b));

        //solo los elementos en la diagonal importan
        Mass_Purity_Matrix->SetBinContent(a,b,Mass_Smearing_Matrix->GetBinContent(a,b)/Mass_Smearing_Matrix->Integral(a,a,1,binnum_gen));        
        
       }
    }


    //fill migration matrix for colsure

    for(int a=1;a<=newrec;a++){
       for(Int_t b=1;b<=binnum_gen;b++){

        Migration_Matrix_closure->SetBinContent(a,b,Smearing_Matrix_closure->GetBinContent(a,b)/Smearing_Matrix_closure->Integral(1,newrec,b,b));

       }
    }


    for(int a=1;a<=newrec_Mass;a++){
       for(Int_t b=1;b<=binnum_gen_Mass;b++){

        Mass_Migration_Matrix_closure->SetBinContent(a,b,Mass_Smearing_Matrix_closure->GetBinContent(a,b)/Mass_Smearing_Matrix_closure->Integral(1,newrec,b,b)); 

       }
    }



   // Purity && Stability
    for(Int_t m=1;m<=binnum_gen;m++){
         Stability->SetBinContent(m,Migration_Matrix->GetBinContent(m,m));
         Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
//         EfficiencyxAcceptance->SetBinContent(m,Eff_Vis->GetBinContent(m)*Acceptance->GetBinContent(m));
    }


   // Purity && Stability
    for(Int_t m=1;m<=binnum_gen_Mass;m++){
         Mass_Stability->SetBinContent(m,Mass_Migration_Matrix->GetBinContent(m,m));
         Mass_Purity->SetBinContent(m,Mass_Purity_Matrix->GetBinContent(m,m));
//         Mass_EfficiencyxAcceptance->SetBinContent(m,Mass_Eff_Vis->GetBinContent(m)*Mass_Acceptance->GetBinContent(m));
    }

//rapidity
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

//Mass

    Mass_Purity->GetYaxis()->SetRangeUser(0,1.3);
    Mass_Purity->GetXaxis()->SetTitle("DeltaY [GeV]");
    Mass_Purity->SetLineColor(kRed);
    Mass_Purity->SetLineWidth(2);
    Mass_Stability->SetLineColor(kBlue);
    Mass_Stability->SetLineWidth(2);
    Mass_Eff_Vis->SetLineColor(kGreen+1);
    Mass_Eff_Vis->SetLineStyle(9);
    Mass_Eff_Vis->SetLineWidth(2);
//    Mass_Acceptance->SetLineColor(kViolet);
//    Mass_Acceptance->SetLineStyle(9);
//    Mass_Acceptance->SetLineWidth(2);
//    Mass_EfficiencyxAcceptance->SetLineColor(kViolet);
//    Mass_EfficiencyxAcceptance->SetLineStyle(9);
//    Mass_EfficiencyxAcceptance->SetLineWidth(2);


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

//Mass
    Mass_rec_closure->Write();
    Mass_gen_closure->Write();
    Mass_Migration_Matrix_closure->Write();
    Mass_rec->Write();
    Mass_gen_rec->Write();
    Mass_Visgen->Write();
    Mass_Eff_Vis->Write();
//    Mass_Acceptance->Write();
    Mass_Smearing_Matrix_closure->Write();
    Mass_Purity_Matrix->Write();
    Mass_Migration_Matrix->Write();
    Mass_Response_Matrix->Write();
    Mass_Stability->Write();
    Mass_Purity->Write();
//    Mass_EfficiencyxAcceptance->Write();


//Plots


// #################RAPIDITY#####################

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


// ################# MASS #####################

    TCanvas* cc_mass = new TCanvas("Scatter_Mass","Scatter_Mass",2400,1200);

    cc_mass->Divide(1,1);
    cc_mass->cd(1);

    Mass_Purity->Draw();
    Mass_Stability->Draw("same");
//    Mass_Acceptance->Draw("same");
    Mass_Eff_Vis->Draw("same");

    Double_t Mass_Res_gauss[] = {90.4,141.,200,203,286,313,860};
    Double_t Mass_Bin_size[binnum_gen_Mass];
    Double_t Mass_Relative_Resolution[binnum_gen_Mass];

    TH1F *Mass_Ratio_res = new TH1F("Mass_Ratio_res","",binnum_gen_Mass,bins_gen_Mass);

    for(int j=1;j<=binnum_gen_Mass;j++){
            Mass_Bin_size[j-1] = bins_gen_Mass[j] - bins_gen_Mass[j-1];
            Mass_Relative_Resolution[j-1]=Mass_Res_gauss[j-1]/Mass_Bin_size[j-1];
            Mass_Ratio_res->SetBinContent(j,Mass_Relative_Resolution[j-1]);
    }

    Mass_Ratio_res->SetLineColor(kYellow+4);
    Mass_Ratio_res->SetLineWidth(2);
    Mass_Ratio_res->SetLineStyle(9);
    Mass_Ratio_res->Draw("same");

    TLegend leg_Mass(.65, .65, .85, .85, "");
    leg_Mass.SetFillColor(0);
    leg_Mass.AddEntry(Mass_Purity, "Purity");
    leg_Mass.AddEntry(Mass_Stability, "Stability");
    leg_Mass.AddEntry(Mass_Eff_Vis,"Eff_Vis");
//    leg_Mass.AddEntry(Mass_Acceptance,"Acceptance");
    leg_Mass.AddEntry(Mass_Ratio_res,"Resolution (Gauss)");
    leg_Mass.SetBorderSize(0);
    leg_Mass.Draw("Same");

    TLegend leg2_Mass(.20, .75, .35, .85, "");
    leg2_Mass.AddEntry((TObject*)0, "#mu + jets", "");
    leg2_Mass.SetBorderSize(0);
    leg2_Mass.Draw("same");

    cc_mass->Print(Form("Mass_P&S_%s.pdf",pdf_name.c_str()));

    TCanvas* dd_mass = new TCanvas("dd_mass","dd_mass",2400,1200);
    dd_mass->Divide(1,1);
    dd_mass->cd(1);

    Mass_Migration_Matrix->GetXaxis()->SetTitle("Mttbar_rec [GeV]");
    Mass_Migration_Matrix->GetYaxis()->SetTitle("Mttbar_gen [GeV]");
    Mass_Migration_Matrix->GetZaxis()->SetRangeUser(0,1);
    Mass_Migration_Matrix->Draw("text colz");
    dd_mass->Print(Form("Mass_Migration_matrix_%s.pdf",pdf_name.c_str()));


    TCanvas* ee_mass = new TCanvas("ee_mass","ee_mass",2400,1200);
    ee_mass->Divide(1,1);
    ee_mass->cd(1);

    Mass_Migration_Matrix_closure->GetXaxis()->SetTitle("Mttbar_rec [GeV]");
    Mass_Migration_Matrix_closure->GetYaxis()->SetTitle("Mttbar_gen [GeV]");
    Mass_Migration_Matrix_closure->GetZaxis()->SetRangeUser(0,1);
    Mass_Migration_Matrix_closure->Draw("text2 colz");
    ee_mass->Print(Form("Mass_Closure_Matrix_%s.pdf",pdf_name.c_str()));


    //uncomment only to create projections
    #define TEST0
     
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


    auto ProY1_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY1_Mass",1,1);
    auto ProY2_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY2_Mass",2,2);
    auto ProY3_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY3_Mass",3,3);
    auto ProY4_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY4_Mass",4,4);
    auto ProY5_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY5_Mass",5,5);
    auto ProY6_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY6_Mass",6,6);
    auto ProY7_Mass = (TH1*)Mass_Smearing_Matrix->ProjectionY("ProY7_Mass",7,7);

    TH1* hh1_Mass = (TH1*) gDirectory->Get("ProY1_Mass");
    TH1* hh2_Mass = (TH1*) gDirectory->Get("ProY2_Mass");
    TH1* hh3_Mass = (TH1*) gDirectory->Get("ProY3_Mass");
    TH1* hh4_Mass = (TH1*) gDirectory->Get("ProY4_Mass");
    TH1* hh5_Mass = (TH1*) gDirectory->Get("ProY5_Mass");
    TH1* hh6_Mass = (TH1*) gDirectory->Get("ProY6_Mass");
    TH1* hh7_Mass = (TH1*) gDirectory->Get("ProY7_Mass");
    TH1* hh8_Mass = (TH1*) gDirectory->Get("ProY8_Mass");

    TFile *MyFile3 = new TFile("Gauss_Mass.root","recreate");
    gDirectory->WriteObject(hh1_Mass,"ProY1_Mass");
    gDirectory->WriteObject(hh2_Mass,"ProY2_Mass");
    gDirectory->WriteObject(hh3_Mass,"ProY3_Mass");
    gDirectory->WriteObject(hh4_Mass,"ProY4_Mass");
    gDirectory->WriteObject(hh5_Mass,"ProY5_Mass");
    gDirectory->WriteObject(hh6_Mass,"ProY6_Mass");
    gDirectory->WriteObject(hh7_Mass,"ProY7_Mass");
    gDirectory->WriteObject(hh8_Mass,"ProY8_Mass");


    #endif

}

