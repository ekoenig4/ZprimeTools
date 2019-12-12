#!/bin/sh

extraction1='-b incu40 --nhist ChNemPtFrac -c "ChNemPtFrac>0.5"'
extraction2='-b incl40 --nhist ChNemPtFrac'
nvariables='ChNemPtFrac ChNemPt ChNemPt123 recoil nJets j1pT j1Eta j1Phi nVtx'
singleleps='LeptonPt LeptonEta'
doubleleps='dileptonM dileptonPt leadingLeptonPt leadingLeptonEta subleadingLeptonEta subleadingLeptonPt'

options=$@

run() {
    cd $1
    shift 1
    pwd
    python PlotTool/autoplotter.py $options --nhist $nvariables $@
    python PlotTool/autoplotter.py $options $extraction1
    python PlotTool/autoplotter.py $options $extraction2
    cd ../
}

run SignalRegion
run SingleEleCR $singleleps
run SingleMuCR $singleleps
run DoubleEleCR $doubleleps
run DoubleMuCR $doubleleps
