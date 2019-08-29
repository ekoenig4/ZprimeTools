.PHONY = test

plugin=${CMSSW_BASE}/src/ZprimeTools2017/plugins/

testDir=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019/ZJetsToNuNu_HT-600To800_13TeV-madgraph/crab_job_ZJetsToNuNu_HT600-800/190508_233402/0000/

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore

analyze: ZprimeJets* $(plugin)/ZprimeJets* RootFiles
	g++ -I $(plugin) -Wno-deprecated ZprimeJets*.C $(plugin)/*.C -o analyze $(rflags)

RootFiles:
	if [ ! -d RootFiles ]; then ln -s ../RootFiles/; fi

test: analyze
	./analyze $(testDir) test.root 5000 100 1-1

clean:
	rm post*.root
	rm -r DataEra
