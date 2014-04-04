#include "RA2tools.h"

RA2tools::RA2tools(TString nameTag){

  // bin names
  // ---------
  binNames[0]="met: 200-300";
  binNames[1]="met: 300-450";
  binNames[2]="met: 450-600";
  binNames[3]="met: >600"; 
  binNames[4]="met: 200-300";
  binNames[5]="met: 300-450";
  binNames[6]="met: 450-600";
  binNames[7]="met: >600";
  binNames[8]="met: 200-300";
  binNames[9]="met: 300-450";
  binNames[10]="met: 450-600";
  binNames[11]="met: >600";
  binNames[12]="met: 200-300";
  binNames[13]="met: 300-450";
  binNames[14]="met: >450";
  binNames[15]="met: 200-300";
  binNames[16]="met: >300";
  binNames[17]="met: 200-300";
  binNames[18]="met: 300-450";
  binNames[19]="met: >450";
  binNames[20]="met: 200-300";
  binNames[21]="met: 300-450";
  binNames[22]="met: >450";
  binNames[23]="met: 200-300";
  binNames[24]="met: 300-450";
  binNames[25]="met: >450";
  binNames[26]="met: 200-300";
  binNames[27]="met: 300-450";
  binNames[28]="met: >450";
  binNames[29]="met: 200-300";
  binNames[30]="met: >300";
  binNames[31]="met: >200";
  binNames[32]="met: >200";
  binNames[33]="met: >200";
  binNames[34]="met: >200";
  binNames[35]="met: >200";
  // ---------

  // map for enumerator names
  // ========================
  MetRegionNames["k200_300"] = k200_300;
  MetRegionNames["k300_450"] = k300_450;
  MetRegionNames["k450_600"] = k450_600;
  MetRegionNames["k200_Inf"] = k200_Inf;
  MetRegionNames["k300_Inf"] = k300_Inf;
  MetRegionNames["k450_Inf"] = k450_Inf;
  MetRegionNames["k600_Inf"] = k600_Inf;

  HtRegionNames["k500_800"  ] = k500_800  ;
  HtRegionNames["k800_1000" ] = k800_1000 ;
  HtRegionNames["k1000_1250"] = k1000_1250;
  HtRegionNames["k1250_1500"] = k1250_1500;
  HtRegionNames["k1500_Inf" ] = k1500_Inf ;

  JetMultNames["kLow" ] = kLow;
  JetMultNames["kMed" ] = kMed;
  JetMultNames["kHigh"] = kHigh;
  // ========================

  // lowest jet multiplicity, 3-5
  // Ht: 500-800
  binMap[triplet( k200_300 , doublet( k500_800 , kLow ) )] = 1; 
  binMap[triplet( k300_450 , doublet( k500_800 , kLow ) )] = 2; 
  binMap[triplet( k450_600 , doublet( k500_800 , kLow ) )] = 3; 
  binMap[triplet( k600_Inf , doublet( k500_800 , kLow ) )] = 4; 
  
  // lowest jet multiplicity, 3-5
  // Ht: 800-1000
  binMap[triplet( k200_300 , doublet( k800_1000 , kLow ) )] = 5;
  binMap[triplet( k300_450 , doublet( k800_1000 , kLow ) )] = 6;
  binMap[triplet( k450_600 , doublet( k800_1000 , kLow ) )] = 7;
  binMap[triplet( k600_Inf , doublet( k800_1000 , kLow ) )] = 8;

  // lowest jet multiplicity, 3-5
  // Ht: 1000-1250
  binMap[triplet( k200_300 , doublet( k1000_1250 , kLow ) )] = 9;
  binMap[triplet( k300_450 , doublet( k1000_1250 , kLow ) )] = 10;
  binMap[triplet( k450_600 , doublet( k1000_1250 , kLow ) )] = 11;
  binMap[triplet( k600_Inf , doublet( k1000_1250 , kLow ) )] = 12;

  // lowest jet multiplicity, 3-5
  // Ht: 1250-1500
  binMap[triplet( k200_300 , doublet( k1250_1500 , kLow ) )] = 13;
  binMap[triplet( k300_450 , doublet( k1250_1500 , kLow ) )] = 14;
  binMap[triplet( k450_Inf , doublet( k1250_1500 , kLow ) )] = 15;

  // lowest jet multiplicity, 3-5
  // Ht: 1500-inf
  binMap[triplet( k200_300 , doublet( k1500_Inf , kLow ) )] = 16;
  binMap[triplet( k300_Inf , doublet( k1500_Inf , kLow ) )] = 17;

  // lowest jet multiplicity, 6-7
  // Ht: 500-800
  binMap[triplet( k200_300 , doublet( k500_800 , kMed ) )] =18;
  binMap[triplet( k300_450 , doublet( k500_800 , kMed ) )] =19;
  binMap[triplet( k450_Inf , doublet( k500_800 , kMed ) )] =20;

  // lowest jet multiplicity, 6-7
  // Ht: 800-1000
  binMap[triplet( k200_300 , doublet( k800_1000 , kMed ) )] = 21;
  binMap[triplet( k300_450 , doublet( k800_1000 , kMed ) )] = 22;
  binMap[triplet( k450_Inf , doublet( k800_1000 , kMed ) )] = 23;

  // lowest jet multiplicity, 6-7
  // Ht: 1000-1250
  binMap[triplet( k200_300 , doublet( k1000_1250 , kMed ) )] = 24;
  binMap[triplet( k300_450 , doublet( k1000_1250 , kMed ) )] = 25;
  binMap[triplet( k450_Inf , doublet( k1000_1250 , kMed ) )] = 26;

  // lowest jet multiplicity, 6-7
  // Ht: 1250-1500
  binMap[triplet( k200_300 , doublet( k1250_1500 , kMed ) )] = 27;
  binMap[triplet( k300_450 , doublet( k1250_1500 , kMed ) )] = 28;
  binMap[triplet( k450_Inf , doublet( k1250_1500 , kMed ) )] = 29;

  // lowest jet multiplicity, 6-7
  // Ht: 1500-inf
  binMap[triplet( k200_300 , doublet( k1500_Inf , kMed ) )] = 30;
  binMap[triplet( k300_Inf , doublet( k1500_Inf , kMed ) )] = 31;

  // lowest jet multiplicity, >=8
  // Ht: 500-800
  binMap[triplet( k200_Inf, doublet( k500_800    , kHigh ) )] = 32;

  // lowest jet multiplicity, >=8
  // Ht: 800-1000
  binMap[triplet( k200_Inf, doublet( k800_1000   , kHigh ) )] = 33;

  // lowest jet multiplicity, >=8
  // Ht: 1000-1250
  binMap[triplet( k200_Inf, doublet( k1000_1250  , kHigh ) )] = 34;

  // lowest jet multiplicity, >=8
  // Ht: 1250-1500
  binMap[triplet( k200_Inf, doublet( k1250_1500  , kHigh ) )] = 35;

  // lowest jet multiplicity, >=8
  // Ht: 1500-inf
  binMap[triplet( k200_Inf, doublet( k1500_Inf   , kHigh ) )] = 36;

  // build histogram 
  yieldHisto = new TH1F("yieldHisto_"+nameTag,"yieldHisto_"+nameTag,36,1,36);

}

