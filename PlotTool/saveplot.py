#!/usr/bin/python

from ROOT import *
from sys import argv
from sys import path
import Plot as plot
from os import system,getcwd
from cfg_saveplot import config
from mcinfo import lumi as mc
from optparse import OptionParser

gROOT.SetBatch(1)

rfile = TFile('Systematics_'+str(config['year'])+'.root','recreate')
dir = {"SignalRegion/":"sr","DoubleEleCR/":"ee","DoubleMuCR/":"mm","SingleEleCR/":"e","SingleMuCR/":"m"}

variable = argv[-1]
samples = {}
Uncertainty = config['Uncertainty']
lumi = max( lumi for region,lumi in mc.items() )
for region,nhisto in config['regions'].items():
    print region
    directory = rfile.mkdir(dir[region])
    # store[dir] = directory
    norm = plot.datamc(fileDir=region,lumi=lumi,show=False)
    norm.initiate(variable+'_'+nhisto)
    directory.cd()
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
        for var,info in unc['unc'].items():
            if config['year'] != 2016 and region == 'SignalRegion/':
                info[id] = str( int(info[id])-1 )
            print '\t',var
            input = variable+'_'+str( int(info[id]) + int(nhisto) )
            norm.initiate( input )
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
rfile.cd()
lumi_hs = TH1F("lumi","lumi",1,0,1)
lumi_hs.SetBinContent(1,norm.lumi)
lumi_hs.Write()
year_hs = TH1F("year","year",1,0,1)
year_hs.SetBinContent(1,int(norm.version))
year_hs.Write()
var_hs = TH1F("variable",variable,1,0,1)
var_hs.Write()
