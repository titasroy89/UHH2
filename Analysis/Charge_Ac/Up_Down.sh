#!/bin/bash

declare -a StringArray=("ttbar_pu" "ttbar_cferr1" "ttbar_cferr2" "ttbar_lf" ttbar_"hf" "ttbar_hfstats1" "ttbar_hfstats2" "ttbar_jes" "ttbar_lfstats1" "ttbar_lfstats2" "ttbar_Trigger" "ttbar_MuonID" )
 
for val in ${StringArray[@]}; do
    root -l -b -q "hist_unc.C(\"${val}\")"
done

