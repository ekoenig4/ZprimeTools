#define ZprimeYear_cxx
#include "ZprimeYear.h"

using namespace std;

#ifdef ZprimeYear_cxx
vector<string> ZprimeYear::split(string str,string delim) {
  vector<string> splitString;
  char strChar[str.size() + 1];
  strcpy(strChar,str.c_str());
  char *token = strtok(strChar,delim.c_str());
  while (token != NULL) {
    splitString.push_back(string(token));
    token = strtok(NULL,delim.c_str());
  }
  return splitString;
}

bool ZprimeYear::fileSelection(string filename,string fileRange)
{
  if (fileRange == "-1") return true;
  int numPos;
  for (int i = filename.size(); i > 0; --i) {
    if (filename[i] == '_') {
      numPos = i+1;
      break;
    }
  }
  filename.erase(filename.begin(),filename.begin()+numPos);
  int fileNum = atoi(filename.c_str());
  //1-100/200-250/300-300
  vector<string> rangeOfFiles = split(fileRange,"/");
  for (int i = 0; i < rangeOfFiles.size(); i++) {
    vector<string> range = split(rangeOfFiles[i],"-");
    if (atoi(range[0].c_str()) <= fileNum && fileNum <= atoi(range[1].c_str())) {
      return true;
    }
  }
  return false;
}

ZprimeYear::ZprimeYear(const char* inputFilename,const char* outputFilename,const char* fileRange) 
{
  output = outputFilename;
  TChain *chain = new TChain("phoJetNtuplizer/eventTree");
  TString path = inputFilename;
  TSystemDirectory sourceDir("hi",path);
  TList* fileList = sourceDir.GetListOfFiles();
  TIter nextlist(fileList);
  TSystemFile* filename;
  int fileNumber = 0;
  int maxFiles = -1;
  int inFile=0;
  while ((filename = (TSystemFile*)nextlist()))
    {
      //Debug
      if (debug) {
	cout<<"file path found: "<<(path+filename->GetName())<<endl;
	cout<<"name: "<<(filename->GetName())<<endl;
	cout<<"fileNumber: "<<fileNumber<<endl;
      }

      TString dataset = ".root";
      TString  FullPathInputFile = (path+filename->GetName());
      TString name = filename->GetName();
      if (name.Contains(dataset))
	{
	  string fname = string(name);
	  fname.erase(fname.end()-5,fname.end());
	  bool isin = fileSelection(fname,string(fileRange));
	  if(isin)
	    {
	      if (debug)
		cout<<"Adding FullPathInputFile to chain:"<<FullPathInputFile<<endl<<endl;
	      chain->Add(FullPathInputFile);
	      inFile++;
	    }
	}
      fileNumber++;
    }
  cout<<inFile<<" files added."<<endl;
  cout<<"Initializing chain."<<endl;
  Init(chain);
}

ZprimeYear::~ZprimeYear()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t ZprimeYear::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t ZprimeYear::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void ZprimeYear::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("run", &run, &b_run);
  fChain->SetBranchAddress("event", &event, &b_event);
  fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
  fChain->SetBranchAddress("isData", &isData, &b_isData);
  
  Notify();
}

Bool_t ZprimeYear::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void ZprimeYear::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t ZprimeYear::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef ZprimeYear_cxx

