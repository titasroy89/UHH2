import ROOT as R
import sys
import numpy as np
import math

nbins = 140
#file = R.TFile("rebin_PDF_SR1T.root")
file = R.TFile("mu_Test_4cat_PDF_SR1T.root")
values_per_bin_ttbar = {}
sigmas = []
for i in range(140):
    values_per_bin_ttbar[str(i)]  = []
#get values per bin
proc = ['ttbar_semi', 'ttbar_others', 'wjets', 'dy', 'singletop']
h_bkg = {}
h_tmp_PDF = {}
h_PDF = {}
 
fout = R.TFile("templates_pdf_SR1T.root", 'recreate')
for p in proc:

    file.cd('SR1T/'+p)
    dir = R.gDirectory.GetListOfKeys()

    for key in dir:
        a = key.GetName()
        print a
        h_bkg[a] = file.Get('SR1T/'+p+'/'+a).Clone()

    for i in range(1,h_bkg['wgtMC__PDF_0'].GetNbinsX()+1):
        h_tmp_PDF[str(i)]=R.TH1F("PDF"+str(i),"PDF"+str(i), 1000, 0., 1.)

    for key1 in dir:
        b = key1.GetName()
        for i in range(1,h_bkg[b].GetNbinsX()+1):
            value = h_bkg[b].GetBinContent(i)
            normal = h_bkg['wgtMC__PDF_0'].GetBinContent(i)
            if value>0 and normal>0: 
                 h_tmp_PDF[str(i)].Fill(value/normal)

    bin = h_bkg['wgtMC__PDF_0'].GetNbinsX()+1
    h_PDF["PDFUp"] = h_bkg['wgtMC__PDF_0'].Clone()
    h_PDF["PDFUp"].SetName("PDFUp")
    h_PDF["PDFUp"].SetTitle("PDFUp")
    h_PDF["PDFDown"] = h_bkg['wgtMC__PDF_0'].Clone()
    h_PDF["PDFDown"].SetName("PDFDown")
    h_PDF["PDFDown"].SetTitle("PDFDown")
    for i in range(1,bin):
        normal = h_bkg['nominal'].GetBinContent(i)
        h_PDF["PDFUp"].SetBinContent(i,normal*(h_tmp_PDF[str(i)].GetMean()+h_tmp_PDF[str(i)].GetRMS()))
        h_PDF["PDFDown"].SetBinContent(i,normal*(h_tmp_PDF[str(i)].GetMean()-h_tmp_PDF[str(i)].GetRMS()))
    #h_PDF["PDFUp"].Draw()

    #fout.mkdir('SR1T/ttbar')
    fout.cd("")
    R.gDirectory.WriteObject(h_PDF["PDFUp"],p+"_pdfUp" )
    R.gDirectory.WriteObject(h_PDF["PDFDown"],p+"_pdfDown" )
