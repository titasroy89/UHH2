from array import array
from ROOT import *
import ROOT as R
import sys
from sys import *
import numpy

samplelist = {
#'other':'Variables/'+argv[1]+'/'+argv[1]+'_muon_3cat.root',
'other':argv[1]+'_muon_3cat.root',
}

#proc = ['Ttbar','data_obs','singletop','wjets','dy','qcd','vv']
#cat = ['SR1T']
fout = R.TFile('/nfs/dust/cms/user/hugobg/UHH2_v2/CMSSW_10_2_17/src/UHH2/Analysis/tres_categorias_muon_CHS/'+argv[1]+'_muon.root', 'recreate')
#for t in cat:
#    for p in proc:
#        fout.mkdir(t+'/'+p)

for key_sample in samplelist:
    fin = R.TFile(samplelist[key_sample])
#    for key_c in cat:
#                for key_p in proc:
#                    fin.cd(key_c+'/'+key_p)
    dir = R.gDirectory.GetListOfKeys()
    for key_dir in dir:
        name = key_dir.GetName()
        temp = fin.Get(name)
        nb = temp.GetNbinsX()
        temp.SetBinContent(1,temp.GetBinContent(0)+temp.GetBinContent(1)) 		
	temp.SetBinContent(1,temp.GetBinContent(0)+temp.GetBinContent(1)) 		
        temp.SetBinContent(nb,temp.GetBinContent(nb)+temp.GetBinContent(nb+1))                        
        fout.cd('')
        R.gDirectory.WriteObject(temp,name)
        del temp








