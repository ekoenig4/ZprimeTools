#define ZprimeJetsCommon_cxx
#include "ZprimeJetsCommon.h"

void ZprimeJetsCommon::PSWeights(int nhist,double event_weight) {
  /* 44 Histograms
                   up  dn
     isrRed        0   2
     fsrRed        1   3
     isrDef        4   6
     fsrDef        5   7
     isrCon        8  10 
     fsrCon        9  11
     fsr_G2GG_muR  12 13
     fsr_G2QQ_muR  14 15
     fsr_Q2QG_muR  16 17
     fsr_X2XG_muR  18 19
     fsr_G2GG_cNS  20 21
     fsr_G2QQ_cNS  22 23
     fsr_Q2QG_cNS  24 25
     fsr_X2XG_cNS  26 27 
     isr_G2GG_muR  28 29
     isr_G2QQ_muR  30 31
     isr_Q2QG_muR  32 33
     isr_X2XG_muR  34 35
     isr_G2GG_cNS  36 37
     isr_G2QQ_cNS  38 39
     isr_Q2QG_cNS  40 41
     isr_X2XG_cNS  42 43
  */
  int nPS = 44;
  for (int i = 0; i < nPS; i++) {
    double ps_weight = event_weight;
    if (!sample.isData) ps_weight *= psWeight->at(i+2);
    fillHistos(nhist+i,ps_weight );
  }
}
