#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/ZprimeTools2016' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2016'
options['region'] = 'WE'
options['parallel'] = True
#----Submit---#
submit('egamma',label='SingleEle_')
submit('wjets')
submit('zjets')
submit('qcd')
submit('ttjets')
submit('gjets')
submit('ewk')

