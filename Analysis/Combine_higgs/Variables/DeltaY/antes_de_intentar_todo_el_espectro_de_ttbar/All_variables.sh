#!/bin/bash

declare -a StringArray=("met_pt" "Mttbar" "pT_ttbar" "DeltaY" "Rapidity_ttbar" "Rapidity_had" "Rapidity_lep" "DeltaPhi_thad_lepton" "Cos_theta_thad_tlep" "Mu_E" "Mu_eta" "Mu_phi" "Mu_pt" "ak8jet1_eta" "ak8jet1_pt" )

for var in ${StringArray[@]}; do
   for (( t=0; t<1; t++ ))     
      do
      for (( b=0; b<=1; b++ )) 
        do 
        python script2/makePlots_fromAnalysisTree.py ${var} "$t" "$b"
      done
   done 
done


