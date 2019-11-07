import json
import os
wd,wf = os.path.split(__file__)
EFLAGS = {
    ValueError:False
}
def getDataset():
    dataset = {}
    ntuples = '%s/ntuples' % wd
    for fname in os.listdir(ntuples):
        if not fname.endswith('.json'): continue
        with open(os.path.join(ntuples,fname)) as f: data = json.load(f)
        def checkdir(directory):
            if os.path.isdir(directory): return True
            else: print '%s not a directory' % directory; EFLAGS[ValueError] = True; return False
        dataset[ fname.replace('.json','') ] = { subdir:[ directory for directory in data[subdir] if checkdir(directory) ] for subdir in data }
        
    if EFLAGS[ValueError]: print 'Invalid directories detected, exiting...'; exit()
    return dataset
dataset = getDataset()
