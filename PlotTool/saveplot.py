#!/usr/bin/python

from ROOT import *
from sys import argv
from sys import path
import Plot as plot
from os import system,getcwd
from cfg_saveplot import config

gROOT.SetBatch(1)

rfile = TFile('Systematics_'+str(config['year'])+'.root','recreate')

variable = argv[-1]
samples = {}
Uncertainty = config['Uncertainty']
for region,nhisto in config['regions'].items():
    print region
    store = {}
    directory = rfile.mkdir(region)
    store[dir] = directory
    norm = plot.datamc(fileDir=region,show=False)
    norm.initiate(variable+'_'+nhisto)
    directory.cd()
    store['norm'] = norm
    for sample in norm.SampleList:
        if sample == 'Data':
            sumOfBkg = norm.getSumOfBkg()
            sumOfBkg.SetName('data_obs')
            sumOfBkg.Write()
        elif sample == "Signal":
            for signal in norm.signal:
                norm.histo[signal].SetName(signal)
                norm.histo[signal].Write()
        else:
            norm.histo[sample].SetName(sample)
            norm.histo[sample].Write()
    ##############################################
    sample_unc = { name:unc for name,unc in Uncertainty.items() if not any(unc['region']) or region in unc['region'] }
    for name,unc in sample_unc.items():
        # if not any(unc['region']):
        unc[dir] += region
        norm = plot.datamc(fileDir=unc[dir],show=False)
        for var,info in unc['unc'].items():
            print '\t',var
            norm.initiate(variable+'_'+info[id])
            directory.cd()
            for sample in norm.SampleList:
                if sample == 'Data': continue
                elif sample == "Signal":
                    for signal in norm.signal:
                        norm.histo[signal].SetName(signal+'_'+var)
                        norm.histo[signal].Write()
                else:
                    norm.histo[sample].SetName(sample+'_'+var)
                    norm.histo[sample].Write()
    ###############################################################
###################################################################
                        
