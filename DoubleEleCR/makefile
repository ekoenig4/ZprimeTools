.PHONY = test

testDir=/hdfs/store/user/ekoenig4/MonoZprimeJet/NTuples/2018/MC2018_Autumn18_June2019/DYJets/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsClass.h ZprimeJetsCommon.C
	g++ -Wno-deprecated ZprimeJetsClass.C ZprimeJetsInit.C ZprimeJetsCommon.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
