import json
import os
wd,wf = os.path.split(__file__)
if wd == '': wd = '.'
EFLAGS = {
    ValueError:False
}
def getDataset(label):
    dataset = {}
    jsonfile = '%s/ntuples/%s.json' % (wd,label)
    if not os.path.isfile(jsonfile): return None
    with open(jsonfile) as f:
        try:data = json.load(f)
        except ValueError:
            print '%s.json not formatted correctly' % label
            return {}
    def checkdir(directory):
        if os.path.isdir(directory): return True
        else: print '%s not a directory' % directory; EFLAGS[ValueError] = True; return False
    dataset[label] = { subdir:[ directory for directory in data[subdir] if checkdir(directory) ] for subdir in data }
    return dataset
    
def getAllDatasets():
    dataset = {}
    ntuples = '%s/ntuples/' % wd
    for fname in os.listdir(ntuples):
        if fname.endswith('.json'): dataset.update( getDataset(fname.replace('.json','')) )
    if EFLAGS[ValueError]: print 'Invalid directories detected, exiting...'; exit()
    return dataset

if __name__ == '__main__':
    datasets = getAllDatasets()

    datalist = ['egamma','met','zjets','wjets','dyjets','gjets','ttjets','ewk','qcd']
    for data in datalist:
        for sub in datasets[data]:
            print '%s----%s' % (data,sub)
            for directory in datasets[data][sub]:
                print '------%s' % directory
