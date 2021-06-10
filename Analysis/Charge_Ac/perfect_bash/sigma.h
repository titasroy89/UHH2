
Float_t sigma(Int_t data[], Int_t N, Int_t gen)

{
      Float_t sum = 0.0, mean, standardDeviation = 0.0;
      Int_t i;
      for(i = 0; i < N; ++i){
        sum += (data[i] - gen);
      }
      mean = (float) sum / N;
      for(i = 0; i < N; ++i){
        standardDeviation += pow((data[i]-gen) - mean, 2);
      }
      Float_t sigma = sqrt(standardDeviation/N);

      return sigma;
}



