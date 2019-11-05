RUN="python ${CMSSW_BASE}/src/ZprimeTools2018/CondorTools/SubmitCondor.py -y 2018 -r ZE -f analyze"

. "${CMSSW_BASE}/src/ZprimeTools2018/plugins/data_cfg.sh"

make || exit -1

echo "Do the CR Data samples"

file="DoubleEle"
label="Ele"

# ELE_A "$RUN" $file $label
# ELE_B "$RUN" $file $label
# ELE_C "$RUN" $file $label
ELE_D "$RUN" $file $label
