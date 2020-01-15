#!/bin/sh

for r in $REGIONS; do
    ./PlotTool/plotter.py --run2 $r -s Mx1_Mv1000 recoil
    ./PlotTool/plotter.py --run2 $r -s Mx1_Mv1000 -b incl40 ChNemPtFrac
    for y in $YEARS; do
	pushd $y;
	pushd $r;
	./PlotTool/plotter.py -s Mx1_Mv1000 --autovar recoil
	./PlotTool/plotter.py -s Mx1_Mv1000 --autovar -b incl40 ChNemPtFrac
	popd;
	popd;
    done
    popd;
done
	 
