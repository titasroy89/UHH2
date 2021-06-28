Float_t mean(Int_t data[], Int_t N, Int_t gen)

{
   Float_t sum = 0.0, mean, standardDeviation = 0.0, center = 0.0;
   Int_t i;
   for(i = 0; i < N; ++i){
      sum += (data[i] - gen);
   }
   mean = (float) sum / N;
   return mean;
}

/* para crear las gaussianas, deb Float_t mean(Int_t data[], Int_t N, Int_t gen, Int_t bin) y hacer loop en solo ese bin
TH1F *G = new TH1F("G","",50,-1,1);
TFile *MyFile2 = new TFile(Form("g_%d_%d.root",N,bin),"recreate");
center = (float) (data[i]-gen)/gen;
G->Fill(center);
gDirectory->WriteObject(G,"G");
*/
