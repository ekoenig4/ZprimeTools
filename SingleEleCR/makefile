.PHONY = test

testDir=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190512_161613/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h ZprimeJetsCommon.C
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsCommon.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
