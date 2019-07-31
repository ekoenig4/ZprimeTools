RUN="python ${CMSSW_BASE}/src/ZprimeTools2016/SubmitCondor.py analyze"

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
