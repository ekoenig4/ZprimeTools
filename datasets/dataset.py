import os
wd,wf = os.path.split(__file__)
if wd == '': wd = '.'
EFLAGS = {
    ValueError:False
}
def getDataset(label):
    dataset = {}
    fname = '%s/ntuples/%s.txt' % (wd,label)
    if not os.path.isfile(fname): return None
    def checkdir(directory):
        if os.path.isdir(directory): return True
        else: print '%s not a directory' % directory; EFLAGS[ValueError] = True; return False
    with open(fname) as f:
        subset = {}; subname = None
        for line in f.readlines():
            line = line.replace('\n','')
            if '#' in line: continue
            if '>>' in line:
                subname = line.replace('>>','')
                subset[subname] = []
            elif any(line):
                if checkdir(line): subset[subname].append(line)
    dataset[label] = subset
    return dataset
    
def getAllDatasets():
    dataset = {}
    ntuples = '%s/ntuples/' % wd
    for fname in os.listdir(ntuples):
        if fname.endswith('.txt'): dataset.update( getDataset(fname.replace('.txt','')) )
    if EFLAGS[ValueError]: print 'Invalid directories detected, exiting...'; exit()
    return dataset

if __name__ == '__main__':
    datasets = getAllDatasets()

    datalist = ['egamma','met','signal','zjets','wjets','dyjets','gjets','ttjets','ewk','qcd']
    for data in datalist:
        for sub in datasets[data]:
            print '%s----%s' % (data,sub)
            for directory in datasets[data][sub]:
                print '------%s' % directory
