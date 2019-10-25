#!/usr/bin/env python
import os
from ROOT import gROOT
from cfg_saveplot import config
from plotter import plotter

# nvariables = [ 'ChNemPtFrac','ChNemPt','ChNemPt123','h_recoil','nJets','j1pT' ]
nvariables = ['ChNemPtFrac','ChNemPt','j1pT' ]
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

getplots('SignalRegion/',nvariables)
# getplots('DoubleMuCR/',nvariables + doubleleps)
# getplots('DoubleEleCR/',nvariables + doubleleps)
# getplots('SingleMuCR/',nvariables + singleleps)
# getplots('SingleEleCR/',nvariables + singleleps)

for var in outvar:
    print var
