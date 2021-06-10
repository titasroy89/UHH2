#!/bin/bash

rm -f *.pdf
for max in {1898..1910..1}
#for max in 3970
#for max in 40

#for max in {40}
do
  	root -l -b -q "UMass_6bins.C(${max})" 
        root -l -b -q unfold_susan.C
done

