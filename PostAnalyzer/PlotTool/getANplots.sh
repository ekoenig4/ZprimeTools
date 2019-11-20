#!/bin/sh

nvariables='recoil nJets j1pT j1Eta j1Phi nVtx'
singleleps='LeptonPt LeptonEta'
doubleleps='dileptonM dileptonPt leadingLeptonPt leadingLeptonEta subleadingLeptonEta subleadingLeptonPt'

options=$@

run() {
    cd $1
    shift 1
    pwd
    python PlotTool/autoplotter.py $options --nhist $nvariables $@
    cd ../
}

run SignalRegion
run SingleEleCR $singleleps
run SingleMuCR $singleleps
run DoubleEleCR $doubleleps
run DoubleMuCR $doubleleps
