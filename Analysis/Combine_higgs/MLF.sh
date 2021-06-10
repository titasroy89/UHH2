#!/bin/bash

#declare -a StringArray=("Mttbar" "pT_ttbar" "DeltaY" "Rapidity_ttbar" "Rapidity_had" "Rapidity_lep" "DeltaPhi_thad_lepton" "Cos_theta_thad_tlep")
declare -a StringArray=("DeltaY")
#declare -a StringArray2=("ttagN == 1 && btagN >= 1 && wtagN == 0 && rec_chi2 < 30" "ttagN == 0 && btagN == 1 && wtagN == 0 && rec_chi2 < 30" "ttagN == 0 && btagN >= 1 && wtagN == 1 && rec_chi2 < 30")
declare -a StringArray2=("0.9*(ttagN == 1 && btagN >= 1 && wtagN == 0 || ttagN == 0 && btagN == 1 && wtagN == 0) &&  rec_chi2 < 30 && Mttbar > 900")

var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'
year='2018'

num=0
for var in ${StringArray[@]}; do
   for region in "${StringArray2[@]}"; do

       num=$((num + 1))

        root -l -b -q "script/all_unfolding_data.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\")"
        
#        for (( c=0; c<=1; c++ ))
#        do  
#            gen_up=$(( $c + 1 ))  
#            for (( d=0; d<=1; d++ ))
#            do
#               rec_up=$(( $d + 1 ))
#               root -l -b -q "script/dd_unfolding.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\",${gen_up},$c,${rec_up},$d)"
#            done 
#        done

         
        
#        python script/Full_sys.py
#        python script/dd_plotting.py  

        python script/Unfolding_data.py ${var}
#        python script/data_plotting.py ${var}
#        python script/Unfolding_dd.py ${var} 

        if [ ${num} -eq 1 ]
        then
            mv *.* Variables/${var}/Boosted/ 
            mv Variables/${var}/Boosted/MLF.sh .
        fi

        if [ ${num} -eq 2 ]
        then
            mv *.* Variables/${var}/Resolved/
            mv Variables/${var}/Resolved/MLF.sh .
        fi

        if [ ${num} -eq 3 ]
        then
            mv *.* Variables/${var}/SemiResolved/
            mv Variables/${var}/SemiResolved/MLF.sh .
        fi

    done

done


