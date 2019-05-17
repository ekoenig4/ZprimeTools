.PHONY = test

testDir=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019/ZJetsToNuNu_HT-600To800_13TeV-madgraph/crab_job_ZJetsToNuNu_HT600-800/190508_233402/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h ZprimeJetsCommon.C
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsCommon.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
