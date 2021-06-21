
import array
import ROOT as R
import sys
import numpy as np

samplelist = {
'other':'rebin_mu_4cat.root',
#'other2':'rebin_small_Combine.root',
'SR1Ttt':'templates_pdf_SR1T.root',
'SR0Ttt':'templates_pdf_SR0T.root',
'CR1tt':'templates_pdf_CR1.root',
'CR2tt':'templates_pdf_CR2.root',
'SR1Tq2':'templates_q2_SR1T.root',
'SR0Tq2':'templates_q2_SR0T.root',
'CR1q2':'templates_q2_CR1.root',
'CR2q2':'templates_q2_CR2.root'
}
proc = ['ZprimeNarrow3000', 'ttbar', 'wjets_l','ZprimeNarrow1500','data_obs','singletop','wjets_c','DY','QCD','ZprimeNarrow0500','ZprimeNarrow0750','ZprimeNarrow1000','ZprimeNarrow1250','ZprimeNarrow2000','ZprimeNarrow2500','ZprimeNarrow3500','ZprimeNarrow4000','ZprimeNarrow4500','ZprimeNarrow5000','ZprimeNarrow6000','ZprimeNarrow6500','ZprimeNarrow7000']
cat = ['SR1T','SR0T','CR1','CR2']
fout = R.TFile('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/Full_sys_4cat_muon.root', 'recreate')

for t in cat:
    for p in proc:
	if p == 'DY':
	   p = 'dy'
        elif p == 'VV':
           p = 'vv'
        elif p == 'QCD':
           p = 'qcd'
        fout.mkdir(t+'/'+p)

cat2 = ['SR1T','SR0T']
cat3 = ['CR1','CR2']
proc2 = ['ttbar'] 
proc3 = ['ttbar','wjets_l']
#proc_other = ['ZprimeNarrow3000', 'ttbar', 'wjets_l','ZprimeNarrow1500','data_obs','singletop']
#proc_other2 = ['wjets_b','wjets_c','DY','QCD']


for key_sample in samplelist:
    fin = R.TFile(samplelist[key_sample])
    if (key_sample == 'other') :
	for key_c in cat:
	    	for key_p in proc:
        	    fin.cd(key_c+'/'+key_p)
		    dir = R.gDirectory.GetListOfKeys()
		    for key_dir in dir:
                	name = key_dir.GetName()
               		temp = fin.Get(key_c+'/'+key_p+'/'+name)
                	fout.cd('')
                	a = key_p
			if name == 'toptagUp':
				continue
			if name == 'toptagDown':
				continue
                	if a == 'DY':
                   		a = 'dy'
                	elif a == 'VV':
                   		a = 'vv'
                        elif a == 'QCD':
                                a = 'qcd'
                	fout.cd(key_c+'/'+a)
                	R.gDirectory.WriteObject(temp,name)
                	del temp
    ''' 
    if (key_sample == 'other2') :
        for key_c in cat:
                for key_p in proc_other2:
                    fin.cd(key_c+'/'+key_p)
                    dir = R.gDirectory.GetListOfKeys()
                    for key_dir in dir:
                        name = key_dir.GetName()
                        temp = fin.Get(key_c+'/'+key_p+'/'+name)
                        fout.cd('')
                        a = key_p
                        if a == 'DY':
                                a = 'dy'
                        elif a == 'VV':
                                a = 'vv'
                        elif a == 'QCD':
                                a = 'qcd'
                        fout.cd(key_c+'/'+a)
                        R.gDirectory.WriteObject(temp,name)
                        del temp
    '''

    if (key_sample[0:2] == 'SR'):
         for key_c in cat2:
                for key_p in proc2:
                    if (key_c != key_sample[0:4]):
                        continue
                    fin.cd(key_c+'/'+key_p)
                    dir = R.gDirectory.GetListOfKeys()
                    for key_dir in dir:
                        name = key_dir.GetName()
                        temp = fin.Get(key_c+'/'+key_p+'/'+name)
                        fout.cd('')
                        if name	== 'toptagUp':
                                continue
                        if name	== 'toptagDown':
                                continue
                        a = key_p
                        fout.cd(key_c+'/'+a)
                        R.gDirectory.WriteObject(temp,name)
                        del temp

    if (key_sample[0:2] == 'CR'):
         for key_c in cat3:
                for key_p in proc3:
                    if (key_c != key_sample[0:3]):
       	       	       	continue
                    fin.cd(key_c+'/'+key_p)
                    dir = R.gDirectory.GetListOfKeys()
                    for key_dir in dir:
                        name = key_dir.GetName()
                        temp = fin.Get(key_c+'/'+key_p+'/'+name)
                        print(key_c+'/'+key_p+'/'+name)
                        fout.cd('')
                        if name	== 'toptagUp':
                                continue
                        if name	== 'toptagDown':
                                continue
                        a = key_p
                        fout.cd(key_c+'/'+a)
                        R.gDirectory.WriteObject(temp,name)
                        del temp

