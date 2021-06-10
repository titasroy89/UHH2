import ROOT
import uproot
import numpy as np
import concurrent.futures
import time
import multiprocessing

InFile = uproot.open("/nfs/dust/cms/user/hugobg/ZPrimeSemi/workdir_FullVisPS/uhh2.AnalysisModuleRunner.MC.TT_TuneCUETP8M2T4_2016v3.root")
tree = InFile["AnalysisTree/GenParticles"]
pt = tree["GenParticles.m_pt"].array()
print(pt)
h1 = ROOT.TH1D('h1', 'Test random', 100, 0., 500)

def sleep_some(x):
    h1.Fill(pt[x][2])

print(multiprocessing.cpu_count())
a_pool = multiprocessing.Pool(20)
tic = time.time()
result = a_pool.map(sleep_some, range(30000))
toc = time.time()
print("Time elapsed: %0.4fsecs" % (toc - tic))

tic = time.time()
for i in range(30000):
    h1.Fill(pt[i][2])
toc = time.time()
print("Time elapsed: %0.2fsecs" % (toc - tic))


#h1 = ROOT.TH1D('h1', 'Test random', 100, 0., 500)
#tic = time.time()
#for i in range(30000):
#    h1.Fill(pt[i][2])
#    vals2[i] = i**2
#with concurrent.futures.ThreadPoolExecutor(max_workers=8) as p:
#	ret = p.map(sleep_some, range(10000))

#toc = time.time()
#print("Time elapsed: %0.2fsecs" % (toc - tic))

#canv = ROOT.TCanvas()
#h1.Draw()
#canv.Print("Python.pdf")

