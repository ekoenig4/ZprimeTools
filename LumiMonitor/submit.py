#!/usr/bin/env python
import os
import sys
cmssw = os.getenv("CMSSW_BASE")
repo = os.path.realpath('../')
sys.path.append(repo)

from CondorTools.SubmitDataset import submit,options
options['year'] = '2017'
options['region'] = 'LM'
options['parallel'] = True
#----Submit---#
submit('egamma',sub='F',script='calcLumi.py',filelist=True)
# submit('met',script='calcLumi.py',filelist=True)
# submit('egamma',script='calcLumi.py',filelist=True)

