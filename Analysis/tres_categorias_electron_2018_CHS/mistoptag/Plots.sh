#!/bin/bash

rm -f *.txt

#declare -a StringArray=("N_Ak4" "N_Ak8" "Mttbar" "lep1_pt" "MET_pt" "Ak8_j1_pt" "DeltaY")
declare -a StringArray=("N_Ak4")

for var in ${StringArray[@]}; do

        python makePlots_fromAnalysisTree.py  ${var}

done

