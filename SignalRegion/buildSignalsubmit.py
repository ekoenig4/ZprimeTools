import os
import re
from sys import argv

mxsearch = re.compile(r'Mx\d*')
mvsearch = re.compile(r'Mv\d*')

inputdir = argv[1]
if inputdir[-1] != '/': inputdir += '/'

if not os.path.isdir(inputdir): print "%s is an invalid directory" % inputdir; exit()

signaldirs = {}

for signaldir in os.listdir(inputdir):
    mx = mxsearch.findall(signaldir)[0]
    mv = mvsearch.findall(signaldir)[0]

    if not mx in signaldirs: signaldirs[mx] = {}
    signaldirs[mx][mv] = '%s%s/' % (inputdir,signaldir)

with open('signalsubmit.sh','w') as submit:
    submit.write('#!/bin/sh\n')
    submit.write('RUN="python ${CMSSW_BASE}/src/ZprimeTools2018/CondorTools/SubmitCondor.py -y 2018 -r SR analyze"')
    submit.write('make || exit -1\n')
    mxlist = sorted(signaldirs.keys(),key=lambda x : int(x.replace('Mx','')) )
    for mx in mxlist:
        submit.write( '\necho Dark Matter Mass %s GeV\n' % mx.replace('Mx','') )
        mvdirs = signaldirs[mx]
        mvlist = sorted(mvdirs.keys(),key=lambda x : int(x.replace('Mv','')) )
        for mv in mvlist:
            mvdir = mvdirs[mv]
            submit.write( '$RUN %s post%s_%s.root -1 1000 %s_%s split_1\n' % (mvdir,mx,mv,mx,mv))
        
