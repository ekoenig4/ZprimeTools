.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools2017/plugins/

testDir=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190512_161613/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJets* $(plugin)/ZprimeJets*
	g++ -I $(plugin) -Wno-deprecated ZprimeJets*.C $(plugin)/*.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
