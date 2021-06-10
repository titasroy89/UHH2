#!/bin/bash

rm -f *.txt

declare -a StringArray2=("rec_chi2 < 30 && Mttbar < 2000")

year='2018'

num=0


for region in "${StringArray2[@]}"; do

        root -l -b -q "N_Ak4.C(\"${var}\",\"${var_gen}\",\"${region}\",\"${year}\")"
#        python data_plotting.py ${var} ${jet}        
        python data_plotting_chs.py ${var} ${jet}
 
done
