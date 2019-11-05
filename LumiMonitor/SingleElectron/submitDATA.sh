MC=/hdfs/store/user/varuns/MC2017_12Apr2018_May2019
DATA=/hdfs/store/user/varuns/Run2017_31Mar2018_May2019
RUN="python ${CMSSW_BASE}/src/ZprimeTools2018/CondorTools/SubmitCondor.py -y 2018 -r EG -f calcXsec.py"

. "${CMSSW_BASE}/src/ZprimeTools2018/plugins/data_cfg.sh"

make || exit -1

echo "Do the Data samples"

ELE_B "$RUN" SingleEle Ele
ELE_C "$RUN" SingleEle Ele
ELE_D "$RUN" SingleEle Ele
