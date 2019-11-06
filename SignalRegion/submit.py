#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = os.path.realpath('../')
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2018'
options['region'] = 'SR'
options['parallel'] = True
#----Submit---#
submit('signal',split=1)
submit('met',sub='A',filelist=True)
submit('wjets')
submit('zjets')
submit('qcd')
submit('ttjets')
submit('gjets')
submit('ewk')

