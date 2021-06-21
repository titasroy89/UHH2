#!/bin/bash

rm -f *.txt
rm -f *.root

declare -a StringArray=("DeltaY")
declare -a StringArray2=("rec_chi2 < 30 && Mttbar > 900")
declare -a StringArray3=("(ttagN==0 & wtagN ==0 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)" "(ttagN==0 & wtagN ==1 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)" "(ttagN==1 & wtagN ==0 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)")
year='2018'
num=0
var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'

for var in ${StringArray[@]}; do
for region in "${StringArray2[@]}"; do

    for regionn in "${StringArray3[@]}"; do
        python script/Input_file.py ${var} "${regionn}"
    done

#    cd script2
#    bash PDF_q2.sh
#    cd ..
 
    cp script2/pdf.root .
    cp script2/q2.root .
 
    hadd DeltaY_muon_3cat.root DeltaY_muon_3cat_ttag.root DeltaY_muon_3cat_wtag.root DeltaY_muon_3cat_btag.root pdf.root q2.root   
    python script/Get_UF_OF.py ${var}

    root -l -b -q "script/all_unfolding_data.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\")"
    hadd Input_undfolding_data.root Input_undfolding_data_.root DeltaY_muon.root

    python script/Unfolding_data.py ${var}
    cp Input_undfolding_data.root up_down
    cd up_down
    python plot_*.py
    cd ..

    mv *.* Variables/${var}/Boosted/
    mv Variables/${var}/Boosted/Run_all.sh .

 
done
done


