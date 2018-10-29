DATE=May2018
DATE_2=29May
DATE_DATA=19May

echo "Do the CR data samples"

./rootcom ZprimeJetsClass2017 analyzedata

./../SubmitCondor.py analyzedata /hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017B/ postSingleMu_0.root -1 10000 Mu_0 split_-1

./../SubmitCondor.py analyzedata /hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017C/ postSingleMu_1.root -1 10000 Mu_1 split_-1

./../SubmitCondor.py analyzedata /hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017D/ postSingleMu_2.root -1 10000 Mu_2 split_-1

./../SubmitCondor.py analyzedata /hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017E/ postSingleMu_3.root -1 10000 Mu_3 split_-1  

./../SubmitCondor.py analyzedata /hdfs/store/user/varuns/NTuples/Data/Run2017_31Mar2018_94X/MET/MET2017F/ postSingleMu_4.root -1 10000 Mu_4 split_-1

echo "Do the MC samples"

./rootcom ZprimeJetsClass2017_MC analyze

#QCD Samples
./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT100-200/0000/ postQCD100to200_0.root -1 10000 QCD100_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT100-200/0001/ postQCD100to200_1.root -1 10000 QCD100_1 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT100-200/0002/ postQCD100to200_2.root -1 10000 QCD100_2 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT100-200/0003/ postQCD100to200_3.root -1 10000 QCD100_3 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT200-300/0000/ postQCD200to300_0.root -1 10000 QCD200_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT200-300/0001/ postQCD200to300_1.root -1 10000 QCD200_1 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT200-300/0002/ postQCD200to300_2.root -1 10000 QCD200_2 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT300-500/0000/ postQCD300to500_0.root -1 10000 QCD300_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT300-500/0001/ postQCD300to500_1.root -1 10000 QCD300_1 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT300-500/0002/ postQCD300to500_2.root -1 10000 QCD300_2 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT300-500/0003/ postQCD300to500_3.root -1 10000 QCD300_3 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT500-700/0000/ postQCD500to700_0.root -1 10000 QCD500_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT500-700/0001/ postQCD500to700_1.root -1 10000 QCD500_1 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT500-700/0002/ postQCD500to700_2.root -1 10000 QCD500_2 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT700-1000/0000/ postQCD700to1000_0.root -1 10000 QCD700_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT700-1000/0001/ postQCD700to1000_1.root -1 10000 QCD700_1 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT700-1000/0002/ postQCD700to1000_2.root -1 10000 QCD700_2 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT1000-1500/ postQCD1000to1500_0.root -1 10000 QCD1000_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT1500-2000/ postQCD1500to2000_0.root -1 10000 QCD1500_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/QCD/QCD_HT2000-Inf/ postQCD2000toInf_0.root -1 10000 QCD2000_0 split_-1

#TTJets

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0000/ postTTJets_MLM_0.root -1 10000 TTJets_MLM_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0001/ postTTJets_MLM_1.root -1 10000 TTJets_MLM_1 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0002/ postTTJets_MLM_2.root -1 10000 TTJets_MLM_2 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0003/ postTTJets_MLM_3.root -1 10000 TTJets_MLM_3 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0004/ postTTJets_MLM_4.root -1 10000 TTJets_MLM_4 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0005/ postTTJets_MLM_5.root -1 10000 TTJets_MLM_5 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0006/ postTTJets_MLM_6.root -1 10000 TTJets_MLM_6 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets/0007/ postTTJets_MLM_7.root -1 10000 TTJets_MLM_7 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/TTJets_DiLept/ postTTJetsDiLept_0.root -1 10000 TTJetsDiLept_0 split_-1

#GJets
./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/GJets/GJets_HT40-100/ postGJets40to100.root -1 10000 GJets40_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/GJets/GJets_HT100-200/ postGJets100to200.root -1 10000 GJets100_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/GJets/GJets_HT200-400/ postGJets200to400.root -1 10000 GJets200_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/GJets/GJets_HT400-600/ postGJets400to600.root -1 10000 GJets400_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/GJets/GJets_HT600-Inf/ postGJets600toInf.root -1 10000 GJets600_0 split_-1

#Diboson
./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/EWK/WW/ postWW.root -1 10000 WW_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/EWK/WWTo2L2Nu/ postWWto2L2Nu.root -1 10000 WWto2L2Nu_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/EWK/WWTo4Q/ postWWto4Q.root -1 10000 WWto4Q_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/EWK/WWToLNuQQ/ postWWtoLNuQQ.root -1 10000 WWtoLNuQQ_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/EWK/WZ/ postWZ.root -1 10000 WZ_0 split_-1

./../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/EWK/ZZ/ postZZ.root -1 10000 ZZ_0 split_-1

#WJets
./rootcom ZprimeJetsClass2017_MC_WJets analyzeWJets

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJetsToLNu_Incl/v1/ postWJets_MLM_0.root -1 10000 W_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJetsToLNu_Incl/v2/0000/ postWJets_MLM_1.root -1 10000 W_1 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJetsToLNu_Incl/v2/0001/ postWJets_MLM_1.root -1 10000 W_1 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJetsToLNu_Incl/v2/0002/ postWJets_MLM_1.root -1 10000 W_1 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT100To200/ postW100to200_0.root -1 10000 W100_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT200To400/ postW200to400_0.root -1 10000 W200_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT400To600/ postW400to600_0.root -1 10000 W400_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT600To800/ postW600to800_0.root -1 10000 W600_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT800To1200/ postW800to1200_0.root -1 10000 W800_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT1200To2500/ postW1200to2500_0.root -1 10000 W1200_0 split_-1

./../SubmitCondor.py analyzeWJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/WJets/WJetsToLNu_HT2500ToInf/ postW2500toInf_0.root -1 10000 W2500_0 split_-1

#ZJets
./rootcom ZprimeJetsClass2017_MC_ZJets analyzeZJets

#DYJets

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_FXFX/v1/ postDY_MLM_0.root -1 10000 DYMLM_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT70To100/ postDY70to100_0.root -1 10000 DY70_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT100To200/ postDY100to200_0.root -1 10000 DY100_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT200To400/ postDY200to400_0.root -1 10000 DY200_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT400To600/ postDY400to600_0.root -1 10000 DY400_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT600To800/ postDY600to800_0.root -1 10000 DY600_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT800To1200/ postDY800to1200_0.root -1 10000 DY800_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT1200To2500/ postDY1200to2500_0.root -1 10000 DY1200_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/DYJets/DYJetsToLL_HT2500ToInf/ postDY2500toInf_0.root -1 10000 DY2500_0 split_-1

#ZJets
./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT100To200/ postZ100to200_0.root -1 10000 Z100_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT200To400/ postZ200to400_0.root -1 10000 Z200_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT400To600/ postZ400to600_0.root -1 10000 Z400_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT600To800/ postZ600to800_0.root -1 10000 Z600_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT800To1200/ postZ800to1200_0.root -1 10000 Z800_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT1200To2500/ postZ1200to2500_0.root -1 10000 Z1200_0 split_-1

./../SubmitCondor.py analyzeZJets /hdfs/store/user/varuns/NTuples/MC/MC2017_12Apr2018_94X/ZJets/ZJetsToNuNu_HT2500ToInf/ postZ2500toInf_0.root -1 10000 Z2500_0 split_-1
