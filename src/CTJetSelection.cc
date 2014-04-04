// main code
//
// Package: CTJetSelection
// Class: CTJetSelection
/*

 Description: Takes as cfg input an anti-kt jet collection 
 and clusters the jets into large-R jets.
 A collection of 4-vectors corresponding to these 
 jets is saved to the event.
*/

//
// Author: Manuel Scinta
// Created: Fri Apr 04 2014
//
//

// system include files
#include <memory>

#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TLorentzVector.h"
#include "TTree.h"

#include "MScinta/CTFatJets/interface/CTJetSelection.h"

#include <fastjet/ClusterSequence.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/JetDefinition.hh>
#include <fastjet/tools/Filter.hh>

#include "SubjetCounting.hh"

#include <vector>


CTJetSelection::CTJetSelection(const edm::ParameterSet& iConfig):
  jetCollection(iConfig.getUntrackedParameter<std::string>("jetCollection","patJetsAK5PF")),
  ptmin(iConfig.getUntrackedParameter<double>("ptmin",30.0)),
  etamax(iConfig.getUntrackedParameter<double>("etamax",2.5)),
  clusterRadius(iConfig.getUntrackedParameter<double>("clusterRadius",1.2)),
  dR(iConfig.getUntrackedParameter<double>("dR",0.5)),
  muonCollection(iConfig.getUntrackedParameter<std::string>("muonCollection","patMuonsPF")),
  electronCollection(iConfig.getUntrackedParameter<std::string>("electronCollection","patElectronsPF")),
  debug(iConfig.getUntrackedParameter<bool>("debug",true))
{
  produces< std::vector< math::XYZTLorentzVector > >("");
}


CTJetSelection::~CTJetSelection()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}

//
// member functions
//

// ------------ method called for each event ------------
void CTJetSelection::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;

  // get collections
  Handle< View<pat::Jet> > jetCands;
  iEvent.getByLabel(jetCollection,jetCands);

  Handle< View<pat::Muon> > muonCands;
  iEvent.getByLabel(muonCollection,muonCands);

  Handle< View<pat::Electron> > electronCands;
  iEvent.getByLabel(electronCollection,electronCands);

  std::auto_ptr< std::vector< math::XYZTLorentzVector > > FatJets ( new std::vector< math::XYZTLorentzVector > () );

  if( debug )
	{
    std::cout << "===================" << std::endl;
    std::cout << "    New events     " << std::endl;
    std::cout << "===================" << std::endl;
	}

  std::vector<fastjet::PseudoJet> pre_jetColl;
  std::vector<fastjet::PseudoJet> _veto_jetColl;
  std::vector<fastjet::PseudoJet> veto_jetColl;
  std::vector<fastjet::PseudoJet> _fat_jetColl;
  std::vector<fastjet::PseudoJet> fat_jetColl;

  for(View<pat::Jet>::const_iterator iJet = jetCands->begin(); iJet != jetCands->end(); ++iJet)
	{
	
	 if (  iJet->pt() > ptmin && fabs( iJet->eta() ) < etamax )
		{
		pre_jetColl.push_back( fastjet::PseudoJet( iJet->px(), iJet->py() ,iJet->pz() ,iJet->energy() ) );
		}

	}

  //pre_jetColl is created and contains all the PFjets

  //NB: next ~30 lines were intended to remove leptons from jets.
  // However this may not be the right way and/or place to do it
  // Thus, these lines are commented
