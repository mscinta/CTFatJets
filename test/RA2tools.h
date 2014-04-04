#include <map>
#include <utility>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include "TH1F.h"
#include "TString.h"

using namespace std;

// enumerators for classification
enum JetMult { kLow, // 3<=njets<=5
	       kMed, // 6<=njets<=7
	       kHigh // njets>8
             };

enum HtRegion { k500_800, 
		k800_1000,
		k1000_1250,
		k1250_1500,
		k1500_Inf
              };



enum MetRegion{ k200_300,
		k300_450,
		k450_600,
		k200_Inf,
		k300_Inf,
		k450_Inf,
		k600_Inf
              };

typedef pair < HtRegion , JetMult > doublet;
typedef pair < MetRegion , doublet > triplet;

class RA2tools {

public:

  RA2tools(TString nametag="temp");
  ~RA2tools(){};

  void setBin(MetRegion metReg, HtRegion htReg, JetMult jetBin){
    jetMult_ = jetBin ;
    metRegion_ = metReg ;
    htRegion_ = htReg ;
  };
  void setJetMult(JetMult jetBin){ jetMult_ = jetBin ; };
  void setMetRegion(MetRegion metReg){ metRegion_ = metReg ; };
  void setHtRegion(HtRegion htReg){ htRegion_ = htReg ; };

  void fillHisto(float yield);
  void fillHisto(MetRegion metReg,HtRegion htReg,JetMult jetBin,float yield);

  void readData(TString fileName);
  vector<string> &split(const string &s, vector<string> &elems);
  vector<string> split(const string &s);
  // public data members
  TH1F* yieldHisto;

private:

  char* binNames[36];

  // private data members
  JetMult jetMult_;
  HtRegion htRegion_;
  MetRegion metRegion_;
  
  map < triplet , int > binMap;

  map < string , JetMult   > JetMultNames;
  map < string , HtRegion  > HtRegionNames;
  map < string , MetRegion > MetRegionNames;

};
