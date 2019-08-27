.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools2018/plugins/

testDir=/hdfs/store/user/ekoenig/MonoZprimeJet/NTuples/2018/MC2018_Autumn18_June2019/DYJets/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJets* $(plugin)/ZprimeJets* RootFiles
	g++ -I $(plugin) -Wno-deprecated ZprimeJets*.C $(plugin)/*.C -o analyze $(rflags)

RootFiles:
	if [[ ! -d RootFiles ]]; then ln -s ../RootFiles; fi

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
