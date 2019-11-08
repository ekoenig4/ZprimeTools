import os
wd,wf = os.path.split(__file__)
if wd == '': wd = '.'
EFLAGS = {
    ValueError:False
}

if os.path.isdir('ntuples/'): ntuple_path = 'ntuples'
else: ntuple_path = '%s/ntuples' % wd
def getDataset(label):
    dataset = {}
    fname = '%s/%s.txt' % (ntuple_path,label)
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
    ntuples = ntuple_path
    for fname in os.listdir(ntuples):
        if fname.endswith('.txt'): dataset.update( getDataset(fname.replace('.txt','')) )
    if EFLAGS[ValueError]: print 'Invalid directories detected, exiting...'; exit()
    return dataset

if __name__ == '__main__':
    datalist = ['egamma','met','signal','zjets','wjets','dyjets','gjets','ttjets','ewk','qcd']
    from sys import argv
    if len(argv) == 1: datasets = getAllDatasets()
    else:
        datasets = {}
        for data in argv[1:]: datasets.update( getDataset(data) )
    import re
    def sort_nicely( l ):
        """ Sort the given list in the way that humans expect.
        """
        convert = lambda text: int(text) if text.isdigit() else text
        alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
        l.sort( key=alphanum_key )
    for data in datalist:
        if data not in datasets: continue
        sublist = datasets[data].keys()
        sort_nicely(sublist)
        for sub in sublist:
            print '%s----%s' % (data,sub)
            for directory in datasets[data][sub]:
                print '------%s' % directory
