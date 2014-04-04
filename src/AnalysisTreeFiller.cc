// -*- C++ -*-
//
// Package:    AnalysisTreeFiller
// Class:      AnalysisTreeFiller
// 
/**\class AnalysisTreeFiller AnalysisTreeFiller.cc

 Description: Class which takes several types of jet collections
 and saves their kinematic properties to a TTree.  collections 
 that can be read and analyzed are either reco::Jet collections 
 and should be passed via the jetCollection argument or 
 std::vector< math::XYZTLorentzVector > collections (which 
 are built from the SubjetProducer, for example).   

 In both cases the string argument used to pass the collections
 can be used to pass a list of collections to be saved.  All
 collections should be deliniated used a ':'.  

 e.g.  for reading ak5PFJets and ak4PFJets collections, one 
 should pass "ak5PFJets:ak4PFJets" to jetCOllections.

 NOTE:  current, the get handle does not catch exceptions 
 from collections not being found in the event and thus 
 will just seg fault... this will hopefully be fixed soon.

*/
//
// Original Author:  Andrew Whitbeck
//         Created:  Wed Dec 17 2013
//         Last updated: Feb 11, 2014
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


class AnalysisTreeFiller : public edm::EDAnalyzer {

public:
  explicit AnalysisTreeFiller(const edm::ParameterSet&);
  ~AnalysisTreeFiller();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:

  // ----------member data ---------------------------
  
  TTree* AnalysisTree;

  TH1F*  Ht_histo;
  TH1F*  met_histo;
  TH1F*  sumJetMass_histo;

  TH2F*  Ht_vs_met_histo;
  TH2F*  Ht_vs_sumJetMass_histo;
  TH2F*  sumJetMass_vs_met_histo;

  struct jetKinematics {

    std::vector< double > pt;
    std::vector< double > eta;
    std::vector< double > mass;
    std::vector< double > phi;  
    int nJets;
    double sumJetMass;
    double missHt;
    double missHtPhi;
    double Ht;

  };

  std::vector< jetKinematics* > jetKin ;
  std::vector< jetKinematics* > particleKin ;

  double eventWeight;

  // ---------- configurable data ----------------
  // --------------- members ---------------------
  
  std::string jetCollection;    // name of jet collection
  std::string pseudoParticleCollection;    // name of jet collection
  std::vector < std::string > jetCollectionList ; // parsed jet collections
  std::vector < std::string > pseudoParticleCollectionList ; // parsed jet collections
  bool debug;

  // ---------- private methods! -----------

  virtual void beginJob() ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  void zeroJetKinematics( jetKinematics& jetKin );
  void addJetKinToTree( jetKinematics& jetKin, TString tag, TTree& tree );
  void parseString( std::vector< std::string > &container, std::string orig, size_t pos = 0, std::string delim = ":" );
  
};


