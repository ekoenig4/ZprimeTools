#!/usr/bin/env python
from ROOT import *
import os
from argparse import ArgumentParser

def init(input,output,filerange):
    chain = TChain("phoJetNtuplizer/eventTree")
    fileNumber = 0
    inFiles = 0
    for filename in filerange:
        fullpath = input + filename
        chain.Add(fullpath)
        print 'Adding File to chain',fullpath
        inFiles += 1
    print inFiles,'files added.'
    return chain

def printOut(json,output):
    print json
    with open(output,"w") as out:
        for run,lumilist in json.iteritems():
            lumis = sorted(lumilist.keys())
            out.write( '%s|[%s]\n' % (run,','.join(lumis)) )

def getargs():
    parser = ArgumentParser()
    parser.add_argument("argv",type=str,nargs='+')
    args = parser.parse_args()
    args.input = args.argv[0]
    args.output = args.argv[1]
    args.maxevents = int(args.argv[2])
    args.reportevery = int(args.argv[3])
    args.range = args.argv[4:]
    return args
    
def main():
    args = getargs()
    chain = init(args.input,args.output,args.range)

    json = {}
    total = chain.GetEntries()
    print 'Total Events:        %i' % total
    if args.maxevents < total and not -1: total = args.maxevents
    print 'Processesing Events: %i' % total
    for i,e in enumerate(chain):
        run = str(e.run)
        lumis = str(e.lumis)

        if run not in json: json[run] = {}
        if not lumis in json[run]: json[run][lumis] = 0
        json[run][lumis] += 1
        if i % args.reportevery == 0: print 'Finished entry',i,'/',total
    printOut(json,args.output)

if __name__ == "__main__": main()
