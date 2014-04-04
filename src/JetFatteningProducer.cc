// -*- C++ -*-
//
// Package:    SuSySubstructure
// Class:      JetFatteningProducer
// 
/*

 Description: Takes as cfg input a jet collection 
 and clusters the jets into large-R anti-kt jets.
 A collection of 4-vectors corresponding to these 
 jets is saved to the event.

*/
//
// Original Author:  Andrew Whitbeck
//         Created:  Wed March 7, 2014
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

#include "AWhitbeck/SuSySubstructure/interface/JetFatteningProducer.h"

#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TTree.h"

#include <DataFormats/JetReco/interface/Jet.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>

#include <fastjet/ClusterSequence.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/JetDefinition.hh>
#include <fastjet/tools/Filter.hh>

#include "SubjetCounting.hh"

#include <vector>

JetFatteningProducer::JetFatteningProducer(const edm::ParameterSet& iConfig):
  jetCollection(iConfig.getUntrackedParameter<std::string>("jetCollection","patJetsAK5PFPt30")),
  clusterRadius(iConfig.getUntrackedParameter<double>("clusterRadius",1.2)),
  debug(iConfig.getUntrackedParameter<bool>("debug",true))
{
  //produces< std::vector< reco::Jet > >(jetCollection+"-Subjets");
  produces< std::vector< math::XYZTLorentzVector > >(""); //jetCollection+"-FattenedJets"); 
}


JetFatteningProducer::~JetFatteningProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
JetFatteningProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // fill histograms for di-lepton system

  using namespace edm;

  // get jet collection
  Handle< View<reco::Jet> > jetCands;
  iEvent.getByLabel(jetCollection,jetCands);

  // initialize objects needed for fastjet 
  // -------------------------------------
  std::vector<fastjet::PseudoJet> fatJets;
  std::vector<fastjet::PseudoJet> constituents;      
  fastjet::JetDefinition aktp12(fastjet::antikt_algorithm, clusterRadius);  
  // -------------------------------------

  // syntax is probably not right!!!!
  //std::auto_ptr< std::vector< reco::Jet > > Subjets ( new std::vector< reco::Jet > () );
  std::auto_ptr< std::vector< math::XYZTLorentzVector > > fatJet4Vec ( new std::vector< math::XYZTLorentzVector > () );

  if( debug ){
    std::cout << "new events" << std::endl;
    std::cout << "===================" << std::endl;
  }

  for(View<reco::Jet>::const_iterator iJet = jetCands->begin(); iJet != jetCands->end(); ++iJet){
      
    if ( debug ) {

      std::cout << "std jet pt: " << iJet->pt() << std::endl;

    }// end debug

    constituents.push_back( fastjet::PseudoJet( iJet->px(),
                                                iJet->py(),
                                                iJet->pz(),
                                                iJet->energy()
                                              )
                          ) ; 
    if( debug ) {
	       std::cout << "input jets p_{mu}: " 
		      << iJet->px() << " " 
		      << iJet->py() << " " 
		      << iJet->pz() << " " 
		      << iJet->energy() << std::endl;
    }// end debug
     

  }// end loop over jets

	// recluster 
	fastjet::ClusterSequence cs_aktp12(constituents, aktp12);
	fatJets = sorted_by_pt(cs_aktp12.inclusive_jets());

	if( debug ){
	  
	  std::cout << "hand clustered jet: " << std::endl;
	  for ( unsigned int k = 0 ; k < fatJets.size() ; k++){
	      std::cout << "pt: " << fatJets[ k ].pt() << std::endl;
	  }
	  std::cout << "-----------------------" << std::endl;
	}
	// ..............................


	// fill vector of XYZTLorentzVector for putting in event
	for( unsigned int iFatJet = 0 ; iFatJet < fatJets.size() ; iFatJet++ ){

	  math::XYZTLorentzVector p4( fatJets[iFatJet].px(), 
	                              fatJets[iFatJet].py(), 
	                              fatJets[iFatJet].pz(), 
	                              fatJets[iFatJet].e() ) ;

	  fatJet4Vec->push_back( p4 ) ; 

	}// done filling XYZTLorentzVector vector


  iEvent.put(fatJet4Vec); 
}


// ------------ method called once each job just before starting event loop  ------------
void 

JetFatteningProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetFatteningProducer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
JetFatteningProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
JetFatteningProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
JetFatteningProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
JetFatteningProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetFatteningProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(JetFatteningProducer);
