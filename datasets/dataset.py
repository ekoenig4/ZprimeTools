import json
import os
wd,wf = os.path.split(__file__)
def getDataset():
    dataset = {}
    ntuples = '%s/ntuples' % wd
    for fname in os.listdir(ntuples):
        if not fname.endswith('.json'): continue
        with open(os.path.join(ntuples,fname)) as f: data = json.load(f)
        dataset[ fname.replace('.json','') ] = dict(data)
    return dataset
dataset = getDataset()