/*
  for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) 
	{
    bool jetIsOK = true;
    for (View<pat::Muon>::const_iterator iMuon = muonCands->begin(); iMuon != muonCands->end(); ++iMuon) 
		{
		float sq_eta_muon = (iMuon->eta() - pre_jetColl[ijet].eta() ) * (iMuon->eta() - pre_jetColl[ijet].eta() ) ;
		float sq_phi_muon = (iMuon->phi() - pre_jetColl[ijet].phi() ) * (iMuon->phi() - pre_jetColl[ijet].phi() ) ;
		float deltaR_muon = sqrt(sq_eta_muon + sq_phi_muon) ;
		if(deltaR_muon < dR)
			{
	  		jetIsOK = false;
	  		break;
			}
		}


    for (View<pat::Electron>::const_iterator iEle = electronCands->begin(); iEle != electronCands->end(); ++iEle) 
		{
		float sq_eta_ele = (iEle->eta() - pre_jetColl[ijet].eta() ) * (iEle->eta() - pre_jetColl[ijet].eta() ) ;
		float sq_phi_ele = (iEle->phi() - pre_jetColl[ijet].phi() ) * (iEle->phi() - pre_jetColl[ijet].phi() ) ;
		float deltaR_ele = sqrt(sq_eta_ele + sq_phi_ele) ;
		if(deltaR_ele < dR)
			{
	  		jetIsOK = false;
	  		break;
			}
		}

	if (jetIsOK)
      _veto_jetColl.push_back( fastjet::PseudoJet( pre_jetColl[ijet].px(),pre_jetColl[ijet].py(), pre_jetColl[ijet].pz(),pre_jetColl[ijet].e() ) );
	}

  veto_jetColl = sorted_by_pt(_veto_jetColl) ;
*/

  Bool_t   *used;
  Double_t **pairDR;
  Int_t    *DRjets;
  UInt_t   maxjetN;
  Bool_t   jetsleft;

  if (pre_jetColl.size()!=0) {
    pairDR = new Double_t* [pre_jetColl.size()];
    for (UInt_t i=0; i < pre_jetColl.size(); i++)
      pairDR[i] = new Double_t [pre_jetColl.size()];  
    for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++)
      for (UInt_t kjet = ijet+1; kjet < pre_jetColl.size(); kjet++)
	pairDR[ijet][kjet] = pre_jetColl[ijet].delta_R( pre_jetColl[kjet] );


    //count number of closest jets
    used = new Bool_t [pre_jetColl.size()];
    DRjets = new Int_t [pre_jetColl.size()];
    for (UInt_t i=0; i < pre_jetColl.size(); i++) {
      used[i]=false;
      DRjets[i]=0;
    }  
    for (UInt_t ijet = 0; ijet < pre_jetColl.size(); ijet++) 
      for (UInt_t kjet = ijet+1; kjet < pre_jetColl.size(); kjet++) 
	if (pairDR[ijet][kjet] < clusterRadius)
	  {
	  DRjets[ijet]++;
	  }

    //find the jet that has the most
    Double_t DRjets_temp=0;
    maxjetN=0;
    for (UInt_t i = 0; i < pre_jetColl.size(); i++) {
      if (DRjets_temp < DRjets[i]) {
	DRjets_temp = DRjets[i];
	maxjetN=i;
      }
    }
    
    //start merging from the one that has more
    UInt_t FATn=0;
    UInt_t ijet=maxjetN;
    jetsleft = true;
    while(jetsleft) {
      jetsleft=false;
      DRjets_temp=0;
      _fat_jetColl.push_back( pre_jetColl[ijet] );
      used[ijet] = true;
      for (UInt_t kjet = 0; kjet < pre_jetColl.size(); kjet++) {
	if (!used[kjet] && _fat_jetColl[FATn].delta_R( pre_jetColl[kjet] ) < clusterRadius) {
	  _fat_jetColl[FATn] += pre_jetColl[kjet];
	  used[kjet] = true;
	if (debug) std::cout << " non è qui l'errore madornale e grossolano "<<std::endl;
	}
	if (!used[kjet] && DRjets_temp<DRjets[kjet]) {
	  DRjets_temp = DRjets[kjet];
	  ijet=kjet;
	  jetsleft = true;
	}
      }

      FATn++;
    }

     fat_jetColl = sorted_by_pt(_fat_jetColl) ;
  }
  //FAT jet collection has been created and sorted

//  iEvent.put(fat_jetColl, jetCollection+"-fatjets" );
 
 for( unsigned int iFatJet = 0 ; iFatJet < fat_jetColl.size() ; iFatJet++ ){

      math::XYZTLorentzVector p4( fat_jetColl[iFatJet].px(),
                                  fat_jetColl[iFatJet].py(),
                                  fat_jetColl[iFatJet].pz(),
                                  fat_jetColl[iFatJet].e() ) ;

      FatJets->push_back( p4 ) ;

    }

   iEvent.put(FatJets) ;


}

// ------------ method called once each job just before starting event loop ------------
void CTJetSelection::beginJob()
{
}

// ------------ method called once each job just after ending the event loop ------------
void CTJetSelection::endJob()
{
}

// ------------ method called when starting to processes a run ------------
void CTJetSelection::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run ------------
void CTJetSelection::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block ------------
void CTJetSelection::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block ------------
void CTJetSelection::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module ------------
void CTJetSelection::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {

  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);

}

//define this as a plug-in
DEFINE_FWK_MODULE(CTJetSelection);
//
