.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools2018/plugins/

testDir=/hdfs/store/user/varuns/MC2018_Autumn18_May2019/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT600-800/190516_074725/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.* $(plugin)/ZprimeJets*
	g++ -I $(plugin) -Wno-deprecated ZprimeJetsClass.C $(plugin)/*.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
