import os
import json

jsonlist = {}
eralist = ['A','B','C','D']
egamma_pattern = 'postEGdata_%s'
met_pattern = 'postMETdata_%s'

for era in eralist:
    for pattern in (egamma_pattern,met_pattern):
        jsonlist[ pattern % era ] = {}

def AddToJson(fname):
    for pattern,jmap in jsonlist.iteritems():
        if pattern in fname: break
        else: jmap = None
    if jmap == None: return
    with open('.output/%s' % fname,"r") as f: text = f.readlines()
    for line in text:
        data = line.split("|")
        run = data[0]
        if run not in jmap: jmap[run] = []
        lumilist = data[1].replace('[','').replace(']','')
        for lumi in lumilist.split(','):
            if lumi not in jmap[run]: jmap[run].append( int(lumi) )
for fname in os.listdir('.output'):
    if fname.endswith('.root'): AddToJson(fname)
print "Merge Successful."
####################################################################
def FormatJson(jmap):
    for run,lumis in jmap.iteritems():
        jmap[run] = []
        lumis.sort()
        first = lumis[0]
        last = lumis[0]
        for lumi in lumis:
            if lumi - last > 1:
                jmap[run].append( [first,last] )
                first = lumi
            last = lumi
        if not any(jmap[run]): jmap[run].append( [first,last] )
def WriteJson(jmap,output):
    if not any(jmap): return
    output = output.replace('post','processedLumis_')+".json"
    print output
    FormatJson(jmap)
    with open(output,'w') as jfile:
        jfile.write('{\n')
        for i,run in enumerate(sorted(jmap.keys(),key=int)):
            jfile.write('    "%s": [\n' % run)
            lumistr = [ str(lumi) for lumi in jmap[run] ]
            lumistr = ','.join(lumistr)
            jfile.write('          %s\n' % lumistr)
            jfile.write('     ]' + (',\n' if i+1 < len(jmap) else '\n'))
        jfile.write('}\n')
            
    
print "Creating JSONS"
for output,jmap in jsonlist.items():
    WriteJson(jmap,output)
################################
print "Finished."        
