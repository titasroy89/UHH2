#!/bin/bash

rm -f *.txt

#declare -a StringArray=("N_Ak4" "N_Ak8" "Mttbar" "lep1_pt" "MET_pt" "Ak8_j1_pt")

declare -a StringArray=("Ak8_j1_tau32" "Ak8_j1_tau21" "Ak8_j1_pt" "Ak8_j1_mSD")
for var in ${StringArray[@]}; do

        #python test.py  ${var} -b
#        python makePlots_fromAnalysisTree.py ${var} -b

      python rec_chi2.py  ${var} -b 
done

