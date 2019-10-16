#!/usr/bin/env python
import os
from PlotTool.cfg_saveplot import config
from PlotTool.plotter import plotter

nvariables = [ 'ChNemPtFrac','ChNemPt','ChNemPt123','h_recoil','nJets','jetPt' ]
singleleps = [ 'h_LeptonPt','h_LeptonEta' ]
doubleleps = [ 'h_dileptonM','h_dileptonPt' ]

cwd = os.getcwd()

def getplots(dir,variables):
    os.chdir(dir)
    nhist = config['regions'][dir]
    plotter([ '%s_%s' % (variable,nhist) for variable in variables ])
    os.chdir(cwd)

#----Signal Region----#
dir = 'SignalRegion/'
getplots(dir,nvariables)

#----Double Lepton CR----#
dir = 'DoubleMuCR/'
getplots(dir,nvariables + doubleleps)
dir = 'DoubleEleCR/'
getplots(dir,nvariables + doubleleps)

#----Single Lepton CR----#
dir = 'SingleMuCR/'
getplots(dir,nvariables + singleleps)
dir = 'SingleEleCR/'
getplots(dir,nvariables + singleleps)
