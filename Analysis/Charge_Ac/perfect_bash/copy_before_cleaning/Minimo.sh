#!/bin/bash

rm -f *.pdf
for max in {9401..9599..10}

#for max in {40}
do
  	root -l -b -q "Mass_6bins.C(${max})" 
        root -l -b -q unfold_susan.C
done

