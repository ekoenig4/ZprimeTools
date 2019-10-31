interface=${CMSSW_BASE}/src/MonoZprimeJet/interface
plugin=${CMSSW_BASE}/src/MonoZprimeJet/2016/plugins

rflags = -I$ROOTSYS/include -L$ROOTSYS/lib `root-config --cflags` `root-config --libs` -lFoam -lMathMore -Wno-deprecated

analyze: Zprime* $(plugin)/Zprime* $(interface)/Zprime* RootFiles PlotTool
	g++ -I $(interface) -I $(plugin)  Zprime*.C $(interface)/Zprime*.C $(plugin)/Zprime*.C -o analyze $(rflags)

RootFiles:
	if [ ! -d RootFiles ]; then ln -s ../RootFiles/; fi

PlotTool:
	if [ ! -d PlotTool ]; then ln -s ../PlotTool/; fi

test: analyze
	./analyze

clean:
	rm post*.root

condor_clean:
	rm -r .output
	rm -r .status

condor_submit: analyze
	./signalsubmit.sh
	./submitDATA.sh
	./submitMC.sh

hadd: PlotTool
	./PlotTool/plotter.py

plot:
	./PlotTool/plotter.py $(variable)
