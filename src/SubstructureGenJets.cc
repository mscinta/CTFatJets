// -*- C++ -*-
//
// Package:    SuSySubstructure
// Class:      SuSySubstructure
// 
/**\class SubstructureGenJets SubstructureGenJets.cc

 Description: Takes as cfg input a jet collection and
 a collection of PFCandidates.  PFCandidates within 
 each jet radius are reclustered for calculating 
 substructure variables. 

*/
//
// Original Author:  Andrew Whitbeck
//         Created:  Wed Dec 5, 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TTree.h"

#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/CompositeCandidate.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>

#include <fastjet/ClusterSequence.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/JetDefinition.hh>
#include <fastjet/tools/Filter.hh>
#include "SubjetCounting.hh"

#include <vector>


class SubstructureGenJets : public edm::EDProducer {

public:
  explicit SubstructureGenJets(const edm::ParameterSet&);
  ~SubstructureGenJets();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  // ----------member data ---------------------------


  // ---------- configurable data ----------------
  // --------------- members ---------------------
  
  std::string jetCollection;    // name of jet collection
  double      clusterRadius;    // jet clustering radius
  double      trimPtFracMin;   // %pt for trimming
  bool        trimJets;         // apply trimming
  bool        debug;
};


SubstructureGenJets::SubstructureGenJets(const edm::ParameterSet& iConfig):
  jetCollection(iConfig.getUntrackedParameter<std::string>("jetCollection","ak1p2GenJets")),
  clusterRadius(iConfig.getUntrackedParameter<double>("clusterRadius",1.2)),
  trimPtFracMin(iConfig.getUntrackedParameter<double>("trimPtFracMin",0.05)),
  trimJets(iConfig.getUntrackedParameter<bool>("trimJets",true)),
  debug(iConfig.getUntrackedParameter<bool>("debug",true))
{
  produces<double>(jetCollection+"-nSubJets");
  produces<double>(jetCollection+"-sumJetMass");
}


SubstructureGenJets::~SubstructureGenJets()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SubstructureGenJets::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // fill histograms for di-lepton system

  using namespace edm;

  Handle< View<reco::GenJet> > jetCands;
  iEvent.getByLabel(jetCollection,jetCands);

  // initialize object for counting subjets
  //               SubjetCountingCA(mass_cutoff,ycut,R_min,pt_cut);    
  std::vector<fastjet::PseudoJet> fatJets;
  std::vector<fastjet::PseudoJet> constituents;      

  fastjet::JetDefinition aktp12(fastjet::antikt_algorithm, clusterRadius);
  
  fastjet::contrib::SubjetCountingCA subjetCounter_pt50(50.,0.15,0.15,50.);
  // --------------------------------------------------------------

  std::auto_ptr<double> sumJetMass ( new double(0.0) );
  std::auto_ptr<double> nSubJets   ( new double(0.0) );

  if( debug ){
    std::cout << "new events" << std::endl;
    std::cout << "===================" << std::endl;
  }

  // loop over all jets to recluster and recover clutser sequence
  // NOTE: this might not produce the EXACT sequence from the original
  // clustering, but it should be close (might ask experts)
  for(View<reco::GenJet>::const_iterator iJet = jetCands->begin();
      iJet != jetCands->end();
      ++iJet){
      
    if ( iJet->pt() < 50. ) continue;

    if ( debug ) {

      std::cout << "std jet pt: " << iJet->pt() << std::endl;

    }// end debug

    // get jet constituents
    constituents.clear();      
    std::vector< const reco::Candidate * > jetConst = iJet->getJetConstituentsQuick();
    // loop over jet constituents for iJet
    for ( unsigned int  iJetConst = 0 ; 
	  iJetConst < jetConst.size() ;
	  iJetConst++ ){

      // get pseudojets to cluster
      constituents.push_back( fastjet::PseudoJet( jetConst[ iJetConst ]->px(), 
						  jetConst[ iJetConst ]->py(),
						  jetConst[ iJetConst ]->pz(),
						  jetConst[ iJetConst ]->energy() ) );

      if( debug ) {
	std::cout << "jet const. p_{mu}: " 
		  << jetConst[ iJetConst ]->px() << " " 
		  << jetConst[ iJetConst ]->py() << " " 
		  << jetConst[ iJetConst ]->pz() << " " 
		  << jetConst[ iJetConst ]->energy() << std::endl;
      }// end debug
      
    }// end loop over ith jet's constituents

    // recluster 
    fastjet::ClusterSequence cs_aktp12(constituents, aktp12);
    fatJets = sorted_by_pt(cs_aktp12.inclusive_jets());

    // sanity checks.................
    
    if( debug && fatJets.size() > 1 ) std::cout << "ERROR: " << fatJets.size() << " were clustered, but only 1 was expected. \n Only the first jet will be used." << std::endl;
    
    
    if( debug ){
      
      std::cout << "std Jet collection: " << iJet->pt() << std::endl;
      
      std::cout << "hand clustered jet: " << std::endl;
      for ( unsigned int k = 0 ; k < fatJets.size() ; k++){
	std::cout << "pt: " << fatJets[ k ].pt() << std::endl;
      }
    }
    if( debug ) 
      std::cout << "-----------------------" << std::endl;
    // ..............................

    // update sumJetMass and nSubJets for event
    if( fatJets.size() > 0 )
      *nSubJets   += subjetCounter_pt50.result( fatJets[ 0 ] );

    // trim jets
    fastjet::Filter trimmer( aktp12 , fastjet::SelectorPtFractionMin( trimPtFracMin ) );
    if( fatJets.size() > 0 )
      *sumJetMass += trimmer( fatJets[ 0 ] ).m();


  }// end loop over jets
  
  iEvent.put(sumJetMass, jetCollection+"-sumJetMass" );
  iEvent.put(nSubJets,   jetCollection+"-nSubJets"   );

}


// ------------ method called once each job just before starting event loop  ------------
void 

SubstructureGenJets::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SubstructureGenJets::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
SubstructureGenJets::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SubstructureGenJets::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SubstructureGenJets::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SubstructureGenJets::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SubstructureGenJets::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(SubstructureGenJets);
