import FWCore.ParameterSet.Config as cms

process = cms.Process("demo")

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options   = cms.untracked.PSet(
    SkipEvent   = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
    )

##################################
# DEFINE MODULES FOR ANALYSIS
##################################

# SELECTS EVENTS IN WHICH ALL TOPS DECAY HADRONICALLY
process.AllHadronicFilter = cms.EDFilter("AllHadronicGenFilter")

# CLUSTER GEN PARTICLES

from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.ak5GenJets_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

process.ak1p2GenJets = ak5GenJets.clone(
    src = cms.string("genParticlesForJetsNoNu"),
    rParam = cms.double(1.2)
)

#process.ak1p2GenJets = cms.EDProducer("FastjetJetProducer",
#                                      GenJetParameters,
#                                      AnomalousCellParameters, 
#                                      jetAlgorithm = cms.string("AntiKt"),
#                                      rParam       = cms.double(1.2),
#                                      useTrimming = cms.bool(False),
#                                      rFilt = cms.double(0.2),
#                                      trimPtFracMin = cms.double(0.05),
#                                      useExplicitGhosts = cms.bool(False)
#                                      )

# Calculate Substructure Variables and put into event
process.Substructure = cms.EDProducer("Substructure",
                                      jetCollection = cms.untracked.string("ak1p2GenJets"),
                                      PFCandCollection = cms.untracked.string("genParticlesForJetsNoNu"),
                                      clusterRadius = cms.untracked.double(1.2),
                                      debug = cms.untracked.bool(False)
                                      )

##  EVENTS TO PROCESS

#process.skipEvents = cms.untracked.PSet( input = cms.untracked.uint32(5000) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

##  LOAD DATAFILES
#process.load("MScinta.CTFatJets.testSample_cff")
#process.load("MScinta.CTFatJets.ZHbbSample_cff")
#process.load("MScinta.CTFatJets.ZjetsSample_cff")
process.load("MScinta.CTFatJets.T1ttttSample_cff")
#process.load("MScinta.CTFatJets.QCDSample_cff")

##  DEFINE PATH
process.p = cms.Path(process.AllHadronicFilter
                     *process.ak1p2GenJets
                     *process.Substructure
                     )


#OUPUT CONFIGURATION
process.out = cms.OutputModule("PoolOutputModule",
                               fileName = cms.untracked.string('test.root'),
                               #save only events passing the full path
                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
                               outputCommands = cms.untracked.vstring('keep *_*GenJets*_*_*',
                                                                      'keep *_*_*sumJetMass*_*',
                                                                      'keep *_*_*nSubJets*_*')
                               )

process.outpath = cms.EndPath(process.out)
