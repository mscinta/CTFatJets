#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>

#include <fastjet/ClusterSequence.hh>
#include <fastjet/PseudoJet.hh>
#include <fastjet/JetDefinition.hh>
#include <fastjet/tools/Filter.hh>

#include "AWhitbeck/SuSySubstructure/src/SubjetCounting.hh"

#include <vector>


class SubjetProducer : public edm::EDProducer {

public:
  explicit SubjetProducer(const edm::ParameterSet&);
  ~SubjetProducer();
  
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
  
  std::string jetCollection;     // name of jet collection
  double      clusterRadius;     // jet clustering radius
  double      trimPtFracMin;     // %pt for trimming
  bool        trimJets;          // apply trimming
  double      subjetPtCut;       // min pt of subjets
  double      subjetMassCut;     // min mass of subjets
  double      subjetRcut;        // min delta R between subjets
  double      subjetPtImbalance; // maximum imbalance between jet and subjet 
  bool        debug;
};


