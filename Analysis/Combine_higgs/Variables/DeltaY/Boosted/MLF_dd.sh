#!/bin/bash

#declare -a StringArray=("Mttbar" "pT_ttbar" "DeltaY" "Rapidity_ttbar" "Rapidity_had" "Rapidity_lep" "DeltaPhi_thad_lepton" "Cos_theta_thad_tlep")
declare -a StringArray=("DeltaY")
#declare -a StringArray2=("ttagN == 1 && btagN >= 1 && wtagN == 0 && rec_chi2 < 30" "ttagN == 0 && btagN == 1 && wtagN == 0 && rec_chi2 < 30" "ttagN == 0 && btagN >= 1 && wtagN == 1 && rec_chi2 < 30")
declare -a StringArray2=("ttagN == 1 && btagN >= 1 && wtagN == 0 && rec_chi2 < 30")

var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'
year='2018'

num=0
for var in ${StringArray[@]}; do
   for region in "${StringArray2[@]}"; do

       num=$((num + 1))


       for (( c=0; c<=1; c++ ))
       do  
           gen_up=$(( $c + 1 ))  
           for (( d=0; d<=1; d++ ))
           do
              rec_up=$(( $d + 1 ))
              root -l -b -q "script/dd_unfolding.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\",${gen_up},$c,${rec_up},$d)"
           done 
       done



       python script/Full_sys.py
       python script/dd_plotting.py  

       python script/Unfolding_data.py ${var} 

        mv *.root Variables/${var}/diff
        mv *.pdf  Variables/${var}/diff


    done

done





