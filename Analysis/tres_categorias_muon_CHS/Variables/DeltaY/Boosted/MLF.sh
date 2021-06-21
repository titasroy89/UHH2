#!/bin/bash

rm -f *.txt

declare -a StringArray=("DeltaY")
#declare -a StringArray2=("(ttagN==0 & wtagN ==0 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)" "(ttagN==0 & wtagN ==1 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)" "(ttagN==1 & wtagN ==0 & btagN>=1 & Mttbar > 900 & rec_chi2 < 30)")
#declare -a StringArray2=("(Mttbar > 900 & rec_chi2 < 30)")
declare -a StringArray2=("rec_chi2 < 30 && Mttbar > 900")
year='2018'
num=0
var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'


for i in {1..1}; do
for var in ${StringArray[@]}; do
   for region in "${StringArray2[@]}"; do
#         echo ${region}
#         python script/Input_file.py ${var} "${region}"
#   done
#        cd mistoptag
#        bash mistoptag.sh > Mistoptag.txt
#        cd .. 

#        cd script2
#        bash PDF_q2.sh   
#        cd ..
#  cp script2/pdf.root .
#  cp script2/q2.root .
#  hadd DeltaY_muon_3cat.root DeltaY_muon_3cat_ttag.root DeltaY_muon_3cat_wtag.root DeltaY_muon_3cat_btag.root     
#  python script/Get_UF_OF.py ${var}

#  python Yield_table.py

  num=$((num + 1))
  
  
#        python script/Get_UF_OF.py ${var}

#        python script/TxtDC.py ${var}
#        combineCards.py SR1T_muon=SR1T_muon${var}.txt > Combined_muon.txt
#        text2workspace.py Combined_muon.txt
#        combine -M MultiDimFit -d Combined_muon.txt --robustFit 1 -v 2 --saveFitResult --freezeParameters r --setParameters r=1 --saveNorm 

#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1  
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
#        plotImpacts.py -i impacts.json -o impacts        

        root -l -b -q "script/all_unfolding_data.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\")"

#        rm -f Input_undfolding_data.root
        hadd Input_undfolding_data.root Input_undfolding_data_.root DeltaY_muon.root 

#        python script/data_plotting.py ${var}        
#        python script/Unfolding_data.py ${var}

  if [ ${num} -eq 1 ]
  then
      mv *.* Variables/${var}/Boosted/ 
      mv Variables/${var}/Boosted/MLF.sh .
  fi
done
done
done




#var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'