AnalysisTreeFiller::AnalysisTreeFiller(const edm::ParameterSet& iConfig):
  jetCollection(iConfig.getUntrackedParameter<std::string>("jetCollection","patJetsAK5PFPt30")),
  pseudoParticleCollection(iConfig.getUntrackedParameter<std::string>("pseudoParticleCollection","fatjetSubjets")),
  debug(iConfig.getUntrackedParameter<bool>("debug",false))
{

  edm::Service<TFileService> fs;

  AnalysisTree            = fs->make<TTree>("AnalysisTree","AnalysisTree");

  // NOTE: histograms will only be filled for the last jet collection!
  // -----------------------------------------------------------------
  Ht_histo                = fs->make<TH1F >("Ht_histo","H_{T} [GeV]",400,0,2000);
  met_histo               = fs->make<TH1F >("met_histo","missing H_{T} [GeV]",400,0,2000);
  sumJetMass_histo        = fs->make<TH1F >("sumJetMass_histo","#Sigma m_{j} [GeV]",400,0,2000);

  Ht_vs_met_histo         = fs->make<TH2F >("Ht_vs_met_histo",";H_{T} [GeV];missing H_{T} [GeV]",400,0,2000,400,0,2000);
  Ht_vs_sumJetMass_histo  = fs->make<TH2F >("Ht_vs_sumJetMass_histo",";H_{T} [GeV];#Sigma m_{j} [GeV]",400,0,2000,400,0,2000);
  sumJetMass_vs_met_histo = fs->make<TH2F >("sumJetMass_vs_met_histo",";#Sigma m_{j} [GeV];missing H_{T} [GeV]",400,0,2000,400,0,2000);

  // parse list of jet collections to analyze
  parseString( jetCollectionList, jetCollection ) ;
  // parse list of pseudo particle collections to analyze
  parseString( pseudoParticleCollectionList, pseudoParticleCollection ) ;

  if( debug ){

    for(unsigned int iJetColl = 0 ; iJetColl < jetCollectionList.size() ; iJetColl++ ){
      std::cout << "jets collection " << iJetColl << " " << jetCollectionList[ iJetColl ] << std::endl;
    }
    for(unsigned int iParticleColl = 0 ; iParticleColl < pseudoParticleCollectionList.size() ; iParticleColl++ ){
      std::cout << "pseudo particle collection " << iParticleColl << " " << pseudoParticleCollectionList[ iParticleColl ] << std::endl;
    }

  }

  // add branches for saving jets kinematics for each jet collection
  for( unsigned int iJetColl = 0 ; iJetColl < jetCollectionList.size() ; iJetColl++ ){
    jetKin.push_back( new jetKinematics() );
    addJetKinToTree( *jetKin[ iJetColl ], jetCollectionList[ iJetColl ], *AnalysisTree );

  }
 // add branches for saving particle kinematics for each pseudo particle collection
  for( unsigned int iParticleColl = 0 ; iParticleColl < pseudoParticleCollectionList.size() ; iParticleColl++ ){
    particleKin.push_back( new jetKinematics() );
    addJetKinToTree( *particleKin[ iParticleColl ], pseudoParticleCollectionList[ iParticleColl ], *AnalysisTree );
  
  }

  AnalysisTree->Branch("eventWeight",&eventWeight,"eventWeight/D");

  if( debug )
    std::cout << "done in constructor" << std::endl;

}

