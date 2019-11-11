#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/MonoZprimeJet/PostAnalyzer/' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2016'
options['region'] = 'SR'
options['parallel'] = True
options['batchsize'] = 20
# options['submit'] = False
#----Submit---#
submit('signal',split=1)
submit('met',sub='F')
submit('wjets')
submit('zjets')
submit('qcd')
submit('ttjets')
submit('gjets')
submit('ewk')

