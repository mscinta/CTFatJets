#include "TString.h"
#include "TChain.h"
#include "TH1F.h"
#include "TLegend.h"

using namespace std;

//TString dcache = "dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/" ; 

enum files { kQCD, kWjets, kZjets, kTop, kT1tttt, kNumFiles };
int colorCodes[kNumFiles] = { 1 , 3, 4 , 6 , 2 };

TString fileNames[kNumFiles] = {"QCD_condorSub/QCDsample_LPCSUSYPAT_ALL_SumJetMass_AnalysisTree.root",    //QCD 
				"WJetsToLNu_condorSub/WJetsToLNu_LPCSUSYPAT_12200000_SumJetMass_AnalysisTree.root",  //wjets 
				"ZJetsToNuNu_400HTinf_condorSub/ZJetsToNuNu_400HTinf_LPCSUSYPAT_0_SumJetMass_AnalysisTree.root",  //zjets 
				"TT_CT10_condorSub/TT_CT10_LPCSUSYPAT_19700000_SumJetMass_AnalysisTree.root",    //top   
				"T1tttt_mLSP-200_mGo-1000_condorSub/T1tttt_mG1000_mLSP200_LPCSUSYPAT_SumJetMass_AnalysisTree.root"};     // T1tttt

TString sampleNames[kNumFiles] = {"QCD",       //QCD 
				  "WJets",     //wjets 
				  "ZJets",     //zjets 
				  "Top",       //top   
				  "T1tttt" };  // T1tttt

void plotDist(char* drawVar="sumJetMass_pt50",char* binning="(20,0,2000)"){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  setTDRStyle();

  // fill signal tree and draw
  ///////////////////////////////////////
  TChain* sigTree = new TChain("TreeFiller/AnalysisTree");
  cout << sampleNames[ kT1tttt ] << " " << sigTree->Add( fileNames[ kT1tttt ] ) << endl;

  char drawString[150];
  sprintf(drawString,"%s>>sig%s",drawVar,binning);

  sigTree->Draw(drawString,"nJets_pt50>3");

  TH1F* sig = (TH1F*) gDirectory->Get("sig");
  sig->SetLineWidth(2);
  sig->SetLineColor(colorCodes[kT1tttt]);
  
  TLegend* leg = new TLegend(.9,.9,.7,.7);
  leg->SetFillColor(0);
  
  leg->AddEntry(sig,sampleNames[ kT1tttt ],"l");

  // Fill background tree and draw
  //////////////////////////////////////
  const int numBkg = 4;

  TChain* bkgTree[numBkg];
  TH1F* bkg[numBkg];
			
  for( unsigned int iBkg = 0 ; iBkg < numBkg ; iBkg++){

    //if( iBkg == 1 || iBkg==2 || iBkg==3 ) continue;
    
    bkgTree[iBkg] = new TChain("TreeFiller/AnalysisTree");
    cout << sampleNames[ iBkg ] << " " << bkgTree[iBkg]->Add( fileNames[ iBkg ] ) << endl;

    sprintf(drawString,"%s>>bkg%i%s",drawVar,iBkg,binning);

    bkgTree[iBkg]->Draw(drawString,"nJets_pt50>3");

    char histoName[150];
    sprintf(histoName,"bkg%i",iBkg);

    bkg[iBkg] = (TH1F*) gDirectory->Get(histoName);
    bkg[iBkg]->SetLineWidth(2);
    bkg[iBkg]->SetLineColor(colorCodes[iBkg]);

    leg->AddEntry(bkg[iBkg],sampleNames[ iBkg ],"l");

  }

  // hacking normalizations...
  //sig->Scale(1000*4.e-2/50000.);
  //bkg[kQCD]->Scale(1000*2.99e10/100000.);


  sig->DrawNormalized("");
  
  for( unsigned int iBkg = 0 ; iBkg < numBkg ; iBkg++){
    //if( iBkg == 1 || iBkg==2 || iBkg==3 ) continue;
    bkg[iBkg]->DrawNormalized("SAME");
  }

  leg->Draw();

}

