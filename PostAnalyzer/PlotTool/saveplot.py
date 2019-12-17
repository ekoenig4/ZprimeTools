#!/usr/bin/env python

from ROOT import *
from sys import argv,path
from PlotTool import *
from os import system,getcwd,path,mkdir
import config

gROOT.SetBatch(1)

def printVars(obj):
    for var,val in vars(obj).iteritems():
        print var,':',val
    exit()

outdir = "Systematics"
if not path.isdir(outdir): mkdir(outdir)
dir = {"SignalRegion":"sr","DoubleEleCR":"ze","DoubleMuCR":"zm","SingleEleCR":"we","SingleMuCR":"wm"}

def GetZWLinking(rfile):
    if type(rfile) == str: rfile = TFile.Open(rfile)
    rfile.cd(); rfile.cd('sr')
    lhistos = {}
    keylist = [ key.GetName().replace('WJets','ZWlink') for key in gDirectory.GetListOfKeys() if 'WJets' in key.GetName() and 'WJets' != key.GetName() ]
    wjet_norm = gDirectory.Get('WJets')
    zjet_norm = gDirectory.Get('ZJets')
    lhistos['ZWlink'] = GetRatio(zjet_norm,wjet_norm).Clone('ZWlink')
    for key in keylist:
        wkey = '%s_WJets' % key; zkey = '%s_ZJets' % key
        wjet_unc = gDirectory.Get(key.replace('ZWlink','WJets'))
        zjet_unc = gDirectory.Get(key.replace('ZWlink','ZJets'))
        lhistos[wkey] = GetRatio(zjet_norm,wjet_unc).Clone(wkey)
        lhistos[zkey] = GetRatio(zjet_unc,wjet_norm).Clone(zkey)
    rfile.cd(); rfile.mkdir('sr/zwlink'); rfile.cd('sr/zwlink')
    for key,hs in lhistos.iteritems():
        hs.Write()
##################################################################

def GetTransferFactors(rfile):
    if type(rfile) == str: rfile = TFile.Open(rfile)
    tfactors = {'ZJets':{},'WJets':{}}
    varmap = {'ZJets':{'sample':'DYJets','regions':['ze','zm']},
              'WJets':{'sample':'WJets' ,'regions':['we','wm']}}
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
    for sample,transfer in tfactors.iteritems():
        for region,histos in transfer.iteritems():
            rfile.cd(); rfile.cd(region);
            rfile.mkdir('%s/transfer' % region); rfile.cd('%s/transfer' % region)
            for key,hs in histos.items():
                hs.Write()
###################################################################

def saveplot(variable):
    print variable
    lumi = max( config.lumi.values() )
    centmap = {}
    for region,nhisto in config.regions.iteritems():
        centmap[region] = Region(path=region,lumi=lumi,show=False)
        centmap[region].initiate(variable+'_'+nhisto)
        centmap[region].setSumOfBkg()
        varname = centmap[region].varname.split('_')[0]
    rfile = TFile( "%s/%s_%s.sys.root" % (outdir,varname,config.version) ,'recreate')
    for region,norm in centmap.iteritems():
        print region
        directory = rfile.mkdir(dir[region]); directory.cd()
        norm["SumOfBkg"].histo.Write("SumOfBkg")
        for process in norm:
            if process.proctype == 'data':
                if region == 'SignalRegion':
                    data_obs = norm["SumOfBkg"].histo.Clone("data_obs")
                else:
                    data_obs = process.histo.Clone("data_obs")
                data_obs.Write()
            elif process.proctype == 'signal':
                for subprocess in process:
                    signal = subprocess.histo.Clone(subprocess.process)
                    signal.Write()
            else:
                bkg = process.histo.Clone(process.process)
                bkg.Write()
        for unclist in config.Uncertainty.values():
            for unc in unclist:
                for process in norm:
                    process.addUnc(unc,show=False)
                    if process.proctype == 'data': continue
                    elif process.proctype == 'signal':
                        for subprocess in process:
                            up,dn = subprocess.nuisances[unc].GetHistos()
                            up = up.Clone('%s_%sUp' % (subprocess.process,unc))
                            dn = dn.Clone('%s_%sDown' % (subprocess.process,unc))
                            up.Write();dn.Write()
                    else:
                        up,dn = process.nuisances[unc].GetHistos()
                        up = up.Clone('%s_%sUp' % (process.process,unc))
                        dn = dn.Clone('%s_%sDown' % (process.process,unc))
                        up.Write(); dn.Write()
    ###########################################################################
    GetZWLinking(rfile)
    GetTransferFactors(rfile)
    rfile.cd()
    lumi_hs = TH1F("lumi","lumi",1,0,1)
    lumi_hs.SetBinContent(1,norm.lumi)
    lumi_hs.Write()
    year_hs = TH1F("year","year",1,0,1)
    year_hs.SetBinContent(1,config.year)
    year_hs.Write()
    var_hs = TH1F("variable",variable+';'+norm.name,1,0,1)
    var_hs = b_info.template.Clone('variable')
    var_hs.Reset(); var_hs.SetTitle(variable); var_hs.GetXaxis().SetTitle(norm.name);
    var_hs.Write()
    rfile.Close()
################################################################################
if __name__ == "__main__":

    args = parser.parse_args()
    for variable in args.argv: saveplot(variable)
