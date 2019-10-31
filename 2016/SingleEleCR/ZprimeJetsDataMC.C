#define ZprimeYear_cxx
#include "ZprimeYear.h"

ZprimeJetsCommon::DataMC::DataMC(string filename) {
  string sampleID[] = {"SingleElectron","MonoZprime_Mx","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};
  string inclusiveID[] = {"WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8","DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"};
  for (int i = 0; i < Total; i++)
    if (filename.find(sampleID[i]) != string::npos) {
      type = static_cast<Type>(i);
    }
  isData = (type == Data);
  isInclusive = false;
  if (type == WJets || type == DYJets)
    for (int i = 0; i < 2; i++)
      if (filename.find(inclusiveID[i]) != string::npos)
	isInclusive = true;
  if (type == WJets) PID = 24;
  if (type == ZJets || type == DYJets) PID = 23;
}
bool ZprimeJetsCommon::DataMC::isW_or_ZJet() { return type == WJets || type == ZJets || type == DYJets; }
