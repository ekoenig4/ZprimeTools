DATE=May2018
DATE_2=29May

make || exit -1

echo "Do the CR data samples"

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset1/180529_*/0000/ postDoubleMu_0.root -1 10000 Mu_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset1/180529_*/0001/ postDoubleMu_1.root -1 10000 Mu_1 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset1/180529_*/0002/ postDoubleMu_2.root -1 10000 Mu_2 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset1/180529_*/0003/ postDoubleMu_3.root -1 10000 Mu_3 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset2/180529_*/0000/ postDoubleMu_4.root -1 10000 Mu_4 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset2/180529_*/0001/ postDoubleMu_5.root -1 10000 Mu_5 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset3/180529_*/0000/ postDoubleMu_6.root -1 10000 Mu_6 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset3/180529_*/0001/ postDoubleMu_7.root -1 10000 Mu_7 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset4/180529_*/0000/ postDoubleMu_8.root -1 10000 Mu_8 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset4/180529_*/0001/ postDoubleMu_9.root -1 10000 Mu_9 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset5/180529_*/0000/ postDoubleMu_10.root -1 10000 Mu_10 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset5/180529_*/0001/ postDoubleMu_11.root -1 10000 Mu_11 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset6/180529_*/0000/ postDoubleMu_12.root -1 10000 Mu_12 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset6/180529_*/0001/ postDoubleMu_13.root -1 10000 Mu_13 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset6/180529_*/0002/ postDoubleMu_14.root -1 10000 Mu_14 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset7/180529_*/0000/ postDoubleMu_15.root -1 10000 Mu_15  split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset7/180529_*/0001/ postDoubleMu_16.root -1 10000 Mu_16  split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset7/180529_*/0002/ postDoubleMu_17.root -1 10000 Mu_17  split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset7/180529_*/0003/ postDoubleMu_18.root -1 10000 Mu_18  split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/gomber/MonoZprime_Ntuples_29May_SR/MET/crab_dataset8/180529_*/0000/ postDoubleMu_19.root -1 10000 Mu_19 split_-1

echo "Do the MC samples"

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT100to200/180528_*/0000/ postQCD100to200_0.root -1 10000 QCD100_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT200to300/180528_*/0000/ postQCD200to300_0.root -1 10000 QCD200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT300to500/180528_*/0000/ postQCD300to500_0.root -1 10000 QCD300_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT500to700/180528_*/0000/ postQCD500to700_0.root -1 10000 QCD500_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT700to1000/180528_*/0000/ postQCD700to1000_0.root -1 10000 QCD700_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1000to1500/180528_*/0000/ postQCD1000to1500_0.root -1 10000 QCD1000_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT1500to2000/180528_*/0000/ postQCD1500to2000_0.root -1 10000 QCD1500_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_QCD_HT2000toInf/180528_*/0000/ postQCD2000toInf_0.root -1 10000 QCD2000_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/TTJets_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_TTJets/180528_*/0000/ postTTJets_MLM.root -1 10000 TTJets_MLM split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/GJets_DR-0p4_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-40To100/180528_*/0000/ postGJets40to100.root -1 10000 GJets40_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/GJets_DR-0p4_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-100To200/180528_*/0000/ postGJets100to200.root -1 10000 GJets100_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/GJets_DR-0p4_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-200To400/180528_*/0000/ postGJets200to400.root -1 10000 GJets200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/GJets_DR-0p4_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-400To600/180528_*/0000/ postGJets400to600.root -1 10000 GJets400_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/GJets_DR-0p4_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_GJets_HT-600ToInf/180528_*/0000/ postGJets600toInf.root -1 10000 GJets600_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WW_TuneCUETP8M1_13TeV-pythia8/crab_WW/180528_*/0000/ postWW.root -1 10000 WW split_-1 

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WZ_TuneCUETP8M1_13TeV-pythia8/crab_WZ/180528_*/0000/ postWZ.root -1 10000 WZ split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZZ_TuneCUETP8M1_13TeV-pythia8/crab_ZZ/180528_*/0000/ postZZ.root -1 10000 ZZ split_-1


#WJets

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_WJets/180528_*/0000/ postWJets_MLM_0.root -1 10000 W_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W1Jets/180528_*/0000/ postW100to200_0.root -1 10000 W100_0 split_-1 
                                                                                                                                                                                                                  
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W2Jets/180528_*/0000/ postW200to400_0.root -1 10000 W200_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W3Jets/180528_*/0000/ postW400to600_0.root -1 10000 W400_0 split_-1
                                                                                                                                                                                                                   
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W4Jets/180528_*/0000/ postW600to800_0.root -1 10000 W600_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W5Jets/180528_*/0000/ postW800to1200_0.root -1 10000 W800_0 split_-1
                                                                                                                                                                                                                      
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W6Jets/180528_*/0000/ postW1200to2500_0.root -1 10000 W1200_0 split_-1
                                                                                                                                                                                                                      
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_W7Jets/180528_*/0000/ postW2500toInf_0.root -1 10000 W2500_0 split_-1

#ZJets

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJetsToLL/180528_*/0000/ postDY_MLM_0.root -1 10000 DYMLM_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT100to200/180528_*/0000/ postDY100to200.root -1 10000 DY100 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT200to400/180528_*/0000/ postDY200to400.root -1 10000 DY200 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT400to600/180528_*/0000/ postDY400to600.root -1 10000 DY400 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT600to800/180528_*/0000/ postDY600to800.root -1 10000 DY600 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT800to1200/180528_*/0000/ postDY800to1200.root -1 10000 DY800 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT1200to2500/180528_*/0000/ postDY1200to2500.root -1 10000 DY1200 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_DYJets_HT2500toInf/180528_*/0000/ postDY2500toInf.root -1 10000 DY2500 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-2500ToInf_13TeV-madgraph/crab_Zvv2500toInf/180528_*/0000/ postZ2500toInf_0.root -1 10000 Z2500_0 split_-1  

       
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-1200To2500_13TeV-madgraph/crab_Zvv1200to2500/180528_*/0000/ postZ1200to2500_0.root -1 10000 Z1200_0 split_-1
                                                                                                                                                                                                      
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-800To1200_13TeV-madgraph/crab_Zvv800to1200/180528_*/0000/ postZ800to1200_0.root -1 10000 Z800_0 split_-1

python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-600To800_13TeV-madgraph/crab_Zvv600to800/180528_*/0000/ postZ600to800_0.root -1 10000 Z600_0 split_-1
                                                                                                                                                                                                
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-400To600_13TeV-madgraph/crab_Zvv400to600/180528_*/0000/ postZ400to600_0.root -1 10000 Z400_0 split_-1
                                                                                                                                                                                                
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-200To400_13TeV-madgraph/crab_Zvv200to400/180528_*/0000/ postZ200to400_0.root -1 10000 Z200_0 split_-1
                                                                                                                                                                                                
python ../SubmitCondor.py analyze /hdfs/store/user/uhussain/Zprime_Ntuples_${DATE}/ZJetsToNuNu_HT-100To200_13TeV-madgraph/crab_Zvv100to200/180528_*/0000/ postZ100to200_0.root -1 10000 Z100_0 split_-1
