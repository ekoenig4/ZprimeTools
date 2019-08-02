.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools*/plugins/

testDir=/hdfs/store/user/uhussain/Zprime_Ntuples_May2018/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/180528_*/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJets* $(plugin)/ZprimeJets*
	g++ -I $(plugin) -Wno-deprecated ZprimeJets*.C $(plugin)/ZprimeJets*.C -o analyze $(rflags)

test: analyze
	./analyze $(testDir) test.root 5000 100 1-1
