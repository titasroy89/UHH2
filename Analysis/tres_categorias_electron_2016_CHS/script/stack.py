#! /usr/bin/env python
from ROOT import *
import sys
from sys import argv
import numpy

def createCanvasPads():
    c = TCanvas("c", "canvas", 800, 800)
    pad1 = TPad("pad1", "pad1", 0.05,0.25,0.95,0.95)
    pad1.SetBottomMargin(0)  # joins upper and lower plot
    pad1.SetGridx()
    pad1.Draw()
    # Lower ratio plot is pad2
    c.cd()  # returns to main canvas before defining pad2
    pad2 = TPad("pad2", "pad2", 0.05,0.05,0.95,0.24)
    pad2.SetTopMargin(0)  # joins upper and lower plot
    pad2.SetBottomMargin(0.2)
    pad2.SetGridx()
    pad2.Draw()
    return c, pad1, pad2

def plot_cat(categories):
    samplelist = ['singletop','Ttbar','wjets','qcd','dy','vv']
    fin = TFile('Variables/'+argv[1]+'/MDF_shapes.root', 'open')
    canvas_Bkg = {}
    nominalhist = {}
    gROOT.SetBatch(kTRUE)
    i = 1;
    for cat in categories:
        canvas_Bkg[cat], pad1, pad2 = createCanvasPads()
        stack = THStack(cat,cat)
        legend = TLegend(.67, .78, .89, .88)
        legend.SetMargin(0.12);
        legend.SetTextSize(0.03);
        legend.SetFillColor(10);
        legend.SetBorderSize(0);
        for samp in samplelist:
                    nominalhist[cat+samp] = fin.Get(cat+'/'+samp)
                    if(samp == 'Ttbar'):
 		    	nominalhist[cat+samp].SetFillColor(kRed)
                    elif(samp == 'singletop'):
                        nominalhist[cat+samp].SetFillColor(kOrange)		
                    elif(samp == 'wjets'):
                        nominalhist[cat+samp].SetFillColor(kBlue)
                    elif(samp == 'qcd'):
                        nominalhist[cat+samp].SetFillColor(kYellow) 		    
                    elif(samp == 'dy'):
                        nominalhist[cat+samp].SetFillColor(kGreen)
                    elif(samp == 'vv'):
                        nominalhist[cat+samp].SetFillColor(kTeal)
                    stack.Add(nominalhist[cat+samp])
                    legend.AddEntry(nominalhist[cat+samp], samp, "f")
        nominalhist[cat+'data'] = fin.Get(cat+'/data_obs')
        pad1.cd()        
        nominalhist[cat+'data'].SetMarkerStyle(20)
        nominalhist[cat+'data'].Draw('p')
        stack.Draw('esamehist')
        nominalhist[cat+'data'].Draw('samep')

        binmax = stack.GetMaximum()
        binmay = nominalhist[cat+'data'].GetMaximum()
        if(binmax > binmay): 
	  nominalhist[cat+'data'].SetMaximum(binmax*1.1)
#        else: 
#          nominalhist[cat+'data'].SetMaximum(x*1.2)	  			
        nominalhist[cat+'data'].SetTitle(cat)
        y1 = nominalhist[cat+'data'].GetYaxis()
        y1.SetTitle("Events")
        legend.Draw('same')
        pad2.cd()
        gStyle.SetOptStat(0);
        temp = stack.GetStack().Last().Clone("temp")
        temp2  = nominalhist[cat+'data'].Clone()

        temp2.SetTitle("")     
        y = temp2.GetYaxis()
        y.SetTitleSize(.07)
        y.SetTitleOffset(0.4);
        y.SetTitle("Data/Bkg")
        x1 = temp2.GetXaxis()
        x1.SetTitleSize(.15)
        x1.SetTitleOffset(0.4);
        x1.SetTitle(argv[1])

        errorband=stack.GetStack().Last().Clone("error")
        errorband.Sumw2()
        errorband.SetLineColor(kBlack)
        errorband.SetFillColor(kBlack)
        errorband.SetFillStyle(3245)
        errorband.SetMarkerSize(0)
        errorband.Divide(temp)
#        errorband.Draw('e2,same')      
        temp2.Divide(temp2,temp,1,1,'B')
        temp2.Draw('e,x0')
        errorband.Draw('e2,same')
        oneLine = TF1("oneline","1",-9e9,9e9)
        oneLine.SetLineColor(kBlack)
        oneLine.SetLineWidth(1)
        oneLine.SetLineStyle(2)
        oneLine.Draw("same")
        canvas_Bkg[cat].SaveAs(argv[1]+'_'+cat+'.pdf')
		    		
categories  = ['SR1T_muon_postfit']
plot_cat(categories)

categories  = ['SR0T_muon_postfit']
plot_cat(categories)

categories  = ['CR1_muon_postfit']
plot_cat(categories)

#categories  = ['CR2mu_postfit']
#plot_cat(categories)

categories  = ['SR1T_muon_prefit']
plot_cat(categories)

categories  = ['SR0T_muon_prefit']
plot_cat(categories)

categories  = ['CR1_muon_prefit']
plot_cat(categories)

#categories  = ['CR2mu_prefit']
#plot_cat(categories)
