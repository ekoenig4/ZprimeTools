import os
import sys
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-t","--total",help="Sum all the lumis",action="store_true",default="False")
(options,args) = parser.parse_args()

directories = args
result = {}
eraList = []

for d in directories:
    fname = d+"/lumi.txt"
    if not os.path.isfile(fname): continue
    with open(fname,"r") as f:
        text = f.readlines()
        current = ""
        for i in range(len(text)):
            line = text[i]
            if "processedLumis" in line:
                current = line.replace(".json","").replace("\n","")
                current = current.split("v")[0]
                if current not in result:
                    result[current] = 0
                    eraList.append(current)
            if "#Summary:" in line:
                lumi = float(text[i+4].split("|")[6])
                result[current] += lumi

total = 0
for era in eraList:
    print era,":",result[era]
    total += result[era]

if options.total:
    print "Total",":",total

