import os

jsonlist = {}
eralist = ['A','B','C','D']
egamma_pattern = 'postEGdata_%s'
met_pattern = 'postMETdata_%s'

for era in eralist:
    for pattern in (egamma_pattern,met_pattern):
        jsonlist[ pattern % era ] = {}

def AddJson(fname,json):
    with open(file,"r") as f: text = f.readlines()
    for line in text:
        data = line.split("|")
        run = data[0]
        if run not in json: json[run] = []
        lumilist = data[1].replace('[','').replace(']','')
        for lumi in lumilist.split(','):
            if lumi not in json[run]: json[run].append( int(lumi) )
for i,file in enumerate(files):
    for label in jsonlist:
        if label in file: json = jsonlist[label]
    AddJson(file,json)
    # print "Merged Files:",i+1,"of",len(files)
print "Merge Successful."
####################################################################
def WriteJson(json,output):
    output = output.replace('post','processedLumis_')+".json"
    print output
    with open(output,"w") as f:
        f.write('{')
        for i,(run,lumis) in enumerate(json.items()):
            if i != 0: f.write(",")
            f.write('"'+run+'":')
            lumis.sort()
            value = "[["+str(lumis[0])
            last = lumis[0]
            for lumi in lumis[1:]:  
                if lumi - last > 1:
                    value += ","+str(last)+"],["+str(lumi)
                last = lumi
            value += ","+str(last)+"]]"
            f.write(value)
        f.write("}")
print "Creating JSONS"
for output,json in jsonlist.items(): WriteJson()
################################
print "Finished."        
