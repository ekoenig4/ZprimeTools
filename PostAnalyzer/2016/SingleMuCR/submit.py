#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/ZprimeTools/PostAnalyzer/' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options,mclist
options['year'] = '2016'
options['region'] = 'WM'
options['parallel'] = True
options['batchsize'] = 20
# options['submit'] = False
#----Submit---#
submit('met',label='SingleMu_')
for mc in mclist: submit(mc)

