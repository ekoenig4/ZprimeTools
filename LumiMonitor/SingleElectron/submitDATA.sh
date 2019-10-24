MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN='python SubmitCondor.py calcXsec.py '

. "${CMSSW_BASE}/src/ZprimeTools2018/plugins/data_cfg.sh"

make || exit -1

echo "Do the Data samples"

ELE_B "$RUN" SingleEle Ele
# $RUN /hdfs/store/user/varuns/Egamma2018D-run_102X_data2018_farmout/ postSingleElectron_3.root -1 10000 SingleEle_3 split_-1
