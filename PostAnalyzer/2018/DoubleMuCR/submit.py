#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/ZprimeTools/PostAnalyzer/' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options,mclist
options['year'] = '2018'
options['region'] = 'ZM'
options['parallel'] = True
options['batchsize'] = 100
# options['submit'] = False
#----Submit---#
submit('met',label='DoubleMu_',filelist=True)
for mc in mclist: submit(mc)

