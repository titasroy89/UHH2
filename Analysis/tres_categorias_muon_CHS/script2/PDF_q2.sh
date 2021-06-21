#!/bin/bash

python createq2templates_SR1T.py 0 0
python New_q2_SR1T.py
mv templates_q2_SR1T.root q2_btag.root

python createq2templates_SR1T.py 1 0
python New_q2_SR1T.py
mv templates_q2_SR1T.root q2_ttag.root

python createq2templates_SR1T.py 0 1
python New_q2_SR1T.py
mv templates_q2_SR1T.root q2_wtag.root

#python createpdftemplates_SR1T.py 0 0
#python New_PDF_SR1T.py
#mv templates_pdf_SR1T.root pdf_btag.root

#python createpdftemplates_SR1T.py 1 0
#python New_PDF_SR1T.py
#mv templates_pdf_SR1T.root pdf_ttag.root

#python createpdftemplates_SR1T.py 0 1
#python New_PDF_SR1T.py
#mv templates_pdf_SR1T.root pdf_wtag.root

#rm -f -r pdf.root
rm -f -r q2.root

#hadd pdf.root pdf_btag.root pdf_ttag.root pdf_wtag.root
hadd q2.root q2_btag.root q2_ttag.root q2_wtag.root


