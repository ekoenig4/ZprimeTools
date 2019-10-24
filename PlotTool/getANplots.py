#!/usr/bin/env python
import os
from ROOT import gROOT
from cfg_saveplot import config
from plotter import plotter

nvariables = [ 'ChNemPtFrac','ChNemPt','ChNemPt123','h_recoil','nJets','j1pT' ]
# nvariables = ['ChNemPtFrac','ChNemPt' ]
singleleps = [ 'h_LeptonPt','h_LeptonEta' ]
doubleleps = [ 'h_dileptonM','h_dileptonPt','h_leadingLeptonPt','h_leadingLeptonEta','h_subleadingLeptonEta','h_subleadingLeptonPt' ]

cwd = os.getcwd()

outvar = []

outdir = "/afs/hep.wisc.edu/home/ekoenig4/public_html/MonoZprimeJet/Plots%s/%sPlots_EWK/datamc_%s.png" 

def getplots(dir,variables):
    global outvar
    os.chdir(dir)
    region = dir[:-1]
    nhist = config['regions'][dir]
    inputvar = [ '%s_%s' % (variable,nhist) for variable in variables ]
    outvar += [ outdir % (config['year'],region,var) for var in inputvar ]
    plotter(inputvar)
    os.chdir(cwd)

#----Signal Region----#
dir = 'SignalRegion/'
# getplots(dir,nvariables)

#----Double Lepton CR----#
dir = 'DoubleMuCR/'
# getplots(dir,nvariables + doubleleps)
dir = 'DoubleEleCR/'
# getplots(dir,nvariables + doubleleps)

#----Single Lepton CR----#
dir = 'SingleMuCR/'
# getplots(dir,nvariables + singleleps)
dir = 'SingleEleCR/'
getplots(dir,nvariables + singleleps)

for var in outvar:
    print var
