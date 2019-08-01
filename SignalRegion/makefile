.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools2018/plugins/

testDir=/hdfs/store/user/ekoenig/MonoZprimeJet/NTuples/2018/MC2018_Autumn18_June2019/ZJets/ZJetsToNuNu_HT-400To600_13TeV-madgraph/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJetsClass.* $(plugin)/ZprimeJets*
	g++ -I $(plugin) -Wno-deprecated ZprimeJetsClass.C $(plugin)/*.C -o analyze $(rflags)

test:	analyze
	./analyze $(testDir) test.root 5000 100 1-1
