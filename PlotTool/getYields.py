#!/cvmfs/cms.cern.ch/slc6_amd64_gcc630/cms/cmssw/CMSSW_10_1_6/external/slc6_amd64_gcc630/bin/python

from ROOT import *
from sys import argv, path
import Plot as plot
import os

gROOT.SetBatch(1)

samples = plot.datamc(show=0)
samples.initiate("h_cutflow")

samples.SampleList.insert(0,"Bin")
samples.histo['SumOfBkg'] = samples.getSumOfBkg()
samples.SampleList.insert(2,'SumOfBkg')
if 'Signal' in samples.SampleList:
    samples.SampleList[-1] = samples.signal[0]

for s in samples.SampleList:
    space = (15 - len(s))
    if s == "Bin": print s+space*" ",
    else: print s+space*" ",
    for ibin in samples.args:
        ibin = str(int(ibin)+1)
        if s == "Bin":
            label = samples.histo['Data'].GetXaxis().GetBinLabel(int(ibin))
            if (ibin == samples.args[0]): print label,
            else:                         print 5*" ","\t",label,
        else:
            out = ("%.6g" % samples.histo[s].GetBinContent(int(ibin)))
            if (ibin == samples.args[0]): print out,
            else:                         print "\t",out,
    print