AnalysisTreeFiller::~AnalysisTreeFiller()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
AnalysisTreeFiller::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if ( debug ) 
    std::cout << "AnalysisTreeFiller::analyze"  << std::endl;

  using namespace edm;

  // -- Monte Carlo Event Weight
  eventWeight = 1.0 ;
  edm::Handle< GenEventInfoProduct > genEventInfo;
  iEvent.getByLabel("generator", genEventInfo);
  
  if ( genEventInfo.isValid() ){
    
    if( debug )
      std::cout << genEventInfo->weight() << std::endl;

    eventWeight = genEventInfo->weight();

  }
  // ---------------------------

  // start section where jet collections will be looped over!!
  // ===================
  // -------------------
  for ( unsigned int iJetColl = 0 ; iJetColl < jetCollectionList.size() ; iJetColl++ ){

    if( debug ){

      std::cout << jetCollectionList[ iJetColl ] << std::endl;

    }

    Handle< View<reco::Jet> > jetCands;
    iEvent.getByLabel( jetCollectionList[ iJetColl ],jetCands);

    // set all variables in struct to zero or clear std::vectors
    zeroJetKinematics( *jetKin[ iJetColl ] );

    // for calculating missHt
    double negativePx_pt30 = 0.; 
    double negativePy_pt30 = 0.; 

    for(View<reco::Jet>::const_iterator iJet = jetCands->begin();
        iJet != jetCands->end();
        ++iJet){

      //std::cout  << "num. jets: " << jetCands->size() << std::endl;

      // kinematic selection for jets
      if ( iJet->pt() > 50. && fabs( iJet->eta() ) < 2.5 ){

        jetKin[ iJetColl ]->sumJetMass += iJet->mass() ;

      }// end if statement

      // kinematic selection for jets
      if ( iJet->pt() > 30. && fabs( iJet->eta() ) < 5. ){

        jetKin[ iJetColl ]->pt.push_back  (   iJet->pt()   );
        jetKin[ iJetColl ]->eta.push_back (   iJet->eta()  );
        jetKin[ iJetColl ]->phi.push_back (   iJet->phi()  );
        jetKin[ iJetColl ]->mass.push_back(   iJet->mass() );

        jetKin[ iJetColl ]->Ht  += iJet->pt();

        negativePx_pt30        -= iJet->px();
        negativePy_pt30        -= iJet->py();

      }// end if statement

    } // end loop over iJet

    jetKin[ iJetColl ]->missHt   = sqrt( pow( negativePx_pt30 , 2 ) + pow( negativePy_pt30 , 2 ) ) ;

    jetKin[ iJetColl ]->missHtPhi = acos( negativePx_pt30 / jetKin[ iJetColl ]->missHt ) ;

    jetKin[ iJetColl ]->nJets    = jetKin[ iJetColl ]->pt.size() ;

  } // end loop over jet collection list

    Ht_histo->Fill( jetKin[ jetKin.size() - 1 ]->Ht );
    met_histo->Fill( jetKin[ jetKin.size() - 1 ]->missHt );
    sumJetMass_histo->Fill( jetKin[ jetKin.size() - 1 ]->sumJetMass );

    Ht_vs_met_histo->Fill( jetKin[ jetKin.size() - 1 ]->Ht, jetKin[ jetKin.size() - 1 ]->missHt );
    Ht_vs_sumJetMass_histo->Fill( jetKin[ jetKin.size() - 1 ]->Ht, jetKin[ jetKin.size() - 1 ]->sumJetMass );
    sumJetMass_vs_met_histo->Fill( jetKin[ jetKin.size() - 1 ]->sumJetMass, jetKin[ jetKin.size() - 1 ]->missHt );

 for ( unsigned int iParticleColl = 0 ; iParticleColl < pseudoParticleCollectionList.size() ; iParticleColl++ ){

    if( debug ){

      std::cout << pseudoParticleCollectionList[ iParticleColl ] << std::endl;

    }

    Handle< std::vector < math::XYZTLorentzVector > > particleCands;
    iEvent.getByLabel( pseudoParticleCollectionList[ iParticleColl ],particleCands);

    // set all variables in struct to zero or clear std::vectors
    zeroJetKinematics( *particleKin[ iParticleColl ] );

    // for calculating missHt
    double negativePx_pt30 = 0.; 
    double negativePy_pt30 = 0.; 

    for( unsigned int iParticle = 0; iParticle < particleCands->size(); ++iParticle){

      math::XYZTLorentzVector p4 = (*particleCands)[iParticle] ; 

      // kinematic selection for pseudo particles
      if ( p4.pt() > 50. && fabs( p4.eta() ) < 2.5 ){

        particleKin[ iParticleColl ]->sumJetMass += p4.mass() ;

      }// end if statement

      // kinematic selection for jets
      if ( p4.pt() > 30. && fabs( p4.eta() ) < 5. ){

        particleKin[ iParticleColl ]->pt.push_back  (   p4.pt()   );
        particleKin[ iParticleColl ]->eta.push_back (   p4.eta()  );
        particleKin[ iParticleColl ]->phi.push_back (   p4.phi()  );
        particleKin[ iParticleColl ]->mass.push_back(   p4.mass() );

        particleKin[ iParticleColl ]->Ht  += p4.pt();

        negativePx_pt30        -= p4.px();
        negativePy_pt30        -= p4.py();

      }// end if statement

    } // end loop over iParticle

    particleKin[ iParticleColl ]->missHt    = sqrt( pow( negativePx_pt30 , 2 ) + pow( negativePy_pt30 , 2 ) ) ;

    particleKin[ iParticleColl ]->missHtPhi = acos( negativePx_pt30 / particleKin[ iParticleColl ]->missHt ) ;

    particleKin[ iParticleColl ]->nJets     = particleKin[ iParticleColl ]->pt.size();


  } // end loop over jet collection list

  AnalysisTree->Fill();    

}

