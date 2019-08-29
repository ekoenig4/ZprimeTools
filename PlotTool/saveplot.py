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

def greaterThan(hs,cut):
    if hs == None: return '+'+str(cut)
    xaxis = [ hs.GetBinLowEdge(i) for i,v in enumerate(hs) ]
    for i,x in enumerate(xaxis):
        if x < cut: hs.SetBinContent(i,0); hs.SetBinError(i,0)
########################################################################################################
def lessThan(hs,cut):
    if hs == None: return '+'+str(cut)
    xaxis = [ hs.GetBinLowEdge(i) for i,v in enumerate(hs) ]
    for i,x in enumerate(xaxis):
        if x > cut: hs.SetBinContent(i,0); hs.SetBinError(i,0)
########################################################################################################
rfile = TFile('Systematics_'+str(config['year'])+'.root','recreate')
dir = {"SignalRegion/":"sr","DoubleEleCR/":"ee","DoubleMuCR/":"mm","SingleEleCR/":"e","SingleMuCR/":"m"}

cut = None
if '>' in argv[-1]:
    cut = ( greaterThan,float(argv[-1].replace('>','')) )
    argv.pop(-1)
elif '<' in argv[-1]:
    cut = ( lessThan,float(argv[-1].replace('<','')) )
    argv.pop(-1)
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
    sumOfBkg = norm.getSumOfBkg()
    if cut != None: cut[0](sumOfBkg,cut[1])
    sumOfBkg.SetName('sumOfBkg')
    sumOfBkg.Write()
    for sample in norm.SampleList:
        if sample == 'Data':
            data_obs = norm.getSumOfBkg()
            if cut != None: cut[0](data_obs,cut[1])
            data_obs.SetName('data_obs')
            data_obs.Write()
        elif sample == "Signal":
            for signal in norm.signal:
                if cut != None: cut[0](norm.histo[signal],cut[1])
                norm.histo[signal].SetName(signal)
                norm.histo[signal].Write()
        else:
            if cut != None: cut[0](norm.histo[sample],cut[1])
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
            sumOfBkg = norm.getSumOfBkg()
            if cut != None: cut[0](sumOfBkg,cut[1])
            sumOfBkg.SetName('sumOfBkg_'+var)
            sumOfBkg.Write()
            for sample in norm.SampleList:
                if sample == 'Data': continue
                elif sample == "Signal":
                    for signal in norm.signal:
                        if cut != None: cut[0](norm.histo[signal],cut[1])
                        norm.histo[signal].SetName(signal+'_'+var)
                        norm.histo[signal].Write()
                else:
                    if cut != None: cut[0](norm.histo[sample],cut[1])
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
if cut != None: variable = variable+cut[0](None,cut[1])
var_hs = TH1F("variable",variable+';'+norm.name,1,0,1)
var_hs.Write()
