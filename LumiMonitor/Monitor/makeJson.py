
import os
label = "postDoubleMu"
files = [ file for file in os.listdir(".") if label in file ]
jsonlist = {}
for file in files:
    jsonlist[file] = {}
    with open(file,"r") as f: text = f.readlines()
    for line in text:
        data = line.split("|")
        run = data[0]
        lumiInfo = data[1]
        lumilist = [ int(lumi.split(',')[0].replace("[","")) for lumi in lumiInfo.split() ]
        lumilist.sort()
        lumis = "[["+str(lumilist[0])
        last = lumilist[0]
        for lumi in lumilist[1:]:  
            if lumi - last > 1:
                lumis += ","+str(last)+"],["+str(lumi)
            if lumi == lumilist[-1]:
              lumis += ","+str(lumi)+"]]"
            last = lumi
        ################################
        print run,lumis
    exit()
