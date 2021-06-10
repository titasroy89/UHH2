#!/bin/bash

rm -f *.pdf

for max in {1..8..1}

do
    for min in 100 1000 10000
    do
        root -l -b -q "unfold_susan.C(${min},${max})"
    done
done

