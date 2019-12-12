from ROOT import *
from PlotTool import *
from config import config

sample = Region(show=False)

sample.processes = {'test':Process("test",["test_mc"],{"test_mc":1},"bkg",lumi=100000,color=kGray)}
sample.SampleList = ['test']

nhist = config['regions'][sample.region+'/']

unc = 'JES'

sample.initiate('ChNemPtFrac_%s' % nhist)
sample.addUnc(unc,show=True)

process = sample.processes['test']

norm = process.histo
uncUp = process.nuisances[unc]['Up']
uncDn = process.nuisances[unc]['Down']

for ibin in range(1,norm.GetNbinsX()+1):
    print ibin,uncDn[ibin],norm[ibin],uncUp[ibin]
