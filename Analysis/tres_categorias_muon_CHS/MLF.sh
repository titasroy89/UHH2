#!/bin/bash

rm -f *.txt

declare -a StringArray=("DeltaY")
declare -a StringArray2=("rec_chi2 < 30 && Mttbar > 900")

var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'
year='2018'

num=0

for i in {1..1}; do
for var in ${StringArray[@]}; do
   for region in "${StringArray2[@]}"; do

       num=$((num + 1))

        root -l -b -q "script/all_unfolding_data.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\")"
        python script/data_plotting.py ${var}        

        python script/Unfolding_data.py ${var}

#        if [ ${num} -eq 1 ]
#        then
#            mv *.* Variables/${var}/Boosted/ 
#            mv Variables/${var}/Boosted/MLF.sh .
#        fi


    done

done
done

