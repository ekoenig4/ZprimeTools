#!/bin/sh
input="${@}"
arg="${input/_b/_8}"
make -C SignalRegion plot variable="$arg"
arg="${input/_b/_10}"
make -C SingleEleCR plot variable="$arg"
make -C SingleMuCR plot variable="$arg"
make -C DoubleEleCR plot variable="$arg"
make -C DoubleMuCR plot variable="$arg"