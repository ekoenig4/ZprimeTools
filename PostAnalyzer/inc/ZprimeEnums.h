#ifndef ZprimeEnums_h
#define ZprimeEnums_h

enum Type {Data,Signal,WJets,ZJets,DYJets,QCD,TTJets,GJets,WW,WZ,ZZ,nType};
static const char * TypeName[] = {"Data","Signal","WJets","ZJets","DYJets","QCD","TTJets","GJets","WW","WZ","ZZ"};

enum Region{SR,WE,WM,ZE,ZM,nRegion};
static const char * RegionName[] = {"SignalRegion","SingleElectron","SingleMuon","DoubleElectron","DoubleMuon"};

enum Hadron{Charged=211,Neutral=130,Gamma=22};

#endif
