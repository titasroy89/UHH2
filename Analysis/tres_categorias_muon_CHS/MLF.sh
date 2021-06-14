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

#        cd mistoptag
#        bash mistoptag.sh > Mistoptag.txt
#        cd .. 

#        cd script2
#        bash PDF_q2.sh   
#        cd ..
        cp script2/pdf.root .
        cp script2/q2.root .
 
    
        num=$((num + 1))

#        python script/Input_file.py ${var}
#        python script/Get_UF_OF.py ${var}
#        python script/TxtDC.py ${var}
#        combineCards.py SR1T_muon=SR1T_muon${var}.txt > Combined_muon.txt
#        text2workspace.py Combined_muon.txt

#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1  
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
#        plotImpacts.py -i impacts.json -o impacts        

        root -l -b -q "script/all_unfolding_data.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\")"

        rm -f Input_undfolding_data.root
        hadd Input_undfolding_data.root Input_undfolding_data_.root pdf.root q2.root 

        python script/data_plotting.py ${var}        
        python script/Unfolding_data.py ${var}

        if [ ${num} -eq 1 ]
        then
            mv *.* Variables/${var}/Boosted/ 
            mv Variables/${var}/Boosted/MLF.sh .
        fi


    done

done
done

