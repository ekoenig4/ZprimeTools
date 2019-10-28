#!/bin/sh

extraction='-b incl20 --nhist ChNemPtFrac'
nvariables='ChNemPtFrac ChNemPt ChNemPt123 h_recoil nJets j1pT j1Eta'
singleleps='h_LeptonPt h_LeptonEta'
doubleleps='h_dileptonM h_dileptonPt h_leadingLeptonPt h_leadingLeptonEta h_subleadingLeptonEta h_subleadingLeptonPt'

options=$@

run() {
    cd $1
    shift 1
    pwd
    python PlotTool/autoplotter.py $options --nhist $nvariables $@
    python PlotTool/autoplotter.py $options $extraction
    cd ../
}

#run SignalRegion
#run SingleEleCR $singleleps
run SingleMuCR $singleleps
#run DoubleEleCR $doubleleps
#run DoubleMuCR $doubleleps
