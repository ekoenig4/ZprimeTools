import sys
import os
cmssw_base = os.getenv('CMSSW_BASE')
sys.path.append('')
from ROOT import *
import PlotTool.Plot as plot

samples = plot.datamc()

samples.initiate('h_')
