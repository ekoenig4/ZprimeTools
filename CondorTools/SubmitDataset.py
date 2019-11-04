import os
import sys
from multiprocessing import Process
import SubmitCondor
sys.path.append(SubmitCondor.repo_path)

from datasets import dataset
labelmap = { 'dyjets':'DY','ewk':'','gjets':'GJets','qcd':'QCD','ttjets':'TTJets','wjets':'W','zjets':'Z','met':'METdata_','egamma':'EGdata_' }

options = {
    'year':None,
    'region':None,
    'parallel':False
}
    
def submit(data,sub=None,label=None,split=-1,filelist=False):
    if data not in dataset: print '%s not found in dataset' % data; exit()
    if label is None: label = labelmap[data]
    subset = dataset[data]

    if sub is None: sublist = subset.keys()
    elif type(sub) != list: sublist = [sub]
    else: sublist = sub

    for sub in sublist:
        if sub not in subset: print '%s not found in subset' % sub; continue
        for i,input in enumerate(subset[sub]):
            clabel = '%s%s_%i' % (label,sub,i)
            nlabel = '%s%s_%i' % (labelmap[data],sub,i)
            command = ['analyze',input,'post%s.root' % clabel,'-1','10000',nlabel,'split_%i' % split]
            if filelist: command = ['-f'] + command
            if options['region'] is not None: command = ['-r',options['region']] + command
            if options['year'] is not None: command = ['-y',options['year']] + command

            if options['parallel']:
                Process(target=SubmitCondor.submit,args=(command,True)).start()
            else:
                SubmitCondor.submit( command )
    

