#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/ZprimeTools/PostAnalyzer/' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2017'
options['region'] = 'SR'
options['parallel'] = True
options['batchsize'] = 60
# options['submit'] = False
#----Submit---#
submit('met',sub='B',filelist=True)
# submit('wjets')
# submit('zjets')
# submit('qcd')
# submit('ttjets')
# submit('gjets')
# submit('ewk')
# submit('dyjets')

