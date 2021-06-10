#!/usr/bin/env bash

#declare -a arr=("Mttbar" "DeltaY" "Cos_theta_thad_tlep" "DeltaPhi_thad_lepton" "Rapidity_had" "Rapidity_lep" "Rapidity_ttbar" "pT_had" "pT_lep" "pT_ttbar" "tlead_pT" "tsublead_pT")
declare -a arr=("Mttbar")
for i in "${arr[@]}"
do
     root -l -b -q "Stack.C(\"${i}\")"

done

mv *.pdf pdf/
