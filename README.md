# Mono-Z' Jet + MET analysis

This repository contains pacakges to analyze ntuples for the signal region and the control region 
for the Mono-Z' Jet + MET analysis.
Jobs are submitted to condor through the MakeCondorFiles*.csh scripts.
1) MakeCondorFiles_data.csh for data
2) MakeCondorFiles.csh for MC
3) MakeCondorFiles_WZ.csh for Wlv+Jets and Zvv+Jets MC as EWK+NNLO corrections need to be applied 
using the Monojet recipe via kfactors.root
4) kfactors.root can be found in /nfs_scratch/uhussain/MonoZprimeJet_postanalyzer_jobsubmission/ 

Note: In the Control Region directory, MakeCondorFiles_WZ.csh is also used for the DYJetsToLL 
samples as we apply the same EWK+NNLO corrections to the DYSamples for Control Region Plots.

The submit*.sh scripts can be changed as necessary and are just submitting jobs en masse.

Instructions:


```bash
cmsrel CMSSW_8_0_26_patch1
cd $CMSSW_BASE/src
cmsenv
export VO_CMS_SW_DIR=/cvmfs/cms.cern.ch
voms-proxy-init --voms=cms --valid=192:00
./submit.sh
```

Stitching DY inclusive sample and WJets inclusive sample withe the HT-binned samples. Currently done by hand.

Edit the corresponding ZprimeJetsClass_MC*.C files to add the genHT < 100 cut in the beginning 
and then process the inclusive samples as follows:

Signal Region:


```bUpash
./rootcom ZprimeJetsClass_MC analyze1
./MakeCondorFiles.csh analyze1 /hdfs/store/user/uhussain/Zprime_Ntuples_Aug10/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL/170810_152817/0000/ postDY_MLM_0.root -1 10000 DYMLM_0 PU_Central.root
./rootcom ZprimeJetsClass_MC_WJets analyzeWJets1
./MakeCondorFiles_WZ.csh analyzeWJets1 /hdfs/store/user/uhussain/Zprime_Ntuples_Aug10/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJets/170810_152529/0000/ postWJets_MLM_0.root -1 10000 W_0 kfactors.root PU_Central.root
```

All Signal file can be found in /nfs_scratch/uhussain/MonoZprimeJet_postanalyzer_jobsubmission/  
For instance for the signal file with m_{chi} = 5 GeV, edit ZprimeJetsClass_MC.h #L755 to :
TString dataset = "ggtree_mc_signal5GeV_";
And run the following commands:

```bash
./rootcom ZprimeJetsClass_MC signal
./signal /nfs_scratch/uhussain/MonoZprimeJet_postanalyzer_jobsubmission/ postSignal.root -1 1 > signalTest.txt
```

Control Region:

```bash
./rootcom ZprimeJetsClass_MC_ZJets analyze1
./MakeCondorFiles_WZ.csh analyze1 /hdfs/store/user/uhussain/Zprime_Ntuples_Aug10/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL/170810_152817/0000/ postDY_MLM_0.root -1 10000 DYMLM_0 kfactors.root PU_Central.root
./rootcom ZprimeJetsClass_MC_WJets analyzeWJets1
./MakeCondorFiles_WZ.csh analyzeWJets1 /hdfs/store/user/uhussain/Zprime_Ntuples_Aug10/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJets/170810_152529/0000/ postWJets_MLM_0.root -1 10000 W_0 kfactors.root PU_Central.root
```
After your condor jobs are finished and you have post*.root files, make plots using stackplotter*.C scripts and edit/automate the script to your needs

```bash
root -l stackplotter.C
```

PileupCorrection Recipe adopted from Nick Smith (U.Wisconsin)
Add link here to nick's repo later
Get your "processedLumis.json" from crab --report
```bash
./getDataDistribution.sh
python calculatePileupCorrections.py
```
You will need to edit the calculatePileupCorrections.py file in case you are using a different mc profile than what is included
