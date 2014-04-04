#include <DataFormats/JetReco/interface/Jet.h>
#include <DataFormats/MuonReco/interface/Muon.h>

#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/PatCandidates/interface/Muon.h>
#include <DataFormats/PatCandidates/interface/Electron.h>
#include <DataFormats/PatCandidates/interface/CompositeCandidate.h>
#include <DataFormats/ParticleFlowCandidate/interface/PFCandidate.h>


class CTJetSelection : public edm::EDProducer {

public:
  explicit CTJetSelection(const edm::ParameterSet&);
  ~CTJetSelection();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  virtual void beginJob() ;
  virtual void produce(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  virtual void beginRun(edm::Run const&, edm::EventSetup const&);
  virtual void endRun(edm::Run const&, edm::EventSetup const&);
  virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
  
  std::string jetCollection;
  double ptmin;
  double etamax;
  double clusterRadius;
  double dR;
  std::string muonCollection;
  std::string electronCollection;
  bool debug;
};
