#!/bin/bash

#declare -a StringArray=("Mttbar" "pT_ttbar" "DeltaY" "Rapidity_ttbar" "Rapidity_had" "Rapidity_lep" "DeltaPhi_thad_lepton" "Cos_theta_thad_tlep")
declare -a StringArray=("DeltaY")
var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'
year='2018'
for var in ${StringArray[@]}; do

        echo ${var}
#	python script/Input_file.py ${var}
#        python script/Get_UF_OF.py ${var}
#	python script/TxtDC.py ${var} 
#        mkdir Variables/${var}


#Fit para cuando haga unfolding with combine 
#        combineCards.py SR1T_muon=SR1T_muon${var}.txt SR0T_muon=SR0T_muon${var}.txt CR1_muon=CR1_muon${var}.txt > Combined_muon.txt
#        text2workspace.py Combined_muon.txt

#        combine -M MultiDimFit -d Combined_muon.txt --robustFit 1 -v 2 --saveFitResult --setParameterRanges qcd_rate=0,5
#        PostFitShapesFromWorkspace -d Combined_muon.txt -w Combined_muon.root -o MDF_shapes.root -f multidimfit.root:fit_mdf --postfit --sampling --print

#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 --setParameterRanges qcd_rate=0,5
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --robustFit 1 --doFits --setParameterRanges qcd_rate=0,5
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts_data.json
#        plotImpacts.py -i impacts_data.json -o impacts_data 

#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doInitialFit --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 --doFits --robustFit 1 -t -1 --expectSignal 1 --setParameterRanges qcd_rate=0,5
#        combineTool.py -M Impacts -d Combined_muon.root -m 125 -o impacts.json
#        plotImpacts.py -i impacts.json -o impacts

#        combine -M FitDiagnostics Combined_muon.txt --plots --robustFit 1 --saveWithUncertainties
#        python script/diffNuisances.py fitDiagnostics.root -g plots_t0.root >> fitResults_t0.txt

#        python script/makePlots_fromAnalysisTree.py

#        vim fitResults_t0.txt 
#        vim script/Unfolding_data.py

#        python script/stack.py ${var} 
 
        root -l -b -q "script/all_unfolding_data.C(\"${var}\",\"${var_gen}\",\"${year}\")"

        for (( c=0; c<=1; c++ ))
        do  
            gen_up=$(( $c + 1 ))  
            for (( d=0; d<=1; d++ ))
            do
               rec_up=$(( $d + 1 ))
               root -l -b -q "script/dd_unfolding.C(\"${var}\",\"${var_gen}\",\"${year}\",${gen_up},$c,${rec_up},$d)"
            done 
        done
        
        python script/Full_sys.py
        python script/dd_plotting.py 

        python script/Unfolding_data.py ${var}
        python script/Unfolding_dd.py ${var}   

        mv *.* Variables/${var}
        mv Variables/${var}/MLF.sh .


done


