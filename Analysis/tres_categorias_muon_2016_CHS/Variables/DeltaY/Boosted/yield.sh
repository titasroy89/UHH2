#!/bin/bash

rm -f *.txt
rm -f *.root 

declare -a StringArray=("DeltaY")
declare -a StringArray2=("(ttagN==0 & wtagN ==0 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)" "(ttagN==0 & wtagN ==1 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)" "(ttagN==1 & wtagN ==0 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)")
year='2018'
num=0

for i in {1..1}; do
for var in ${StringArray[@]}; do
  for region in "${StringArray2[@]}"; do
         echo ${region}
         python script/Input_file.py ${var} "${region}"
  done

  hadd DeltaY_muon_3cat.root DeltaY_muon_3cat_ttag.root DeltaY_muon_3cat_wtag.root DeltaY_muon_3cat_btag.root     
  python script/Get_UF_OF.py ${var}

  num=$((num + 1))
  
  if [ ${num} -eq 1 ]
  then
      mv *.* Variables/${var}/Boosted/ 
      mv Variables/${var}/Boosted/MLF.sh .
  fi

done
done



