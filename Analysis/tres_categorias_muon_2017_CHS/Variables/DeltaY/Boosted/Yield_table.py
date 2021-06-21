#! /usr/bin/env python

import ROOT
from ROOT import *
import math
import array
from numpy import *

Rootfile = TFile("DeltaY_muon.root")
text = 'Table.txt'
T = open(text,"w+")
process  = ['ttbar_semi','ttbar_others','singletop','DATA','qcd','wjets','vv','dy']
syst = Rootfile.GetListOfKeys()
s=[] 
for proc in process:
	for sys in syst:
        	c = sys.GetName()
        	s.append(c)
	s.sort()
	s = list(dict.fromkeys(s))
	s.sort()
	nominal = 0
	error = 0 
	error_sys = Double(0.0)
	up_down_correction = 0
	err = Double(0.0)
	for element in s:
                if(element.startswith(proc)):
   			if(element.endswith('nominal')):
        			a = 0
        			error_nominal = Double(0.0)
        			Rootfile.cd("")
        			myhisto = gDirectory.Get(element).Clone() 
				a = myhisto.IntegralAndError(0,140,error_nominal,"")
        			nominal = int(a)
        			error = int(error_nominal) 
	for element in s:
                if(element.startswith(proc)):
    			up_down_correction += 1
    			a = 0
   			myhisto = gDirectory.Get(element).Clone()
    			a = myhisto.Integral()
    			err += abs(nominal - a) 
    			if(up_down_correction%2 == 0):
        			err = err/2
        			error_sys += err*err
        			err = 0
 
	error = math.sqrt(error*error + error_sys) 
	nom = int(nominal)
	e = int(error)
	if proc == 'DATA':
    		e = 0
        T.write(proc)
	T.write("\t")
	T.write(str(nom))
	T.write("\pm")
	T.write(str(e))                
	T.write("\n")


