.PHONY = test

testDir=/hdfs/store/user/uhussain/Zprime_Ntuples_May2018/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT600to800/180528_*/0000/

plugin=${CMSSW_BASE}/src/ZprimeTools*/plugins/
rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.* $(plugin)/*
	g++ -I $(plugin) -Wno-deprecated ZprimeJetsClass.C $(plugin)/* -o analyze $(rflags)

test: analyze
	./analyze $(testDir) test.root 5000 100 1-1
