RUN="python ${CMSSW_BASE}/src/ZprimeTools2017/CondorTools/SubmitCondor.py -y 2017 -r WE analyze"

. "${CMSSW_BASE}/src/ZprimeTools2017/plugins/mc_cfg.sh"

make || exit -1

echo "Do the MC samples"

WJETS "$RUN"
GJETS "$RUN"
DIBOSON "$RUN"
TTJETS "$RUN"
DYJETS "$RUN"
ZJETS "$RUN"
QCD "$RUN"
