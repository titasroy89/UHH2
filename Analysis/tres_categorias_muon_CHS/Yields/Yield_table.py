#! /usr/bin/env python

import ROOT
from ROOT import *
import math
import array
from numpy import *
Rootfile = TFile("DeltaY_muon.root")
keys = Rootfile.GetListOfKeys()
channels = []
for key in keys:
        a = key.GetName()
        if a == 'SR0T' or a == 'CR1':
           continue
        channels.append(a)
dir = Rootfile.GetDirectory(channels[0])
dirs = dir.GetListOfKeys()
proc = []
for di in dirs:
       b = di.GetName()
       proc.append(b)
proc.sort()
proc = list(dict.fromkeys(proc))
proc.sort()
text = 'Table.txt'
T = open(text,"w+")

for p in proc:
        if p == 'singletop':
                a = 'ST'
                T.write(a)
        elif p == 'TotalBkg':
                a = 'TBkg'
                T.write(a)
        elif p == 'data_obs':
                a = 'data'
                T.write(a)
        else:
                T.write(p)
        dir2 = Rootfile.GetDirectory(channels[0]+"/"+p)
        syst = dir2.GetListOfKeys()
        s=[] 
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
            if(element == 'nominal'):
                a = 0
                error_nominal = Double(0.0)
                Rootfile.cd("")
                Rootfile.cd(channels[0]+"/"+p)
                myhisto = gDirectory.Get(element).Clone() 
		a = myhisto.IntegralAndError(0,140,error_nominal,"")
                nominal = int(a)
                error = int(error_nominal) 
        for element in s:
                up_down_correction += 1
                a = 0
                Rootfile.cd("")
                Rootfile.cd(channels[0]+"/"+p)
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
        if p == 'data_obs':
            e = 0
        T.write("\t")
        T.write(str(nom))
        T.write("\pm")
        T.write(str(e))                
        T.write("\n")
