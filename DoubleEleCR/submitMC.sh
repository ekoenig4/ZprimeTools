1$DATA1=/hdfs/store/user/varuns/Run2018_17Sep2018_May2019
$DATA2=/hdfs/store/user/varuns/Run2018D_Prompt
$MC=/hdfs/store/user/varuns/MC2018_Autumn18_May2019
$RUN='python ../SubmitCondor.py analyze'

make || exit -1

echo 'Do the MC samples'

#QCD

#TTJets

#GJets

#Diboson

#WJets

$RUN $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190515_202255/0000/ postW100to200_0.root -1 10000 W100_0 split_-1
$RUN $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190515_202255/0001/ postW100to200_1.root -1 10000 W100_1 split_-1
$RUN $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190515_202255/0002/ postW100to200_2.root -1 10000 W100_2 split_-1

$RUN $MC/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT200-400/190515_202409/0000/ postW200to400_0.root -1 10000 W200_0 split_-1
$RUN $MC/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT200-400/190515_202409/0001/ postW200to400_1.root -1 10000 W200_1 split_-1
$RUN $MC/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT200-400/190515_202409/0002/ postW200to400_2.root -1 10000 W200_2 split_-1

$RUN $MC/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT400-600/190515_202530/0000/ postW400to600_0.root -1 10000 W400_0 split_-1

$RUN $MC/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190515_202650/0000/ postW600to800_0.root -1 10000 W600_0 split_-1
$RUN $MC/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190515_202650/0001/ postW600to800_1.root -1 10000 W600_1 split_-1
$RUN $MC/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190515_202650/0002/ postW600to800_2.root -1 10000 W600_2 split_-1

$RUN $MC/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT800-1200/190515_202802/0000/ postW800to1200_0.root -1 10000 W800_0 split_-1

$RUN $MC/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT1200-2500/190515_202922/0000/ postW1200to2500_0.root -1 10000 W1200_0 split_-1

$RUN $MC/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT2500-Inf/190515_203039/0000/ postW2500toInf_0.root -1 10000 W2500_0 split_-1

#DYJets

$RUN $MC/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT70-100/190516_074351/0000/ postDY70to100_0.root -1 10000 DY70_0 split_-1
$RUN $MC/DYJetsToLL_M-50_HT-70to100_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT70-100/190516_074351/0001/ postDY70to100_1.root -1 10000 DY70_1 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-100to200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT100-200/190516_074443/0000/ postDY100to200_0.root -1 10000 DY100_0 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT200-400/190516_074532/0000/ postDY200to400_0.root -1 10000 DY200_0 split_-1
$RUN $MC/DYJetsToLL_M-50_HT-200to400_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT200-400/190516_074532/0001/ postDY200to400_1.root -1 10000 DY200_1 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-400to600_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT400-600/190516_074631/0000/ postDY400to600_0.root -1 10000 DY400_0 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-600to800_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT600-800/190516_074725/0000/ postDY600to800_0.root -1 10000 DY600_0 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-800to1200_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT800-1200/190516_074821/0000/ postDY800to1200_0.root -1 10000 DY800_0 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT1200-2500/190516_074911/0000/ postDY1200to2500_0.root -1 10000 DY1200_0 split_-1

$RUN $MC/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_PSweights_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT2500-Inf/190516_075002/0000/ postDY2500toInf_0.root -1 10000 DY2500_0 split_-1

#ZJets

$RUN $MC/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT100-200/190512_100845/0000/ postZ100to200_0.root -1 10000 Z100_0 split_-1
$RUN $MC/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT100-200/190512_100845/0001/ postZ100to200_1.root -1 10000 Z100_1 split_-1
$RUN $MC/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT100-200/190512_100845/0002/ postZ100to200_2.root -1 10000 Z100_2 split_-1

$RUN $MC/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_job_ZJetsToNuNu_HT200-400/190512_101031/0000/ postZ200to400_0.root -1 10000 Z200_0 split_-1
$RUN $MC/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_job_ZJetsToNuNu_HT200-400/190512_101031/0001/ postZ200to400_1.root -1 10000 Z200_1 split_-1
$RUN $MC/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_job_ZJetsToNuNu_HT200-400/190512_101031/0002/ postZ200to400_2.root -1 10000 Z200_2 split_-1

$RUN $MC/ZJetsToNuNu_HT-400To600_13TeV-madgraph/crab_job_ZJetsToNuNu_HT400-600/190512_101112/0000/ postZ400to600_0.root -1 10000 Z400_0 split_-1

$RUN $MC/ZJetsToNuNu_HT-600To800_13TeV-madgraph/crab_job_ZJetsToNuNu_HT600-800/190512_101153/0000/ postZ600to800_0.root -1 10000 Z600_0 split_-1

$RUN $MC/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT800-1200/190512_101234/0000/ postZ800to1200_0.root -1 10000 Z800_0 split_-1

$RUN $MC/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/crab_job_ZJetsToNuNu_HT1200-2500/190512_101319/0000/ postZ1200to2500_0.root -1 10000 Z1200_0 split_-1

$RUN $MC/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/crab_job_ZJetsToNuNu_HT2500-Inf/190512_101359/0000/ postZ2500toInf_0.root -1 10000 Z2500_0 split_-1
