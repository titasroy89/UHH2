
Float_t sigma(Int_t data[])

{
      Float_t sum = 0.0, mean, standardDeviation = 0.0;
      Int_t i;
      for(i = 0; i < 1000; ++i){
        sum += data[i];
      }
      mean = sum / 1000;
      for(i = 0; i < 1000; ++i){
        standardDeviation += pow(data[i] - mean, 2);
      }
      Float_t sigma = sqrt(standardDeviation/1000);

      return sigma;
}



