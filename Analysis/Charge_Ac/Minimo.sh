#!/bin/bash


var_name='DeltaY'
var_gen='TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))'   
year='2016'

python makePlots_fromAnalysisTree.py ${year} ${var_name}
root -l -b -q "all_unfolding_data.C(\"${var_name}\",\"${var_gen}\",\"${year}\")"
python Unfolding_data.py ${var_name}
<<COM1
var_name='Mttbar'
var_gen='TMath::Sqrt(TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2) - TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2) - TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2))'
year='2016'

python makePlots_fromAnalysisTree.py ${year} ${var_name}
root -l -b -q "all_unfolding_data.C(\"${var_name}\",\"${var_gen}\",\"${year}\")"
python Unfolding_data.py ${var_name}


var_name='pT_ttbar'
var_gen='TMath::Sqrt(TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2) + TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2))'
year='2016'

python makePlots_fromAnalysisTree.py ${year} ${var_name}
root -l -b -q "all_unfolding_data.C(\"${var_name}\",\"${var_gen}\",\"${year}\")"
python Unfolding_data.py ${var_name}


var_name='tlead_pT'
var_gen='GenParticles.m_pt[2] < GenParticles.m_pt[3] ? GenParticles.m_pt[3] : GenParticles.m_pt[2]'
year='2016'

python makePlots_fromAnalysisTree.py ${year} ${var_name}
root -l -b -q "all_unfolding_data.C(\"${var_name}\",\"${var_gen}\",\"${year}\")"
python Unfolding_data.py ${var_name}

COM1
mv *.pdf pdf/
mv *.root root/

#var_name='Rapidity_ttbar'
#var_gen='0.5*TMath::Log(((GenParticles.m_energy[2]+GenParticles.m_energy[3]) + (GenParticles.m_pt[2]+GenParticles.m_pt[3])*TMath::SinH((GenParticles.m_eta[2]+GenParticles.m_eta[3]))/((GenParticles.m_energy[2]+GenParticles.m_energy[3]) - (GenParticles.m_pt[2]+GenParticles.m_pt[3])*TMath::SinH((GenParticles.m_eta[2]+GenParticles.m_eta[3])))))'
#year='2016'

#python makePlots_fromAnalysisTree.py ${year} ${var_name}
#root -l -b -q "all_unfolding_data.C(\"${var_name}\",\"${var_gen}\",\"${year}\")"
#python Unfolding_data.py -b



