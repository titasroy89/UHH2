#!/bin/bash

rm -f *.txt

declare -a StringArray=("rec_chi2")
#declare -a StringArray=("N_Ak4" "N_Ak8" "Mttbar" "lep1_pt" "MET_pt" "Ak8_j1_pt")
#declare -a StringArray=("Ak8_j1_pt" "Ak8_j1_tau32" "Ak8_j1_tau21" "Ak8_j1_mSD")
#declare -a StringArray=("Ak8_j1_pt")

for var in ${StringArray[@]}; do

        python rec_chi2.py rec_chi2 -b 
        #python test.py  ${var} -b
        #python makePlots_fromAnalysisTree.py ${var} -b
 
done

