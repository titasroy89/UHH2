from ROOT import TCanvas, TGraphErrors, TLine
from ROOT import gROOT, gStyle
from array import array
 
c41 = TCanvas("c41","c41",200,10,600,400);
x = array('f',[0, 1, 2, 3, 4])
y = array('f',[0.056, 0.056, 0.056, 0.056, 0.056])
ex = array('f',[0.1, 0.2, 0.3, 0.4, 0.5])
ey = array('f',[0.063, 0.063, 0.063, 0.063, 0.063])
ge = TGraphErrors(5, x, y, ex, ey);
ge.SetFillColor(2)
#ge.SetFillStyle(3010)
ge.Draw("a3")

x = array('f',[0, 1, 2, 3, 4])
y = array('f',[-1, -1, 0.0502, -1, -1])
ex = array('f',[0.1, 0.2, 0.3, 0.4, 0.5])
ey = array('f',[0, 0, 0.01, 0.01, 0.01])
ge2 = TGraphErrors(5, x, y, ex, ey)
ge2.Draw("ap same")
c41.Print("Measurement.pdf")
''' 
c1 = TCanvas( 'c1', 'A Simple Graph with error bars', 200, 10, 700, 500 )
 
#c1.SetGrid()
#c1.GetFrame().SetFillColor( 21 )
c1.GetFrame().SetBorderSize( 12 )
 
n = 1;
x  = array( 'f', [1] )
ex = array( 'f', [0.5] )
y  = array( 'f', [0.056] )
ey = array( 'f', [0.063] )
 
gr = TGraphErrors( n, x, y, ex, ey )
gr.SetMarkerColor(1)
gr.SetMarkerStyle( 21 )
gr.Draw( 'AP' )
gr.GetXaxis().SetRangeUser(0,2)
gr.GetXaxis().SetLabelOffset(999);
gr.GetXaxis().SetLabelSize(0);

line = TLine(0.4,0,1.6,0);
line.SetLineStyle(2)
line.Draw("same") 

n2 = 1;
x2  = array( 'f', [1,2] )
ex2 = array( 'f', [0.5,0.5] )
y2  = array( 'f', [0.05,0.05] )
ey2 = array( 'f', [0.01,0.01] )

gr2 = TGraphErrors( n2, x2, y2, ex2, ey2 )
gr2.SetFillColor(3) 
gr2.Draw('a3 same')
c1.Update()
c1.Print("Measurement.pdf")
'''
