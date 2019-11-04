RUN="python ${CMSSW_BASE}/src/ZprimeTools2017/CondorTools/SubmitCondor.py -y 2017 -r ZE -f analyze"

. "${CMSSW_BASE}/src/ZprimeTools2017/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="DoubleEle"
label="Ele"

ELE_A "$RUN" $file $label
ELE_C "$RUN" $file $label
ELE_D "$RUN" $file $label
ELE_E "$RUN" $file $label
ELE_F "$RUN" $file $label