void RA2tools::fillHisto(float yield){ 

  int bin = binMap[ triplet( metRegion_ , doublet( htRegion_  , jetMult_) ) ];
  //cout << "bin: " << bin << endl;
  yieldHisto->Fill( binNames[bin-1] , yield );

}

void RA2tools::fillHisto(MetRegion metReg,HtRegion htReg,JetMult jetBin,float yield){
  
  int bin = binMap[ triplet( metReg , doublet( htReg  , jetBin ) ) ];
  //cout << "bin: " << bin << endl;
  yieldHisto->Fill( binNames[bin-1] , yield );  

  

}

void RA2tools::readData(TString fileName){

  // retrieve file lines
  // ...................
  ifstream dataFile;
  dataFile.open( fileName.Data() );

  vector<string> lines;
  string line;

  if (dataFile.is_open())
    {
      while ( getline (dataFile,line) )
	{

	  lines.push_back(line);

	}
      dataFile.close();
    }

  else cout << "ERROR: Unable to open file" << endl; 
  // ..................

  for( unsigned int iLine = 0 ; iLine < lines.size() ; iLine++){

    vector<string> words;

    words = split( lines[iLine] );

    if( words.size() != 4 ) 
      cout << "ERROR: syntax of line is not correct: " << lines[iLine] << endl;
    
    jetMult_     = JetMultNames[   words[ 0 ] ];
    htRegion_   = HtRegionNames[  words[ 1 ] ];
    metRegion_ = MetRegionNames[ words[ 2 ] ];
    
    //cout << jetMult_ << " " << htRegion_ << " " << metRegion_ << " " << words[3] << endl;

    double data = atof ( words[ 3 ].c_str() ); 

    fillHisto( data );

  }// end loop over lines
  
}

vector<string> &RA2tools::split(const string &s, vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, ' ')) {
    if( item.empty() ) continue;
    elems.push_back(item);
  }
  return elems;
}

vector<string> RA2tools::split(const string &s) {
  vector<string> elems;
  split(s, elems);
  return elems;
}





