#!/bin/bash

echo -n "Enter a number (1->perfect, 2->extended, 3->closure):  "
read VAR


if [ $VAR -eq 1 ];
then
     pdf_name='perfect'
     root -l -b -q "Ac_perfect.C(\"${pdf_name}\")" > out_Ac_perfect
     root -l -b -q "unfolding.C(\"${pdf_name}\")" > out_unfolding
elif [ $VAR -eq 2 ];
then
     pdf_name='extended'
     root -l -b -q "Ac_extended.C(\"${pdf_name}\")" > out_Ac_extended
     root -l -b -q "unfolding_extended.C(\"${pdf_name}\")" > out_unfolding
else 
      pdf_name='Clsr'
      root -l -b -q "Ac.C(\"${pdf_name}\")" > out_Ac
      root -l -b -q "unfolding.C(\"${pdf_name}\")" > out_unfolding
fi

mv *.pdf pdf
mv *.root root

#more out_unfolding
