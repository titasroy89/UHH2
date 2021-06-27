#! /usr/bin/env python
from ROOT import *
import ROOT
import sys
import numpy

systematic_direction={'hfstats1','toptag','muID','miswtag','lfstats2','hf','pileup','muHLT','lf','pt_rew','hfstats2','lfstats1','cferr1','cferr2','jes','HT','muon_rec','pdf','q2','jer','jec'}
samplelist = {'wjets','ttbar_others','vv','qcd','singletop','ttbar_semi','dy'}
fin = TFile('Input_undfolding_data.root', 'open')
nominalhist = {}
nominalhistDraw = {}
systvarhist = {}
systvarhistDraw = {}
systvarhistRatio = {}
systvarhistRatioDraw = {}
canvas_Bkg = {}
pad1 = {}
pad2 = {}
gROOT.SetBatch(kTRUE)

for samp in samplelist:
    for syst in systematic_direction:
        print syst
        if((syst == 'jec' or syst == 'jer' or syst == 'q2' or syst == 'pdf') and (samp != 'ttbar_semi')):
            continue 
        nominalhist[samp+syst] = fin.Get(samp+'_nominal')
        canvas_Bkg[samp+syst] = TCanvas("SystVariation_"+samp+syst,"SystVariation_"+samp+syst,800,600)
        legend = TLegend(.7,.70,.9,.9)
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
                
        #Upper plot will be in pad1
        pad1[samp+syst] = TPad("pad1", "pad1", 0., 0.3, 1., 1.);
        #pad1.SetBottomMargin(0) # Upper and lower plot are joined
        pad1[samp+syst].SetBottomMargin(5); # Upper and lower plot are not joined
        pad1[samp+syst].SetGridx();         # Vertical grid
        pad1[samp+syst].Draw();             # Draw the upper pad: pad1
        pad1[samp+syst].cd();               # pad1 becomes the current pad
                
        systvarhist[samp+syst+'Up'] = fin.Get(samp+'_'+syst+'Up')
        print(systvarhist[samp+syst+'Up'])
        systvarhist[samp+syst+'Up'].Print()
        systvarhist[samp+syst+'Down'] = fin.Get(samp+'_'+syst+'Down')
        systvarhist[samp+syst+'Down'].Print()
        if systvarhist[samp+syst+'Up'] == None or systvarhist[samp+syst+'Down'] == None:
            continue
        systvarhistDraw[samp+syst+'Up'] = systvarhist[samp+syst+'Up'].DrawClone('ep')
        a = systvarhist[samp+syst+'Up'].GetMaximum()
        systvarhistDraw[samp+syst+'Up'].GetXaxis().SetTitle("| #Delta y |")
        systvarhistDraw[samp+syst+'Up'].SetMarkerColor(kRed)
        systvarhistDraw[samp+syst+'Up'].SetMarkerStyle(21)
        systvarhistDraw[samp+syst+'Up'].SetLineColor(kRed)
                
        systvarhistDraw[samp+syst+'Down'] = systvarhist[samp+syst+'Down'].DrawClone('same')
        systvarhistDraw[samp+syst+'Down'].SetMarkerColor(kBlue)
        systvarhistDraw[samp+syst+'Down'].SetMarkerStyle(21)
        systvarhistDraw[samp+syst+'Down'].SetLineColor(kBlue)
                
        nominalhistDraw[samp+syst] = nominalhist[samp+syst].DrawClone('same')
        nominalhistDraw[samp+syst].SetMarkerStyle(20)
        nominalhistDraw[samp+syst].SetMarkerSize(1.5)
        nominalhistDraw[samp+syst].SetMarkerColor(kBlack)
        nominalhistDraw[samp+syst].SetLineColor(kBlack)
                
        legend.AddEntry(nominalhistDraw[samp+syst],'nominal','lp')
        legend.AddEntry(systvarhistDraw[samp+syst+'Up'],syst+'Up','lp')
        legend.AddEntry(systvarhistDraw[samp+syst+'Down'],syst+'Down','lp')
        legend.Draw()

        latex = ROOT.TLatex()
        latex.SetTextSize(0.045)
        latex.SetTextAlign(11)
        latex.DrawLatex(-1.9,a*1.06,"Work in progress")

        latex2 = ROOT.TLatex()
        latex2.SetTextSize(0.045)
        latex2.SetTextAlign(11)
        latex2.DrawLatex(1.1,a*1.06,"58.8 fb^{-1} (13 TeV)")
                
        canvas_Bkg[samp+syst].cd();          # Go back to the main canvas before defining pad2
        pad2[samp+syst] = TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2[samp+syst].SetTopMargin(5);
        pad2[samp+syst].SetBottomMargin(5);
        pad2[samp+syst].SetGridx(); # vertical grid
        pad2[samp+syst].Draw();
        pad2[samp+syst].cd();      # pad2 becomes the current pad
        systvarhistRatio[samp+syst+'__plus__ratio']  = systvarhistDraw[samp+syst+'Up'].Clone(samp+syst+'Up_Ratio')
        systvarhistRatio[samp+syst+'__plus__ratio'].Divide(nominalhistDraw[samp+syst])
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0.6,1.4)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetTitleSize(0.6)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetNdivisions(5,5,0)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetLabelSize(0.12)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetTitle("Variation/Nominal")
        systvarhistRatio[samp+syst+'__plus__ratio'].GetXaxis().SetTitle("")
        systvarhistRatio[samp+syst+'__plus__ratio'].SetMarkerStyle(1)
        systvarhistRatio[samp+syst+'__plus__ratio'].Draw('l')
        systvarhistRatio[samp+syst+'__minus__ratio']  = systvarhistDraw[samp+syst+'Down'].Clone(samp+syst+'Down_Ratio')
        systvarhistRatio[samp+syst+'__minus__ratio'].Divide(nominalhistDraw[samp+syst])
        systvarhistRatio[samp+syst+'__minus__ratio'].SetMarkerStyle(1)
        systvarhistRatio[samp+syst+'__minus__ratio'].Draw('same')

        canvas_Bkg[samp+syst].SaveAs("SystVariation_"+samp+syst+'.pdf')