// ------------ method to zero information in jetKinematics structs ---------------------
void AnalysisTreeFiller::zeroJetKinematics(jetKinematics& jetKin){

  if( debug ){

    std::cout << "AnalysisTreeFiller::zeroJetKinematics" << std::endl;

  }

  if( jetKin.pt.size() > 0 )
    jetKin.pt.clear();
  if( jetKin.eta.size() > 0 )
    jetKin.eta.clear();
  if( jetKin.mass.size() > 0 )
    jetKin.mass.clear();
  if( jetKin.phi.size() > 0 )
    jetKin.phi.clear();

  jetKin.nJets      = 0. ;
  jetKin.sumJetMass = 0. ;
  jetKin.missHt     = 0. ;
  jetKin.missHtPhi  = 0. ;
  jetKin.Ht         = 0. ;

  if( debug ){

    std::cout << "AnalysisTreeFiller::zeroJetKinematics -- done!" << std::endl;

  }

}

//------------ method for mapping jetKinematics structs to tree branches ------------
void AnalysisTreeFiller::addJetKinToTree(jetKinematics& jetKin, TString tag, TTree& tree){

  if( debug )
    std::cout << "AnalysisTreeFiller::addJetKinToTree" << std::endl;
  tree.Branch( "pt_" + tag,   &jetKin.pt);
  tree.Branch( "eta_" + tag,  &jetKin.eta);
  tree.Branch( "mass_" + tag, &jetKin.mass);
  tree.Branch( "phi_" + tag,  &jetKin.phi);
  
  TString branchName  = "nJets_" + tag ; 
  TString branchTitle = "nJets_" + tag + "/I" ;   
  tree.Branch( branchName.Data() ,      &jetKin.nJets , branchTitle.Data() );
  
  branchName  = "sumJetMass_" + tag ; 
  branchTitle = "sumJetMass_" + tag + "/D" ;   
  tree.Branch( branchName.Data() , &jetKin.sumJetMass , branchTitle.Data() );
  
  branchName  = "missHt_" + tag ; 
  branchTitle = "missHt_" + tag + "/D" ;   
  tree.Branch( branchName.Data() ,     &jetKin.missHt , branchTitle.Data() );
  
  branchName  = "missHtPhi_" + tag ;
  branchTitle = "missHtPhi_" + tag + "/D" ;   
  tree.Branch( branchName.Data() ,     &jetKin.missHtPhi , branchTitle.Data() );
  
  branchName  = "Ht_" + tag ;
  branchTitle = "Ht_" + tag + "/D" ;   
  tree.Branch( branchName.Data() ,         &jetKin.Ht , branchTitle.Data() );

  if( debug )
    std::cout << "AnalysisTreeFiller::addJetKinToTree - done " << std::endl;

}

//------------ method for parsing string passed from configuration file -------------
// ......... NOTE:  this aspect of the code is still in development .................
// This is intended to be used for passing multiple jet collections which are of 
// interest to the user to study.  
void AnalysisTreeFiller::parseString( std::vector< std::string > &container, std::string orig, size_t pos, std::string delim ){

  if ( orig.find( delim ) == std::string::npos ){
    container.push_back( orig );
    return;
  }

  container.push_back( orig.substr( 0, orig.find( delim ) ) ) ;
  parseString( container, orig.substr( orig.find( delim, pos ) + 1 ), orig.find( delim, pos ) ) ;

}

// ------------ method called once each job just before starting event loop  ------------
void AnalysisTreeFiller::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void AnalysisTreeFiller::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void AnalysisTreeFiller::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void AnalysisTreeFiller::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void AnalysisTreeFiller::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void AnalysisTreeFiller::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void AnalysisTreeFiller::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(AnalysisTreeFiller);
