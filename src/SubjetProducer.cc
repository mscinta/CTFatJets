// -*- C++ -*-
//
// Package:    SuSySubstructure
// Class:      SubjetProducer
// 
/*

 Description: Takes as cfg input a jet collection 
 and a collection of PFCandidates.  PFCandidates 
 are clustered each jet radius are reclustered for 
 calculating subjets according to arxiv::?????

*/
//
// Original Author:  Andrew Whitbeck
//         Created:  Wed Feb 10, 2014
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

#include "AWhitbeck/SuSySubstructure/interface/SubjetProducer.h"

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

SubjetProducer::SubjetProducer(const edm::ParameterSet& iConfig):
  jetCollection(iConfig.getUntrackedParameter<std::string>("jetCollection","ak1p2GenJets")),
  clusterRadius(iConfig.getUntrackedParameter<double>("clusterRadius",1.2)),
  trimPtFracMin(iConfig.getUntrackedParameter<double>("trimPtFracMin",0.05)),
  trimJets(iConfig.getUntrackedParameter<bool>("trimJets",true)),
  subjetPtCut(iConfig.getUntrackedParameter<double>("subjetPtCut",30.)),
  subjetMassCut(iConfig.getUntrackedParameter<double>("subjetMassCut",30.)),
  subjetRcut(iConfig.getUntrackedParameter<double>("subjetRcut",0.15)),
  subjetPtImbalance(iConfig.getUntrackedParameter<double>("subjetPtImbalance",.15)),
  debug(iConfig.getUntrackedParameter<bool>("debug",true))
{
  //produces< std::vector< reco::Jet > >(jetCollection+"-Subjets");
  produces< std::vector< math::XYZTLorentzVector > >(""); //(jetCollection+"-Subjets"); 
}


SubjetProducer::~SubjetProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
SubjetProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
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
  
  // initialize object for counting subjets
  if( debug ){
    std::cout << "subjet declustering parameters:" << std::endl;
    std::cout << "pt cut: " << subjetPtCut << std::endl;
    std::cout << "mass cut: " << subjetMassCut << std::endl;
    std::cout << "pt imbalannce: " << subjetPtImbalance << std::endl;
    std::cout << "dR cut: " << subjetRcut << std::endl;
  }

  fastjet::contrib::SubjetCountingCA subjetCounter_pt50(subjetMassCut,subjetPtImbalance,subjetRcut,subjetPtCut);
  // -------------------------------------

  // syntax is probably not right!!!!
  //std::auto_ptr< std::vector< reco::Jet > > Subjets ( new std::vector< reco::Jet > () );
  std::auto_ptr< std::vector< math::XYZTLorentzVector > > Subjets ( new std::vector< math::XYZTLorentzVector > () );

  if( debug ){
    std::cout << "new events" << std::endl;
    std::cout << "===================" << std::endl;
  }

  for(View<reco::Jet>::const_iterator iJet = jetCands->begin(); iJet != jetCands->end(); ++iJet){
      
    if ( iJet->pt() < 50. ) continue;

    if ( debug ) {

      std::cout << "std jet pt: " << iJet->pt() << std::endl;

    }// end debug

    // get jet constituents
    constituents.clear();      
    std::vector< const reco::Candidate * > jetConst = iJet->getJetConstituentsQuick();
    // loop over jet constituents for iJet
    // for each jet constituent, add to vector< pseudojet > for reclustering
    for ( unsigned int  iJetConst = 0 ; iJetConst < jetConst.size() ; iJetConst++ ){

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
      std::cout << "-----------------------" << std::endl;
    }
    // ..............................

    // trim jets
    fastjet::Filter trimmer( aktp12 , fastjet::SelectorPtFractionMin( trimPtFracMin ) );

    // decluster jets into subjets
    std::vector<fastjet::PseudoJet> pseudoSubjets ; 
    if( trimJets )
      pseudoSubjets = subjetCounter_pt50.getSubjets( trimmer( fatJets[ 0 ] ) ) ; 
    else
      pseudoSubjets = subjetCounter_pt50.getSubjets( fatJets[ 0 ] ) ;

    for( unsigned int iSubjet = 0 ; iSubjet < pseudoSubjets.size() ; iSubjet++ ){

      math::XYZTLorentzVector p4( pseudoSubjets[iSubjet].px(), 
                                  pseudoSubjets[iSubjet].py(), 
                                  pseudoSubjets[iSubjet].pz(), 
                                  pseudoSubjets[iSubjet].e() ) ;

      Subjets->push_back( p4 ) ; 

    }

  }// end loop over jets

  iEvent.put(Subjets) ; //,   jetCollection+"-Subjets"   );

}


// ------------ method called once each job just before starting event loop  ------------
void 

SubjetProducer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
SubjetProducer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
SubjetProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
SubjetProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
SubjetProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
SubjetProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SubjetProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(SubjetProducer);
