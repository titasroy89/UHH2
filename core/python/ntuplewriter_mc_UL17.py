import FWCore.ParameterSet.Config as cms
from UHH2.core.ntuple_generator import generate_process  # use CMSSW type path for CRAB
from UHH2.core.optionsParse import setup_opts, parse_apply_opts


"""NTuple config for UL17 MC datasets.

You should try and put any centralised changes in generate_process(), not here.
"""


process = generate_process(year="UL17", useData=False)

# Please do not commit changes to source filenames - used for consistency testing
process.source.fileNames = cms.untracked.vstring([
#    '/store/mc/RunIISummer20UL17MiniAODv2/TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8/MINIAODSIM/106X_mc2017_realistic_v9-v1/230000/24FDC9A3-8E72-CC41-9C37-5D696614A816.root'
    '/store/mc/RunIISummer20UL17MiniAODv2/TTtoLNu2Q-1Jets-smeft_MTT-700to900_TuneCP5_13TeV_madgraphMLM-pythia8/MINIAODSIM/106X_mc2017_realistic_v9-v2/120000/00942A5B-194F-B845-BCF6-EC871C1424D9.root'
])

# Do this after setting process.source.fileNames, since we want the ability to override it on the commandline
options = setup_opts()
parse_apply_opts(process, options)

with open('pydump_mc_UL17.py', 'w') as f:
    f.write(process.dumpPython())
