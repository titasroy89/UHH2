#!/usr/bin/env python
# -*- coding: utf-8 -*-

# usage of script: number of cores, first file, second file, ..., method to use True==Fast, False==counting weights
# python readaMCatNLO.py 4 ../../common/datasets/MC_WJet.xml True/False



import sys, time, os
from multiprocessing.pool import ThreadPool
import subprocess
import ROOT
from ROOT import *
from tqdm import tqdm

ROOT.PyConfig.IgnoreCommandLineOptions = True
ROOT.gROOT.SetBatch(1)


def read_xml(xmlFileDir):
    xmlFile = open(str(xmlFileDir))
    rootFileStore = []
    comment = False
    for line in xmlFile:
        if ".root" in line:
            rootFileStore.append(line.split('"')[1])
    return rootFileStore

def compile_counting_macro():
    """When running without the Fast method, a root macro is called and compiled on the fly if it has not yet been compiled.
    However, when running this method for the first time with multiple jobs in a pool, all of them try to compile the macro in parallel.
    As a result, the compilation bugs out and the jobs crash.
    For that reason, the macro needs to be compiled before running the pool. This is what this function does."""

    # Pretty hacky: check if files that would be generated by compiler exist already
    compiler_outputs = ['countNumberEvents_C.d', 'countNumberEvents_C.so', 'countNumberEvents_C_ACLiC_dict_rdict.pcm']
    do_compile = False
    for o in compiler_outputs:
        if not os.path.isfile(o):
            do_compile = True
            break

    if do_compile:
        for o in compiler_outputs:
            command = 'rm '+o # be very careful with this
            process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
            process.wait()
        # taken from https://root-forum.cern.ch/t/when-to-compile-macros/31792/4
        command = "root -b -l -q -e '.L countNumberEvents.C+' >& countNumberEvents_C_compilation_log.txt"
        process = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE)
        process.wait()

def read_tree(rootDir, progress_bar=None):
    numberOfweightedEntries = 0
    try:
        # Use C++ script to count as significantly faster (~15x)
        cmd = "root -q -b -l 'countNumberEvents.C+(\""+rootDir+"\",false)'"
        output = subprocess.check_output(cmd, shell=True, stderr=subprocess.STDOUT)
        # now have to be careful - root will return 0 even if there's an error
        if "error:" in output.lower():
            raise RuntimeError("Error running ROOT: " + output)
    except Exception as e:
        print 'unable to count events in root file',rootDir
        print e
    numberOfweightedEntries = float(output.splitlines()[-1])
    if progress_bar: progress_bar.update(1)
    return numberOfweightedEntries

def read_treeFast(rootDir, progress_bar=None):
    fastentries =0
    try:
        ntuple = TFile(str(rootDir))
        AnalysisTree = ntuple.Get("AnalysisTree")
        fastentries =  AnalysisTree.GetEntriesFast()
    except Exception as e:
        print 'unable to count events in root file',rootDir
        print e
    if progress_bar: progress_bar.update(1)
    return fastentries

def readEntries(worker, xmlfiles, fast=False):
    if fast: print 'Going to use the Fast Method, no weights used'
    else:
        print 'Going to use the Weight Method: countNumberEvents.C'
        compile_counting_macro()
    print "Number of workers:",worker
    result_list = []
    for xml in xmlfiles:
        pool = ThreadPool(processes=int(worker))
        print "Open XML file:",xml
        rootFileStore = read_xml(xml)
        entries_per_rootfile = []
        progress_bar = tqdm(total=len(rootFileStore), desc='Ntuples counted', dynamic_ncols=True, leave=False)
        for rootFile in rootFileStore:
            entries_per_rootfile.append(pool.apply_async(func=(read_treeFast if fast else read_tree), args=(rootFile,progress_bar,)))
        pool.close()
        pool.join()
        entries_per_rootfile = [result.get() for result in entries_per_rootfile]
        print 'Done.', ('Number of events:' if fast else 'Sum of event weights:'), sum(entries_per_rootfile)
        result_list.append(sum(entries_per_rootfile))
        commentOutEmptyRootFiles(xml, entries_per_rootfile,fast)
    return result_list


def commentOutEmptyRootFiles(xmlfile, entries_per_rootfile,fast=False):
    """Edit the XML file so that ROOT files with 0 events are commented out

    This is because sframe can crash if the first file has 0 events.
    (For some reason CRAB makes these empty files)

    Note that we need != 0 as some files have -ve entries due to weights
    (we assume the user knows how to handle that scenario)
    """
    newText = []
    with open(xmlfile, "U") as file:
        i_ = 0
        for line in file.readlines():
            if '.root' in line:
                newText.append(line if entries_per_rootfile[i_]!=0 else '<!--EMPTY <In FileName="'+line.split('"')[1]+'" Lumi="0.0"/> -->\n')
                i_ += 1
            elif line.startswith('<!-- < NumberEntries'):
                newText.append(line)
        if len(entries_per_rootfile)!= i_: print "ERROR", len(entries_per_rootfile), i_
    with open(xmlfile, "w") as outputfile:
        for line in newText:
            outputfile.write(line)
        method = 'fast' if fast else 'weights'
        outputfile.write('<!-- < NumberEntries="'+str(sum(entries_per_rootfile))+'" Method='+method+' /> -->\n')


if __name__ == "__main__":
    xmllist = sys.argv[2:-1]
    meth = eval(sys.argv[-1])
    readEntries(sys.argv[1],xmllist,meth)
