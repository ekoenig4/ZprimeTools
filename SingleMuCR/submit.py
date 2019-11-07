#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/ZprimeTools2016' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2016'
options['region'] = 'WM'
options['parallel'] = True
#----Submit---#
submit('met',label='SingleMu_')
submit('wjets')
submit('zjets')
submit('qcd')
submit('ttjets')
submit('gjets')
submit('ewk')

