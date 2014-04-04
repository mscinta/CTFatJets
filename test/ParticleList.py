
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

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
process.printTree = cms.EDAnalyzer("ParticleListDrawer",
  maxEventsToPrint = cms.untracked.int32(1),
  printVertex = cms.untracked.bool(False),
  src = cms.InputTag("genParticles")
)

##  LOAD DATAFILES
#process.load("MScinta.CTFatJets.RPVstopSample_cff")
process.load("MScinta.CTFatJets.T1tttt_mG-1150_mLSP-475_Sample_cff")

##  MAXIMUM NUMBER OF EVENTS TO PROCESS
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1) )

##  DEFINE PATH
process.p = cms.Path(process.printTree)

