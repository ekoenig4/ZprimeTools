.PHONY = test

testDir=/hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_102X/ZJets/ZJetsToNuNu_HT600-800/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h ZprimeJetsCommon.C
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsCommon.C -o analyze $(rflags)

test:
	./debug.sh $(testDir) test.root 5000 100 1-1
