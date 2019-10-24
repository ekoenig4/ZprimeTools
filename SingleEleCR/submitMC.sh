RUN="python ${CMSSW_BASE}/src/ZprimeTools2016/CondorTools/SubmitCondor.py -y 2016 -r WE analyze"

. "${CMSSW_BASE}/src/ZprimeTools2016/plugins/mc_cfg.sh"

make || exit -1

echo "Do the MC samples"

WJETS "$RUN"
GJETS "$RUN"
DIBOSON "$RUN"
TTJETS "$RUN"
DYJETS "$RUN"
ZJETS "$RUN"
QCD "$RUN"
