#!/usr/bin/env python
import sys
from os import path, system, mkdir, listdir, rename, remove, chdir, getenv
from CondorConfig import CondorConfig
from argparse import ArgumentParser

script_path = '/'.join(path.realpath(__file__).split('/')[:-1])
cmssw_base = getenv("CMSSW_BASE")
USERPROXY = "x509up_u23216"
NFILE_PER_BATCH = 60

def init():
    #Create Directories to put condor files in
    #Where executable and output files go
    if not path.isdir(".output/"): mkdir(".output/")
    #Where all condor output, log, and error files go
    if not path.isdir(".status/"): mkdir(".status/")
def getargs():
    parser = ArgumentParser()
    parser.add_argument('runargs',help='Specify arguments for run',type=str,nargs='+')
    parser.add_argument('-y','--year',help='Specify year of run',type=str,default='')
    parser.add_argument('-r','--region',help='Specify region of run',type=str,default='')
    args = parser.parse_args()
    args.error = False
    def checkScript(arg):
        if path.isfile(arg): return arg
        else:
            print 'Unable to find script %s' % arg
            args.error = True
    def checkRootDir(arg):
        if path.isdir(arg):
            rfiles = [ fn.replace(".root","") for fn in listdir(arg) if fn.endswith(".root") ]
            if any(rfiles): return arg,rfiles
            print '%s does not have any root files' % arg
        else:
            print '%s is not a directory' % arg
            args.error = True
    def checkOutput(arg):
        if arg.endswith('.root'): return arg[:-5]
    def checkSplit(arg):
        nbatches = 1
        nbatches=int(arg.replace("split_",""))
        #If split_-1 is used program will set custom split for each directory so that there are nfile of files in each batch
        if nbatches == -1: nbatches = len(args.rfiles)/NFILE_PER_BATCH
        #Dealing with some edge cases
        if nbatches == 0: nbatches = 1
        return nbatches
    args.script = checkScript(args.runargs[0])
    args.inputdir,args.rfiles = checkRootDir(args.runargs[1])
    args.outputfile = checkOutput(args.runargs[2])
    args.maxevents = int(args.runargs[3])
    args.reportevery = int(args.runargs[4])
    args.label = args.runargs[5]
    args.nbatches = checkSplit(args.runargs[6])

    if args.error:
        print 'Errors found in arguments, exitting'
        exit()
    return args

def stripDataset(rootFiles):
    #Getting file number instead of the entire filename
    dataset=None
    for i in range(len(rootFiles[0]) - 1, -1,-1): #Loop through filename backwards
        if rootFiles[0][i] == "_" or rootFiles[0][i] == "-":
            dataset = rootFiles[0][:i+1]
            break
    for i in range(len(rootFiles)):rootFiles[i] = rootFiles[i].replace(dataset,"")
    rootFiles.sort(key=int)

def removeOldFiles(filekey,label):
    #Remove any old condor files
    filekey = filekey.replace(".root","_")
    for fn in listdir(".output/"):
        if filekey in fn:
            remove(".output/"+fn)

    if not path.isdir(".status/"+label): mkdir(".status/"+label)
    for fn in listdir(".status/"+label): remove(".status/"+label+"/"+fn)

def splitArgument(nbatches,rfiles,config):
    #Get how many files are in each batch
    batch = len(rfiles)
    binsize = batch/nbatches
    print "Total files:   %i" % batch
    print "Files per job: %i" % binsize
    for i in range(nbatches):
        if nbatches == 1: fileRange = "-1"
        else:
            #0-100/200-250/300-300
            fileRange = rfiles[0]
            if batch/binsize == 1:
                binsize = batch
            for j in range(1,binsize):
                if (int(rfiles[j]) - int(rfiles[j-1]) != 1):
                    fileRange += "-"+rfiles[j-1]+"/"+rfiles[j]

            fileRange += "-"+rfiles[binsize - 1]
            for j in range(binsize - 1, -1, -1):
                rfiles.pop(j) #Remove files already accounted for
                batch-=1

        print "----Batch",i+1,fileRange

        #Append argument lines to condor_submit file adding the file range for this batch
        config['Arguments'] = "$(script) $(inputdir) $(outputfile)_$(Process).root $(maxevents) $(reportevery) " + fileRange
        config.queue()

def main():
    init()
    args = getargs()
    print "Processesing %s" % args.outputfile
    stripDataset(args.rfiles)
    removeOldFiles(args.outputfile,args.label)
    #Assure executable file is in .output/
    if not path.isfile('.output/runAnalyzer.sh'): system('cp %s/runAnalyzer.sh .output/' % script_path)
    system('cp %s .output' % args.script)
    
    #Beginning to write condor_submit file
    config = CondorConfig()
    config['x509userproxy'] = '/tmp/%s' % USERPROXY
    config['universe'] = 'vanilla'
    config['Executable'] = 'runAnalyzer.sh'
    config['Notification'] = 'never'
    config['WhenToTransferOutput'] = 'On_Exit'
    config['ShouldTransferFiles'] = 'yes'
    config['Requirements'] = '(TARGET.UidDomain == "hep.wisc.edu" && TARGET.HAS_CMS_HDFS)'
    config['on_exit_remove'] = '(ExitBySignal == FALSE && (ExitCode == 0 || ExitCode == 42 || NumJobStarts>3))'
    config['+IsFastQueueJob'] = 'True'
    config['getenv'] = 'true'
    config['request_memory'] = 1992
    config['request_disk'] = 2048000
    config['script'] = args.script
    config['inputdir'] = args.inputdir
    config['outputfile'] = args.outputfile
    config['maxevents'] = args.maxevents
    config['reportevery'] = args.reportevery
    config['label'] = args.label
    config['Batch_Name'] = '%s%s_$(label)' % (args.region,args.year)
    config['Transfer_Input_Files'] = ['$(script)','../../RootFiles']
    config['output'] = '../.status/$(label)/$(Process)_$(label).out'
    config['error']  = '../.status/$(label)/$(Process)_$(label).err'
    config['Log']    = '../.status/$(label)/$(Process)_$(label).log'
    splitArgument(args.nbatches,args.rfiles,config)
    config.write('.output/condor_%s' % args.label)
    #Move into .output/ and run newly made condor_submit file
    chdir(".output/")
    system("condor_submit condor_%s" % args.label)
    
    
if __name__ == "__main__": main()
