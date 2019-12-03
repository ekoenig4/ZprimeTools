#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = '%s/src/ZprimeTools/PostAnalyzer/' % cmssw
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2017'
options['region'] = 'GA'
options['parallel'] = True
options['batchsize'] = 100
# options['submit'] = False
#----Submit---#
submit('singlepho',label='Gamma_',filelist=True)
# submit('wjets')
# submit('zjets')
# submit('qcd')
# submit('ttjets')
# submit('gjets')
# submit('ewk')
# submit('dyjets')
