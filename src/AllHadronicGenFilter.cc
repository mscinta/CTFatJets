// -*- C++ -*-
//
// Package:    AllHadronicGenFilter
// Class:      AllHadronicGenFilter
// 
/**\class AllHadronicGenFilter AllHadronicGenFilter.cc 

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Andrew Whitbeck
//         Created:  Wed Oct 16 10:10:37 CDT 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1.h"
#include "TH2.h"
#include "TLorentzVector.h"
#include "TTree.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>

#include <fastjet/ClusterSequence.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/JetDefinition.hh>

#include <vector>



class AllHadronicGenFilter : public edm::EDFilter {

public:
  explicit AllHadronicGenFilter(const edm::ParameterSet&);
  ~AllHadronicGenFilter();
  
private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // ---------- configurable data ----------------
  // --------------- members ---------------------
  
  bool debug;                  

};


AllHadronicGenFilter::AllHadronicGenFilter(const edm::ParameterSet& iConfig):
  debug(iConfig.getUntrackedParameter<bool>("debug",false))
{

}


AllHadronicGenFilter::~AllHadronicGenFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
bool
AllHadronicGenFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  // fill histograms for di-lepton system

  using namespace edm;

  Handle< View<reco::GenParticle> > genCands;
  iEvent.getByLabel("genParticles",genCands);

  if(debug)
    std::cout << "New Event" << std::endl;
  
  for(View<reco::GenParticle>::const_iterator iCand = genCands->begin();
      iCand != genCands->end();
      ++iCand){

    if ( abs(iCand->pdgId()) == 6 ) {
      
      if ( debug ){
	std::cout << "top quark found: " << std::endl;
	std::cout << "daughters: " << iCand->numberOfDaughters() << std::endl;
	
	for ( unsigned int iDaughter = 0 ; iDaughter < iCand->numberOfDaughters() ; iDaughter++ ){
	  std::cout << iCand->daughter(iDaughter)->pdgId() << "  " ;
	}  

      }
    
      const reco::Candidate* topCand = &*iCand;
      while ( abs( topCand->daughter(0)->pdgId() ) == 6 ){
	topCand = topCand->daughter(0);
      }
	
      // find which top daughter is the W
      const reco::Candidate* Wcand;
    
      if ( abs(topCand->daughter(0)->pdgId()) == 24 ) Wcand = topCand->daughter(0) ;
      else if ( abs(topCand->daughter(1)->pdgId()) == 24 ) Wcand = topCand->daughter(1) ;
      else{
	std::cout << "NO W FOUND IN TOP DECAY!!!" << std::endl;
	continue;
      }

      if ( debug )
	std::cout << "    W found: " << std::endl;

      if(debug){
	std::cout << "        W status: " << Wcand->status() << std::endl;
	std::cout << "        W decay: " ;
	
	const reco::Candidate* tempCand = Wcand ; 
	
	while ( abs(tempCand->pdgId()) == 24 ){
	  
	  for ( unsigned int iWdaughter = 0 ; iWdaughter < tempCand->numberOfDaughters() ; iWdaughter++ ){
	    std::cout << tempCand->daughter(iWdaughter)->pdgId() << "  " ;
	    
	  }
	  
	  tempCand = tempCand->daughter(0);
	    
	}

	std::cout << std::endl;
	//std::cout << "last W daughter: " << tempCand->pdgId() << std::endl;

      }

      // check for leptonic W decay
      while ( abs( Wcand->daughter(0)->pdgId() ) == 24 ){
	Wcand = Wcand->daughter(0);
      }

      if( Wcand->numberOfDaughters() >= 2 ){
	if( abs( Wcand->daughter(0)->pdgId() ) > 6 ){
	  return false; // leptonic W decay
	}
      }else{
	std::cout << "Something is wrong with W decay..." << std::endl;
	std::cout << "number W daughters: " ;

	for ( unsigned int iWdaughter = 0 ; iWdaughter < Wcand->numberOfDaughters() ; iWdaughter++ ){
	  std::cout << "(" << Wcand->daughter(iWdaughter)->pdgId() << ", " << Wcand->daughter(iWdaughter)->status() << ") " ;
	}

	std::cout << std::endl;
	return false;  // something wrong with W decay...
      }

    } // check if iCand is a top

  } // end loop over iCand

  return true;

}


// ------------ method called once each job just before starting event loop  ------------
void 

AllHadronicGenFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
AllHadronicGenFilter::endJob() 
{
}


//define this as a plug-in
DEFINE_FWK_MODULE(AllHadronicGenFilter);
