#!/bin/sh

nvariables='recoil nJets j1pT j1Eta j1Phi nVtx'
singleleps='h_LeptonPt h_LeptonEta'
doubleleps='h_dileptonM h_dileptonPt h_leadingLeptonPt h_leadingLeptonEta h_subleadingLeptonEta h_subleadingLeptonPt'

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
