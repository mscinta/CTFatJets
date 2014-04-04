// -*- C++ -*-
//
// Package:    GenJetTreeFiller
// Class:      GenJetTreeFiller
// 
/**\class GenJetTreeFiller GenJetTreeFiller.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Whitbeck
//         Created:  Wed Dec 17 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TTree.h"

#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/CompositeCandidate.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>

#include <SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h>

#include <fastjet/ClusterSequence.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/JetDefinition.hh>

#include "SubjetCounting.hh"

#include <vector>


class GenJetTreeFiller : public edm::EDAnalyzer {

public:
  explicit GenJetTreeFiller(const edm::ParameterSet&);
  ~GenJetTreeFiller();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // ----------member data ---------------------------

  TTree* GenJetTree;

  TH1F*  Ht_histo;
  TH1F*  met_histo;
  TH1F*  sumJetMass_histo;

  TH2F*  Ht_vs_met_histo;
  TH2F*  Ht_vs_sumJetMass_histo;
  TH2F*  sumJetMass_vs_met_histo;

  struct treeStructure {

    std::vector<double> jetPt_min30;
    std::vector<double> jetPt_min50;

    std::vector<double> jetMass_pt30;
    std::vector<double> jetMass_pt50;

    double sumJetMass_pt50;
    double sumJetMass_pt30;
    int nSubJets_pt50;
    int nSubJets_pt30;
    double Ht_pt30;
    double Ht_pt50;
    double met_pt30;    
    double met_pt50;

    int nJets_pt30;
    int nJets_pt50;

    double eventWeight;

  };
  
  treeStructure myTree;

  // ---------- configurable data ----------------
  // --------------- members ---------------------
  
  std::string stdJetCollection;    // name of jet collection
  std::string fatJetCollection;      // name of jet collection with large R

  bool debug;
};


GenJetTreeFiller::GenJetTreeFiller(const edm::ParameterSet& iConfig):
  stdJetCollection(iConfig.getUntrackedParameter<std::string>("stdJetCollection","ak5GenJets")),
  fatJetCollection(iConfig.getUntrackedParameter<std::string>("fatJetCollection","ak1p2GenJets")),
  debug(iConfig.getUntrackedParameter<bool>("debug",false))
{

  //now do what ever initialization is needed
  edm::Service<TFileService> fs;

  GenJetTree = fs->make<TTree>("GenJetTree","GenJetTree");

  Ht_histo                = fs->make<TH1F >("Ht_histo","H_{T} [GeV]",400,0,2000);
  met_histo               = fs->make<TH1F >("met_histo","missing H_{T} [GeV]",400,0,2000);
  sumJetMass_histo        = fs->make<TH1F >("sumJetMass_histo","#Sigma m_{j} [GeV]",400,0,2000);

  Ht_vs_met_histo         = fs->make<TH2F >("Ht_vs_met_histo",";H_{T} [GeV];missing H_{T} [GeV]",400,0,2000,400,0,2000);
  Ht_vs_sumJetMass_histo  = fs->make<TH2F >("Ht_vs_sumJetMass_histo",";H_{T} [GeV];#Sigma m_{j} [GeV]",400,0,2000,400,0,2000);
  sumJetMass_vs_met_histo = fs->make<TH2F >("sumJetMass_vs_met_histo",";#Sigma m_{j} [GeV];missing H_{T} [GeV]",400,0,2000,400,0,2000);

  GenJetTree->Branch("jetPt_min30",&myTree.jetPt_min30);
  GenJetTree->Branch("jetPt_min50",&myTree.jetPt_min50);
  GenJetTree->Branch("jetMass_pt30",&myTree.jetMass_pt30);
  GenJetTree->Branch("jetMass_pt50",&myTree.jetMass_pt50);
  GenJetTree->Branch("sumJetMass_pt30",&myTree.sumJetMass_pt30,"sumJetMass_pt30/D");
  GenJetTree->Branch("sumJetMass_pt50",&myTree.sumJetMass_pt50,"sumJetMass_pt50/D");
  GenJetTree->Branch("nSubJets_pt30",&myTree.nSubJets_pt30,"nSubJets_pt30/I");
  GenJetTree->Branch("nSubJets_pt50",&myTree.nSubJets_pt50,"nSubJets_pt50/I");
  GenJetTree->Branch("Ht_pt30",&myTree.Ht_pt30,"Ht_pt30/D");
  GenJetTree->Branch("Ht_pt50",&myTree.Ht_pt50,"Ht_pt50/D");
  GenJetTree->Branch("met_pt30",&myTree.met_pt30,"met_pt30/D");
  GenJetTree->Branch("met_pt50",&myTree.met_pt50,"met_pt50/D");
  GenJetTree->Branch("nJets_pt30",&myTree.nJets_pt30,"nJets_pt30/I");
  GenJetTree->Branch("nJets_pt50",&myTree.nJets_pt50,"nJets_pt50/I");
  GenJetTree->Branch("eventWeight",&myTree.eventWeight,"eventWeight/D");

}


GenJetTreeFiller::~GenJetTreeFiller()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenJetTreeFiller::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // fill histograms for di-lepton system

  using namespace edm;

  // -- Monte Carlo Event Weight
  double eventWeight = 1.0 ;
  edm::Handle< GenEventInfoProduct > genEventInfo;
  iEvent.getByLabel("generator", genEventInfo);
  
  if ( genEventInfo.isValid() ){
    
    if( debug )
      std::cout << genEventInfo->weight() << std::endl;

    eventWeight = genEventInfo->weight();

  }

  myTree.eventWeight = eventWeight;
  // ---------------------------

  Handle< View<reco::GenJet> > jetCands;
  iEvent.getByLabel(stdJetCollection,jetCands);

  Handle< View<reco::GenJet> > fatJetCands;
  iEvent.getByLabel(fatJetCollection,fatJetCands);

  myTree.jetPt_min30.clear();
  myTree.jetMass_pt30.clear();

  myTree.jetPt_min50.clear();
  myTree.jetMass_pt50.clear();

  myTree.sumJetMass_pt30 = 0.;
  myTree.sumJetMass_pt50 = 0.;

  myTree.nSubJets_pt50   = 0.;
  myTree.nSubJets_pt30   = 0.;

  myTree.Ht_pt30         = 0.;
  myTree.Ht_pt50         = 0.;

  myTree.met_pt30        = 0.; 
  myTree.met_pt50        = 0.; 

  double negativePx_pt30 = 0.; 
  double negativePy_pt30 = 0.; 

  double negativePx_pt50 = 0.; 
  double negativePy_pt50 = 0.; 

  for(View<reco::GenJet>::const_iterator iJet = jetCands->begin();
      iJet != jetCands->end();
      ++iJet){

    //std::cout  << "num. jets: " << jetCands->size() << std::endl;

    // kinematic selection for jets
    if ( iJet->pt() > 50. &&
	 fabs( iJet->eta() ) < 2.5 ){
      
      // set variables for tree
      myTree.jetPt_min50.push_back  (   iJet->pt() );
      myTree.jetMass_pt50.push_back (   iJet->mass()    );

      myTree.Ht_pt50         += iJet->pt();

      negativePx_pt50        -= iJet->px();
      negativePy_pt50        -= iJet->py();

    }// end if statement

    // kinematic selection for jets
    if ( iJet->pt() > 30. && 
	 fabs( iJet->eta() ) < 5. ){

      myTree.jetPt_min30.push_back  (   iJet->pt() );
      myTree.jetMass_pt30.push_back (   iJet->mass()    );

      myTree.Ht_pt30         += iJet->pt();

      negativePx_pt30        -= iJet->px();
      negativePy_pt30        -= iJet->py();

    }// end if statement

  } // end loop over iJet

  myTree.met_pt30   = sqrt( pow( negativePx_pt30 , 2 ) + pow( negativePy_pt30 , 2 ) ) ;
  myTree.met_pt50   = sqrt( pow( negativePx_pt50 , 2 ) + pow( negativePy_pt50 , 2 ) ) ;

  myTree.nJets_pt30 = myTree.jetPt_min30.size();
  myTree.nJets_pt50 = myTree.jetPt_min50.size();
  
  // grab substructure variables from the event
  // ..........................................
  Handle< double > sumJetMass;
  iEvent.getByLabel("SubstructureGenJets","ak1p2GenJets-sumJetMass",sumJetMass);

  myTree.sumJetMass_pt30 = *sumJetMass;
  myTree.sumJetMass_pt50 = *sumJetMass;

  Handle< double > nSubJets;
  iEvent.getByLabel("SubstructureGenJets","ak1p2GenJets-nSubJets",nSubJets);

  myTree.nSubJets_pt30 = *nSubJets;
  myTree.nSubJets_pt50 = *nSubJets;
  // ..........................................

  GenJetTree->Fill();    

  Ht_histo->Fill( myTree.Ht_pt50 );
  met_histo->Fill( myTree.met_pt30 );
  sumJetMass_histo->Fill( myTree.sumJetMass_pt50 );

  Ht_vs_met_histo->Fill( myTree.Ht_pt50, myTree.met_pt30 );
  Ht_vs_sumJetMass_histo->Fill( myTree.Ht_pt50, myTree.sumJetMass_pt50 );
  sumJetMass_vs_met_histo->Fill( myTree.sumJetMass_pt50, myTree.met_pt30 );

}


// ------------ method called once each job just before starting event loop  ------------
void 

GenJetTreeFiller::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenJetTreeFiller::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
GenJetTreeFiller::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
GenJetTreeFiller::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
GenJetTreeFiller::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
GenJetTreeFiller::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenJetTreeFiller::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(GenJetTreeFiller);
