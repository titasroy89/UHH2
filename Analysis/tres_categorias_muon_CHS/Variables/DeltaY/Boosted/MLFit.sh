#!/bin/bash

#combineCards.py SR1T_muon=SR1T_muon.txt SR0T_muon=SR0T_muon.txt CR1_muon=CR1_muon.txt CR2_muon=CR2_muon.txt > Combined_muon.txt
#text2workspace.py Combined_muon.txt
#combine -M MultiDimFit -d Combined_muon.txt --robustFit 1 -v 2 --saveFitResult --freezeParameters r --setParameters r=0 
mlfitNormsToText -d Combined_muon.txt -w Combined_muon.root -o o.tex -f multidimfit.root:fit_mdf
#PostFitShapesFromWorkspace -d Combined_muon.txt -w Combined_muon.root -o MDF_shapes.root -f multidimfit.root:fit_mdf --postfit --sampling --print --freeze r=0
