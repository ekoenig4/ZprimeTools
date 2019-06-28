import os
import subprocess
from sys import argv
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-r","--resubmit",help="resubmit condor jobs that didn't produce output files",action="store_true",default=False)
parser.add_option("-v","--verbose",help="print all files being checked",action="store_true",default=False)

(options,args) = parser.parse_args()
cwd = os.getcwd()

def check(dir):
    print dir
    os.chdir(dir+'/.output/')
    condor = [file for file in os.listdir('.') if 'condor_' in file]
    condor.sort()
    finished = True
    total = {'jobs':0,'completed':0,'removed':0,'idle':0,'running':0,'held':0,'suspended':0}
    for i,file in enumerate(condor):
        if options.verbose: print "Checking",file,"\t|",i,"of",len(condor)
        with open(file,'r') as f:
            arglist = []
            for line in f.readlines():
                if 'Argument' in line: arglist.append(line)
                if 'Log'      in line: logdir = line.split()[2].split("$")[0]
        for f in os.listdir(logdir):
            if '.log' in f:
                logfile = logdir+'/'+f
                break
        #########################
        with open(logfile,'r') as f:
            try: cluster = f.readlines()[0].split()[1].split(".")[0].replace("(","")
            except IndexError: cluster = "-1"
        complete = True
        incomplete = 0
        for arg in arglist:
            output = arg.split()[3]
            if not os.path.isfile(output):
                # print "\t",output,"Not Found"
                incomplete += 1
                complete = False
                finished = False
        if incomplete != 0:
            if not options.verbose: print "Checking",file,"\t|",i,"of",len(condor)
            condor_q = subprocess.Popen(['condor_q',cluster],stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
            stdout, stderr = condor_q.communicate()
            stdout = stdout.split('\n')[-2]
            tmp = stdout.split()
            if cluster != "-1": status = {'jobs':int(tmp[0]),'completed':int(tmp[2]),'removed':int(tmp[4]),'idle':int(tmp[6]),'running':int(tmp[8]),'held':int(tmp[10]),'suspended':int(tmp[12])}
            else: status = {'jobs':0,'completed':0,'removed':0,'idle':0,'running':0,'held':0,'suspended':0}
            for type in status: total[type] += status[type]
            if status['jobs'] == 0:
                print "\t",incomplete,"of",len(arglist),"File(s) Not Found"
                if status['held'] != 0 or status['removed'] != 0:
                    complete=False
            else:
                print "\t",stdout
                complete=True
        if not complete and options.resubmit:
            for f in os.listdir(logdir): os.remove(logdir+'/'+f)
            os.system('condor_submit '+file)
    if finished: print "Finished."
    else:
        print "Total:",total['jobs'],"jobs;",total['completed'],"completed,",total['removed'],"removed,",
        print total['idle'],"idle,",total['running'],"running,",total['held'],"held,",total['suspended'],"suspended"
    os.chdir(cwd)
    print
###################################################################################################################

for dir in args: check(dir)
