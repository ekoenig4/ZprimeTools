.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools2018/plugins/

testDir=/hdfs/store/user/varuns/MC2018_Autumn18_May2019/ZJetsToNuNu_HT-600To800_13TeV-madgraph/crab_job_ZJetsToNuNu_HT600-800/190512_101153/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.* $(plugin)/ZprimeJets*
	g++ -I $(plugin) -Wno-deprecated ZprimeJetsClass.C $(plugin)/*.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
