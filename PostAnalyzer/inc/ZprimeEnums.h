#ifndef ZprimeEnums_h
#define ZprimeEnums_h

enum Type {Data,Signal,ZJets,ZJets_NLO,WJets,WJets_NLO,DYJets,DYJets_NLO,QCD,TTJets,ST,GJets,EWK,nType};
static const char * TypeName[] = {"Data","Signal","ZJets","ZJets_NLO","WJets","WJets_NLO","DYJets","DYJets_NLO","QCD","TTJets","ST","GJets","EWK"};

enum Region{SR,WE,WM,ZE,ZM,nRegion};
static const char * RegionName[] = {"SignalRegion","SingleElectron","SingleMuon","DoubleElectron","DoubleMuon"};

enum Hadron{Charged=211,Neutral=130,Gamma=22};

#endif
