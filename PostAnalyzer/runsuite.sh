
for y in $YEARS; do
    pushd $y
    # sh PlotTool/getANplots.sh -s Mx1_Mv1000 --sub AN
    # python PlotTool/plotTransfer.py -b incu40 -c '"ChNemPtFrac>0.5"'
    # python PlotTool/plotTransfer.py recoil
    for r in $REGIONS; do
    	pushd $r
    	python PlotTool/plotShapeUnc.py -b incu40 -c '"ChNemPtFrac>0.5"'
    	python PlotTool/plotShapeUnc.py recoil
    	popd;
    done
    popd
done
