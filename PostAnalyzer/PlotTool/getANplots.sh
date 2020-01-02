#!/bin/sh

extraction1='-b incu40 ChNemPtFrac -c "ChNemPtFrac>0.5"'
extraction2='-b incl40 ChNemPtFrac'
extraction3='ChNemPtFrac'
extraction_uncertainty='-u JES PFU_ECAL PSW_fsrDef PSW_isrCon'
nvariables='ChNemPt ChNemPt123 recoil nJets j1pT j1Eta j1Phi nVtx'
singleleps='LeptonPt LeptonEta'
doubleleps='dileptonM dileptonPt leadingLeptonPt leadingLeptonEta subleadingLeptonEta subleadingLeptonPt'
uncertainty='-u JES'

options=$@
plot() {
    echo "./PlotTool/plotter.py" $@
    ./PlotTool/plotter.py $@
}

run() {
    pushd $1
    shift 1
    array="$@ $nvariables"
    for variable in ${array[@]}; do
	plot $options --sub AN --autovar $variable $uncertainty || exit 1
    done
    plot $options --sub AN --autovar $extraction1 $extraction_uncertainty || exit 1
    plot $options --sub AN --autovar $extraction2 $extraction_uncertainty || exit 1
    plot $options --sub AN --autovar $extraction3 $extraction_uncertainty || exit 1
    popd
}

run2() {
    region=$1
    shift 1
    array="$@ $nvariables"
    for variable in ${array[@]}; do
	plot --run2 $region $options $variable || exit 1
    done
    plot --run2 $region $options $extraction1 || exit 1
    plot --run2 $region $options $extraction2 || exit 1
    plot --run2 $region $options $extraction3 || exit 1
}

region() {
    run SignalRegion || exit 1
    run SingleEleCR $singleleps  || exit 1
    run SingleMuCR $singleleps || exit 1
    run DoubleEleCR $doubleleps || exit 1
    run DoubleMuCR $doubleleps || exit 1
}

region2() {
    run2 SignalRegion || exit 1
    run2 SingleEleCR $singleleps || exit 1
    run2 SingleMuCR $singleleps || exit 1
    run2 DoubleEleCR $doubleleps || exit 1
    run2 DoubleMuCR $doubleleps || exit 1
}

YEARS="2016 2017 2018"
if [ -d "2016" ]; then
    region2
else
    region
fi
