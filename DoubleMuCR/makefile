.PHONY = test

testDir=/hdfs/store/user/varuns/MC2018_Autumn18_May2019//DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT400-600/190516_074631/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h ZprimeJetsCommon.C
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsCommon.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
