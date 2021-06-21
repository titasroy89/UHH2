from ROOT import *
import os
import sys
from optparse import OptionParser
from numpy import log10
from array import array

padRatio = 0.25
padOverlap = 0.15
padGap = 0.005

gROOT.SetBatch(True)

YesLog = True
NoLog=False

regionText ="loose selection"

import CMS_lumi
from Style import *
thestyle = Style()

HasCMSStyle = False
style = None
if os.path.isfile('tdrstyle.C'):
    ROOT.gROOT.ProcessLine('.L tdrstyle.C')
    ROOT.setTDRStyle()
    print "Found tdrstyle.C file, using this style."
    HasCMSStyle = True
    if os.path.isfile('CMSTopStyle.cc'):
        gROOT.ProcessLine('.L CMSTopStyle.cc+')
        style = CMSTopStyle()
        style.setupICHEPv1()
        print "Found CMSTopStyle.cc file, use TOP style if requested in xml file."
if not HasCMSStyle:
    print "Using default style defined in cuy package."
    thestyle.SetStyle()

ROOT.gROOT.ForceStyle()

stackList = { "TTbar":[kRed], "WJets":[kGreen], "ST":[kYellow], "DY":[kBlue], "VV":[kOrange], "QCD":[kTeal]}

print stackList

_channelText = "#mu+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True

H = 1000;
W = 1200;


# references for T, B, L, R                                                                                                             
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.1*W

legendHeightPer = 0.04
legList = stackList.keys() 

legendStart = 0.69
legendEnd = 0.97-(R/W)

legend = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.), legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))
legend.SetNColumns(2)


legendR = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.)-0.1, legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))

legendR.SetNColumns(2)

legendR.SetBorderSize(0)
legendR.SetFillColor(0)

legend.SetBorderSize(0)
legend.SetFillColor(0)

_file = {}

canvas = TCanvas('c1','c1',W,H)
canvas.SetFillColor(0)
canvas.SetBorderMode(0)
canvas.SetFrameFillStyle(0)
canvas.SetFrameBorderMode(0)
canvas.SetLeftMargin( L/W )
canvas.SetRightMargin( R/W )
canvas.SetTopMargin( T/H )
canvas.SetBottomMargin( B/H )
canvas.SetTickx(0)


pad1 = TPad("zxc_p1","zxc_p1",0,padRatio-padOverlap,1,1)
pad1.SetLeftMargin( L/W )
pad1.SetRightMargin( R/W )
pad1.SetTopMargin( T/H/(1-padRatio+padOverlap) )
pad1.SetBottomMargin( (padOverlap+padGap)/(1-padRatio+padOverlap) )
pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetFrameFillStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetTickx(0)
pad1.SetTicky(0)

pad1.Draw()
canvas.cd()


canvas.ResetDrawn()

stack = THStack("hs","stack")
#SetOwnership(stack,True)
histName="Migration_Matrix"
histograms = {
              "Migration_Matrix"   : ["#cbar #Delta y_{rec} #cbar","#cbar #Delta y_{gen} #cbar",14,[-2.,-1.5,-1.25,-1.,-0.75,-0.5,-0.25,0.,0.25,0.5,0.75,1.,1.25,1.5,2.], 8, [-2.,-1.5,-1.,-0.5,0.,0.5,1.,1.5,2.]],
}

_file = TFile("Input_undfolding_data_.root","read")
hist1 = _file.Get("Migration_Matrix")            
hist1.SetYTitle(histograms["Migration_Matrix"][1])
hist1.SetXTitle(histograms["Migration_Matrix"][0])        
stack.Add(hist1)     
stack.Draw("COLZ")
canvas.Clear()
stack.Draw("COLZ")
stack.SetTitle('')

CMS_lumi.CMS_lumi(pad1, 4, 11)
canvasRatio.SaveAs("Migration_Matrix.pdf")


