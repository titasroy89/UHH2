#!/bin/bash

rm -f *.txt

#declare -a StringArray=("N_Ak4" "N_Ak8" "Mttbar" "lep1_pt" "MET_pt" "Ak8_j1_pt")

declare -a StringArray3=("ttagN==1" "wtagN==1" "btagN==0")
declare -a StringArray=("Ak8_j1_pt")

for var in ${StringArray[@]}; do
for var2 in ${StringArray3[@]}; do

        #python test.py  ${var} -b
#        python makePlots_fromAnalysisTree.py ${var} -b

      python rec_chi2.py  "${var}"  "${var2}" -b 
done
done
