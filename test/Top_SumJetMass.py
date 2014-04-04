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
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

GenJetParameters.src = cms.InputTag("genParticlesForJetsNoNu")

process.ak5GenJets = cms.EDProducer("FastjetJetProducer",
                                    GenJetParameters,
                                    AnomalousCellParameters, 
                                    jetAlgorithm = cms.string("AntiKt"),
                                    rParam       = cms.double(0.5)
                                    )

process.ak1p2GenJets = cms.EDProducer("FastjetJetProducer",
                                      GenJetParameters,
                                      AnomalousCellParameters, 
                                      jetAlgorithm = cms.string("AntiKt"),
                                      rParam       = cms.double(1.2),
                                      useTrimming = cms.bool(True),
                                      rFilt = cms.double(0.2),
                                      trimPtFracMin = cms.double(0.05),
                                      useExplicitGhosts = cms.bool(True)
                                      )

# FILLS TREES WITH THE RELEVANT VARIABLES FOR SUM JET MASS
process.SumJetMassTreeFiller = cms.EDAnalyzer("GenJetTreeFiller",
                                              stdJetCollection = cms.untracked.string("ak5GenJets"),
                                              fatJetCollection = cms.untracked.string("ak1p2GenJets")
                                              )

## CONFIGURE TFILESERVICE

process.TFileService = cms.Service("TFileService",
      fileName = cms.string("Top_SumJetMass_AnalysisTree.root"),
      closeFileFast = cms.untracked.bool(True)
  )

##  MAXIMUM NUMBER OF EVENTS TO PROCESS
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

##  LOAD DATAFILES
#process.load("MScinta.CTFatJets.testSample_cff")
#process.load("MScinta.CTFatJets.ZHbbSample_cff")
#process.load("MScinta.CTFatJets.ZjetsSample_cff")
#process.load("MScinta.CTFatJets.T1ttttSample_cff")
process.load("MScinta.CTFatJets.topSample_cff")
#process.load("MScinta.CTFatJets.QCDSample_cff")

##  DEFINE PATH
process.p = cms.Path(process.AllHadronicFilter
                     *process.ak5GenJets
                     *process.ak1p2GenJets
                     *process.SumJetMassTreeFiller
                     )


#OUPUT CONFIGURATION
#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string('test.root'),
#                               #save only events passing the full path
#                               SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
#                               outputCommands = cms.untracked.vstring('keep *_*Candidate_*_*',
#                                                                      'keep *_selectedPat*_*_*',
#                                                                      'keep *_*GenJets*_*_*')
#                               )
#
#process.outpath = cms.EndPath(process.out)
