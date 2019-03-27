

DATE=May2018
DATE_2=29May
DATE_DATA=19May

make || exit -1

echo "Do the CR data samples"

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/Data/Run2018_17Sep2018_102X/EGamma/EGamma2018A/ postSingleEle_0.root -1 10000 Ele_0 split_-1
 
python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/Data/Run2018_17Sep2018_102X/EGamma/EGamma2018B/ postSingleEle_1.root -1 10000 Ele_1 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/Data/Run2018_17Sep2018_102X/EGamma/EGamma2018C/  postSingleEle_2.root -1 10000 Ele_2 split_-1

echo "Do the MC samples"

#QCD Samples
python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT100-200/ postQCD100to200_0.root -1 10000 QCD100_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT200-300/ postQCD200to300_0.root -1 10000 QCD200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT300-500/ postQCD300to500_0.root -1 10000 QCD300_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT500-700/ postQCD500to700_0.root -1 10000 QCD500_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT700-1000/ postQCD700to1000_0.root -1 10000 QCD700_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT1000-1500/ postQCD1000to1500_0.root -1 10000 QCD1000_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT1500-2000/ postQCD1500to2000_0.root -1 10000 QCD1500_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/QCD/QCD_HT2000-Inf/ postQCD2000toInf_0.root -1 10000 QCD2000_0 split_-1

#TTJets

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/TTJets/TTJets postTTJets_MLM_0.root -1 10000 TTJets_MLM_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/TTJets/TTJets_SingleLeptFromT postTTJetsSingleLept_0.root -1 10000 TTJetsSingleLept_0 split_-1

#GJets
python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/GJets/GJets_HT40-100/ postGJets40to100.root -1 10000 GJets40_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/GJets/GJets_HT100-200/ postGJets100to200.root -1 10000 GJets100_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/GJets/GJets_HT200-400/ postGJets200to400.root -1 10000 GJets200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/GJets/GJets_HT400-600/ postGJets400to600.root -1 10000 GJets400_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/GJets/GJets_HT600-Inf/ postGJets600toInf.root -1 10000 GJets600_0 split_-1

#Diboson
python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/EWK/WW/ postWW.root -1 10000 WW_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/EWK/WWTo2L2Nu/ postWWto2L2Nu.root -1 10000 WWto2L2Nu_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/EWK/WWTo4Q/ postWWto4Q.root -1 10000 WWto4Q_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/EWK/WWToLNuQQ/ postWWtoLNuQQ.root -1 10000 WWtoLNuQQ_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/EWK/WZ/ postWZ.root -1 10000 WZ_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/EWK/ZZ/ postZZ.root -1 10000 ZZ_0 split_-1

#WJets

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJetsToLNu_Incl/v1/ postWJets_MLM_0.root -1 10000 W_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJetsToLNu_Incl/v2/0000/ postWJets_MLM_1.root -1 10000 W_1 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJetsToLNu_Incl/v2/0001/ postWJets_MLM_1.root -1 10000 W_1 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJetsToLNu_Incl/v2/0002/ postWJets_MLM_1.root -1 10000 W_1 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT100-200/ postW100to200_0.root -1 10000 W100_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT200-400/ postW200to400_0.root -1 10000 W200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT400-600/ postW400to600_0.root -1 10000 W400_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT600-800/ postW600to800_0.root -1 10000 W600_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT800-1200/ postW800to1200_0.root -1 10000 W800_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT1200-2500/ postW1200to2500_0.root -1 10000 W1200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/WJets/WJetsToLNu_HT2500-Inf/ postW2500toInf_0.root -1 10000 W2500_0 split_-1

#ZJets

#DYJets

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_Incl/ postDY_MLM_0.root -1 10000 DYMLM_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT70-100/ postDY70to100_0.root -1 10000 DY70_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT100-200/ postDY100to200_0.root -1 10000 DY100_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT200-400/ postDY200to400_0.root -1 10000 DY200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT400-600/ postDY400to600_0.root -1 10000 DY400_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT400-600v2/ postDY400to600_1.root -1 10000 DY400_1 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT600-800/ postDY600to800_0.root -1 10000 DY600_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT800-1200/ postDY800to1200_0.root -1 10000 DY800_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT1200-2500/ postDY1200to2500_0.root -1 10000 DY1200_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/DYJets/DYJetsToLL_HT2500-Inf/ postDY2500toInf_0.root -1 10000 DY2500_0 split_-1

#ZJets
python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT100-200/ postZ100to200_0.root -1 10000 Z100_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT200-400/ postZ200to400_0.root -1 10000 Z200_0 split_-1

# python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT400-600/ postZ400to600_0.root -1 10000 Z400_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT600-800/ postZ600to800_0.root -1 10000 Z600_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT800-1200/ postZ800to1200_0.root -1 10000 Z800_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT1200-2500/ postZ1200to2500_0.root -1 10000 Z1200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/varuns/NTuples/MC/MC2018_RunIIAutumn18_102X/ZJets/ZJetsToNuNu_HT2500-Inf/ postZ2500toInf_0.root -1 10000 Z2500_0 split_-1
