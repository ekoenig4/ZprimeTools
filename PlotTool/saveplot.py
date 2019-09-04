#!/usr/bin/env python

from ROOT import *
from sys import argv
from sys import path
from Plot import datamc,getargs,GetRatio
from os import system,getcwd,path,mkdir
from cfg_saveplot import config
from mcinfo import lumi as mc,version
from optparse import OptionParser

gROOT.SetBatch(1)

outdir = "Systematics"
if not path.isdir(outdir): mkdir(outdir)
dir = {"SignalRegion/":"sr","DoubleEleCR/":"ee","DoubleMuCR/":"mm","SingleEleCR/":"e","SingleMuCR/":"m"}

def GetTransferFactors(rfile):
    if type(rfile) == str: rfile = TFile.Open(rfile)
    tfactors = {'ZJets':{},'WJets':{}}
    varmap = {'ZJets':{'sample':'DYJets','regions':['ee','mm']},
              'WJets':{'sample':'WJets' ,'regions':['e','m']}}
    for sample,transfer in tfactors.items():
        rfile.cd(); rfile.cd('sr')
        sr = { key.GetName():rfile.Get('sr/%s' % key.GetName()).Clone() for key in gDirectory.GetListOfKeys()
               if sample in key.GetName() }
        infomap = varmap[sample]
        for region in infomap['regions']:
            thistos = {}
            rfile.cd(); rfile.cd(region)
            cr = { key.GetName().replace(infomap['sample'],sample):rfile.Get( '%s/%s' % (region,key.GetName()) ).Clone() for key in gDirectory.GetListOfKeys()
                   if infomap['sample'] in key.GetName() }
            for key in cr:
                cr_hs = cr[key]
                sr_hs = sr[key]
                thistos[key] = GetRatio(cr_hs,sr_hs).Clone(key)
            transfer[region] = thistos
    # Write transfer factor histograms to systematic file
    for sample,transfer in tfactors.items():
        for region,histos in transfer.items():
            rfile.cd(); rfile.cd(region);
            rfile.mkdir('%s/transfer' % region); rfile.cd('%s/transfer' % region)
            for key,hs in histos.items():
                hs.Write()
###################################################################

def saveplot(variable):
    print variable
    cut = ''
    if '>' in variable: cut = '>'+variable.split('>')[-1]
    if '<' in variable: cut = '<'+variable.split('<')[-1]
    rfile = TFile( "%s/%s_%s.sys.root" % (outdir,variable,version) ,'recreate')
    Uncertainty = config['Uncertainty']
    lumi = max( lumi for region,lumi in mc.items() )
    for region,nhisto in config['regions'].items():
        rfile.cd()
        var = variable+'_'+nhisto+cut
        print region
        directory = rfile.mkdir(dir[region])
        norm = datamc(fileDir=region,lumi=lumi,show=False)
        norm.initiate(var)
        directory.cd()
        sumOfBkg = norm.getSumOfBkg()
        sumOfBkg.SetName('sumOfBkg')
        sumOfBkg.Write()
        for sample in norm.SampleList:
            if sample == 'Data':
                data_obs = norm.getSumOfBkg()
                data_obs.SetName('data_obs')
                data_obs.Write()
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
                print '\t',var,
                input = variable+'_'+str( int(info[id]) + int(nhisto) )+cut
                norm.initiate( input )
                directory.cd()
                sumOfBkg = norm.getSumOfBkg()
                sumOfBkg.SetName('sumOfBkg_'+var)
                sumOfBkg.Write()
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
            print
    ###########################################################################
    GetTransferFactors(rfile)
    rfile.cd()
    lumi_hs = TH1F("lumi","lumi",1,0,1)
    lumi_hs.SetBinContent(1,norm.lumi)
    lumi_hs.Write()
    year_hs = TH1F("year","year",1,0,1)
    year_hs.SetBinContent(1,int(norm.version))
    year_hs.Write()
    var_hs = TH1F("variable",variable+';'+norm.name,1,0,1)
    var_hs.Write()
    rfile.Close()
################################################################################
if __name__ != "__main__": exit()

options,args = getargs()
for variable in args: saveplot(variable)
