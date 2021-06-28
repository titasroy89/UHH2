#!/bin/bash

rm -f out_unfolding
rm -f *.root 
rm -f *.pdf

pdf_name='perfect'
root -l -b -q "Ac_perfect.C(\"${pdf_name}\")" #> out_Ac_perfect
root -l -b -q "unfolding.C(\"${pdf_name}\")" #> out_unfolding

