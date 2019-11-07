MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019

# QCD
QCD() {
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0000/ postQCD100to200_0.root -1 10000 QCD100_0 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0001/ postQCD100to200_1.root -1 10000 QCD100_1 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0002/ postQCD100to200_2.root -1 10000 QCD100_2 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0003/ postQCD100to200_3.root -1 10000 QCD100_3 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0004/ postQCD100to200_4.root -1 10000 QCD100_4 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0005/ postQCD100to200_5.root -1 10000 QCD100_5 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0006/ postQCD100to200_6.root -1 10000 QCD100_6 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0007/ postQCD100to200_7.root -1 10000 QCD100_7 split_-1
    ${1} $MC/QCD_HT100to200_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT100-200/190511_222431/0008/ postQCD100to200_8.root -1 10000 QCD100_8 split_-1

    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0000/ postQCD200to300_0.root -1 10000 QCD200_0 split_-1
    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0001/ postQCD200to300_1.root -1 10000 QCD200_1 split_-1
    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0002/ postQCD200to300_2.root -1 10000 QCD200_2 split_-1
    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0003/ postQCD200to300_3.root -1 10000 QCD200_3 split_-1
    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0004/ postQCD200to300_4.root -1 10000 QCD200_4 split_-1
    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0005/ postQCD200to300_5.root -1 10000 QCD200_5 split_-1
    ${1} $MC/QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT200-300/190511_012101/0006/ postQCD200to300_6.root -1 10000 QCD200_6 split_-1

    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0000/ postQCD300to500_0.root -1 10000 QCD300_0 split_-1
    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0001/ postQCD300to500_1.root -1 10000 QCD300_1 split_-1
    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0002/ postQCD300to500_2.root -1 10000 QCD300_2 split_-1
    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0003/ postQCD300to500_3.root -1 10000 QCD300_3 split_-1
    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0004/ postQCD300to500_4.root -1 10000 QCD300_4 split_-1
    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0005/ postQCD300to500_5.root -1 10000 QCD300_5 split_-1
    ${1} $MC/QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT300-500/190511_012253/0006/ postQCD300to500_6.root -1 10000 QCD300_6 split_-1

    ${1} $MC/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT500-700/190511_012443/0000/ postQCD500to700_0.root -1 10000 QCD500_0 split_-1
    ${1} $MC/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT500-700/190511_012443/0001/ postQCD500to700_1.root -1 10000 QCD500_1 split_-1
    ${1} $MC/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT500-700/190511_012443/0002/ postQCD500to700_2.root -1 10000 QCD500_2 split_-1
    ${1} $MC/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT500-700/190511_012443/0003/ postQCD500to700_3.root -1 10000 QCD500_3 split_-1
    ${1} $MC/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT500-700/190511_012443/0004/ postQCD500to700_4.root -1 10000 QCD500_4 split_-1
    ${1} $MC/QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT500-700/190511_012443/0005/ postQCD500to700_5.root -1 10000 QCD500_5 split_-1

    ${1} $MC/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT700-1000/190511_012634/0000/ postQCD700to1000_0.root -1 10000 QCD700_0 split_-1
    ${1} $MC/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT700-1000/190511_012634/0001/ postQCD700to1000_1.root -1 10000 QCD700_1 split_-1
    ${1} $MC/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT700-1000/190511_012634/0002/ postQCD700to1000_2.root -1 10000 QCD700_2 split_-1
    ${1} $MC/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT700-1000/190511_012634/0003/ postQCD700to1000_3.root -1 10000 QCD700_3 split_-1
    ${1} $MC/QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT700-1000/190511_012634/0004/ postQCD700to1000_4.root -1 10000 QCD700_4 split_-1

    ${1} $MC/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT1000-1500/190511_012823/0000/ postQCD1000to1500_0.root -1 10000 QCD1000_0 split_-1
    ${1} $MC/QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT1000-1500/190511_012823/0001/ postQCD1000to1500_1.root -1 10000 QCD1000_1 split_-1

    ${1} $MC/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT1500-2000/190511_013012/0000/ postQCD1500to2000_0.root -1 10000 QCD1500_0 split_-1
    ${1} $MC/QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT1500-2000/190511_013012/0001/ postQCD1500to2000_1.root -1 10000 QCD1500_1 split_-1

    ${1} $MC/QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8/crab_job_QCD_HT2000-Inf/190511_013203/0000/ postQCD2000toInf_0.root -1 10000 QCD2000_0 split_-1
}
#TTJets
TTJETS() {
    ${1} $MC/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_TTJets_DiLept/190516_073250/0000/ postTTJetsDiLept_0.root -1 10000 TTJetsDiLept_0 split_-1
    ${1} $MC/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_TTJets_DiLept/190516_073250/0001/ postTTJetsDiLept_1.root -1 10000 TTJetsDiLept_1 split_-1
    ${1} $MC/TTJets_DiLept_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_TTJets_DiLept/190516_073250/0002/ postTTJetsDiLept_2.root -1 10000 TTJetsDiLept_2 split_-1
}
#GJets
GJETS() {
    ${1} $MC/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT40-100/190509_235208/0000/ postGJets40to100.root -1 10000 GJets40_0 split_-1

    ${1} $MC/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT100-200/190515_214007/0000/ postGJets100to200_0.root -1 10000 GJets100_0 split_-1
    ${1} $MC/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT100-200/190515_214007/0001/ postGJets100to200_1.root -1 10000 GJets100_0 split_-1

    ${1} $MC/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT200-400/190509_235511/0000/ postGJets200to400_0.root -1 10000 GJets200_0 split_-1
    ${1} $MC/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT200-400/190509_235511/0001/ postGJets200to400_1.root -1 10000 GJets200_1 split_-1

    ${1} $MC/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT400-600/190515_214055/0000/ postGJets400to600.root -1 10000 GJets400_0 split_-1

    ${1} $MC/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_GJets_HT600-Inf/190509_235640/0000/ postGJets600toInf.root -1 10000 GJets600_0 split_-1
}
# DiBoson
DIBOSON() {
    ${1} $MC/WW_TuneCP5_13TeV-pythia8/crab_job_WW/190510_083150/0000/ postWW.root -1 10000 WW_0 split_-1

    ${1} $MC/WWTo2L2Nu_NNPDF31_TuneCP5_13TeV-powheg-pythia8/crab_job_WWTo2L2Nu/190510_083430/0000/ postWWto2L2Nu.root -1 10000 WWto2L2Nu_0 split_-1

    ${1} $MC/WWTo4Q_NNPDF31_TuneCP5_13TeV-powheg-pythia8/crab_job_WWTo4Q/190510_083547/0000/ postWWto4Q.root -1 10000 WWto4Q_0 split_-1

    ${1} $MC/WWToLNuQQ_NNPDF31_TuneCP5_13TeV-powheg-pythia8/crab_job_WWToLNuQQ/190510_083305/0000/ postWWtoLNuQQ.root -1 10000 WWtoLNuQQ_0 split_-1

    ${1} $MC/WZ_TuneCP5_13TeV-pythia8/crab_job_WZ/190515_214239/0000/ postWZ.root -1 10000 WZ_0 split_-1

    ${1} $MC/ZZ_TuneCP5_13TeV-pythia8/crab_job_ZZ/190515_214324/0000/ postZZ.root -1 10000 ZZ_0 split_-1
}
# WJets
WJETS() {
    ${1} $MC/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_Incl/190516_073431/0000/ postWMLM_0.root -1 10000 WMLM_0 split_-1
    ${1} $MC/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_Incl/190516_073431/0001/ postWMLM_1.root -1 10000 WMLM_1 split_-1
    ${1} $MC/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_Incl/190516_073431/0002/ postWMLM_2.root -1 10000 WMLM_2 split_-1
    ${1} $MC/WJetsToLNu_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_Incl/190516_073431/0003/ postWMLM_3.root -1 10000 WMLM_3 split_-1

    ${1} $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190512_155025/0000/ postW100to200_0.root -1 10000 W100_0 split_-1
    ${1} $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190512_155025/0001/ postW100to200_1.root -1 10000 W100_1 split_-1
    ${1} $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190512_155025/0002/ postW100to200_2.root -1 10000 W100_2 split_-1
    ${1} $MC/WJetsToLNu_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT100-200/190512_155025/0003/ postW100to200_3.root -1 10000 W100_3 split_-1

    ${1} $MC/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT200-400/190509_125712/0000/ postW200to400_0.root -1 10000 W200_0 split_-1
    ${1} $MC/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT200-400/190509_125712/0001/ postW200to400_1.root -1 10000 W200_2 split_-1
    ${1} $MC/WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT200-400/190509_125712/0002/ postW200to400_1.root -1 10000 W200_2 split_-1

    ${1} $MC/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT400-600/190512_160645/0000/ postW400to600_0.root -1 10000 W400_0 split_-1
    ${1} $MC/WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT400-600/190512_160645/0001/ postW400to600_1.root -1 10000 W400_1 split_-1

    ${1} $MC/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190512_161613/0000/ postW600to800_0.root -1 10000 W600_0 split_-1
    ${1} $MC/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190512_161613/0001/ postW600to800_1.root -1 10000 W600_1 split_-1 
    ${1} $MC/WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT600-800/190512_161613/0002/ postW600to800_2.root -1 10000 W600_2 split_-1

    ${1} $MC/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT800-1200/190512_161837/0000/ postW800to1200_0.root -1 10000 W800_0 split_-1
    ${1} $MC/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT800-1200/190512_161837/0001/ postW800to1200_1.root -1 10000 W800_1 split_-1
    ${1} $MC/WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT800-1200/190512_161837/0002/ postW800to1200_2.root -1 10000 W800_2 split_-1

    ${1} $MC/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT1200-2500/190512_162105/0000/ postW1200to2500_0.root -1 10000 W1200_0 split_-1
    ${1} $MC/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT1200-2500/190512_162105/0001/ postW1200to2500_1.root -1 10000 W1200_1 split_-1
    ${1} $MC/WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT1200-2500/190512_162105/0002/ postW1200to2500_2.root -1 10000 W1200_2 split_-1

    ${1} $MC/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT2500-Inf/190512_162333/0000/ postW2500toInf_0.root -1 10000 W2500_0 split_-1
    ${1} $MC/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT2500-Inf/190512_162333/0001/ postW2500toInf_1.root -1 10000 W2500_1 split_-1
    ${1} $MC/WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_WJetsToLNu_HT2500-Inf/190512_162333/0002/ postW2500toInf_2.root -1 10000 W2500_2 split_-1
}
#DYJets
DYJETS() {
    ${1} $MC/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT70-100/190509_151727/0000/ postDY70to100_0.root -1 10000 DY70_0 split_-1
    ${1} $MC/DYJetsToLL_M-50_HT-70to100_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT70-100/190509_151727/0001/ postDY70to100_1.root -1 10000 DY70_1 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT100-200/190509_151851/0000/ postDY100to200_0.root -1 10000 DY100_0 split_-1
    ${1} $MC/DYJetsToLL_M-50_HT-100to200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT100-200/190509_151851/0001/ postDY100to200_1.root -1 10000 DY100_1 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT200-400/190509_152018/0000/ postDY200to400_0.root -1 10000 DY200_0 split_-1
    ${1} $MC/DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT200-400/190509_152018/0001/ postDY200to400_1.root -1 10000 DY200_1 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT400-600/190509_152151/0000/ postDY400to600_0.root -1 10000 DY400_0 split_-1
    ${1} $MC/DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT400-600/190509_152151/0001/ postDY400to600_1.root -1 10000 DY400_1 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT600-800/190509_152313/0000/ postDY600to800_0.root -1 10000 DY600_0 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT800-1200/190509_152436/0000/ postDY800to1200_0.root -1 10000 DY800_0 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT1200-2500/190509_152602/0000/ postDY1200to2500_0.root -1 10000 DY1200_0 split_-1

    ${1} $MC/DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8/crab_job_DYJetsToLL_HT2500-Inf/190509_152739/0000/ postDY2500toInf_0.root -1 10000 DY2500_0 split_-1
}
#ZJets
ZJETS() {
    ${1} $MC/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT100-200/190508_233150/0000/ postZ100to200_0.root -1 10000 Z100_0 split_-1
    ${1} $MC/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT100-200/190508_233150/0001/ postZ100to200_1.root -1 10000 Z100_1 split_-1
    ${1} $MC/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT100-200/190508_233150/0002/ postZ100to200_2.root -1 10000 Z100_2 split_-1

    ${1} $MC/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_job_ZJetsToNuNu_HT200-400/190508_233234/0000/ postZ200to400_0.root -1 10000 Z200_0 split_-1
    ${1} $MC/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_job_ZJetsToNuNu_HT200-400/190508_233234/0001/ postZ200to400_1.root -1 10000 Z200_1 split_-1
    ${1} $MC/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_job_ZJetsToNuNu_HT200-400/190508_233234/0002/ postZ200to400_2.root -1 10000 Z200_2 split_-1

    ${1} $MC/ZJetsToNuNu_HT-400To600_13TeV-madgraph/crab_job_ZJetsToNuNu_HT400-600/190508_233318/0000/ postZ400to600_0.root -1 10000 Z400_0 split_-1

    ${1} $MC/ZJetsToNuNu_HT-600To800_13TeV-madgraph/crab_job_ZJetsToNuNu_HT600-800/190508_233402/0000/ postZ600to800_0.root -1 10000 Z600_0 split_-1

    ${1} $MC/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/crab_job_ZJetsToNuNu_HT800-1200/190508_233447/0000/ postZ800to1200_0.root -1 10000 Z800_0 split_-1

    ${1} $MC/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/crab_job_ZJetsToNuNu_HT1200-2500/190508_233536/0000/ postZ1200to2500_0.root -1 10000 Z1200_0 split_-1

    ${1} $MC/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/crab_job_ZJetsToNuNu_HT2500-Inf/190508_233623/0000/ postZ2500toInf_0.root -1 10000 Z2500_0 split_-1
}
