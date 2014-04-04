import FWCore.ParameterSet.Config as cms
from commandLineParameters import *

process = cms.Process("analysis")

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
    )

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "START53_V11::All"

##################################
# DEFINE MODULES FOR ANALYSIS
##################################

# lepton filters

from PhysicsTools.PatAlgos.selectionLayer1.muonCountFilter_cfi import *

process.reasonableMuons = cms.EDFilter("CandViewSelector",
                                     src = cms.InputTag("patMuonsPF"),
                                     cut = cms.string(" isGlobalMuon"
     						      " && globalTrack().normalizedChi2 < 10"
						      " && globalTrack().hitPattern().numberOfValidMuonHits > 0"
						      " && globalTrack().hitPattern().numberOfValidPixelHits > 0"
						      " && numberOfMatchedStations > 1"
						      " && globalTrack().hitPattern().trackerLayersWithMeasurement > 5."
						      " && dB < 0.2"
						      " && fabs(muonBestTrack().dz(vertex.position())) < 0.5"
						      )
                                     )

process.MuonFinder = cms.EDFilter("CandViewCountFilter",
                                  src = cms.InputTag("reasonableMuons"),
                                  minNumber = cms.uint32(1)
                                  )

from PhysicsTools.PatAlgos.selectionLayer1.electronCountFilter_cfi import *

process.reasonableElectrons = cms.EDFilter("CandViewSelector",
                                         src = cms.InputTag("patElectronsPF"),
                                         cut = cms.string(" ("
							  " ("
							  " isEB &&"
							  " abs(deltaPhiSuperClusterTrackAtVtx) <= 0.15 &&"
							  " abs(deltaEtaSuperClusterTrackAtVtx) <= 0.007"
							  " )"
							  " ||"
							  " ("
							  " isEE &&"
							  " abs(deltaPhiSuperClusterTrackAtVtx) <= 0.10 &&"
							  " abs(deltaEtaSuperClusterTrackAtVtx) <= 0.009"
							  " )"
							  " )")
                                         )

process.ElectronFinder = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("reasonableElectrons"),
                                      minNumber = cms.uint32(1)
                                      )

from RecoJets.JetProducers.ak5PFJets_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *

process.fatjets = cms.EDProducer("CTJetSelection",
				 jetCollection = cms.untracked.string("patJetsAK5PF"),
				 ptmin = cms.untracked.double(30.0),
				 etamax = cms.untracked.double(2.5),
				 clusterRadius = cms.untracked.double(1.2),
				 dR = cms.untracked.double(0.5),
				 muonCollection = cms.untracked.string("patMuonsPF"),
				 electronCollection = cms.untracked.string("patElectronsPF"),
				 debug = cms.untracked.bool(False)
				  )

process.load('MScinta.CTFatJets.smsModelFilter_cfi')
process.smsModelFilter.SusyScanTopology = cms.string(options.SUSYtopo)
process.smsModelFilter.SusyScanMotherMass = cms.double(options.mGo)
process.smsModelFilter.SusyScanLSPMass = cms.double(options.mLSP)
process.smsModelFilter.SusyScanFracLSP = cms.double(0.0)
process.smsModelFilter.Debug = cms.bool(False)


process.TreeFiller = cms.EDAnalyzer("AnalysisTreeFiller",
                                    jetCollection = cms.untracked.string("patJetsAK5PF"),
                                    pseudoParticleCollection = cms.untracked.string("fatjets"),
                                    debug = cms.untracked.bool(False)
                                    )

## CONFIGURE TFILESERVICE

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(options.outputFile+"_CTFatJets_AnalysisTree.root"),
                                   closeFileFast = cms.untracked.bool(True)
                                   )

## LOAD DATAFILES
if options.inputFilesConfig!="" :
    process.load("MScinta.CTFatJets."+options.inputFilesConfig+"_cff")

if options.files!=[] :
    readFiles = cms.untracked.vstring()
    readFiles.extend( options.files )
    process.source = cms.Source("PoolSource",
                                fileNames = readFiles )

## EVENTS TO PROCESS
process.skipEvents = cms.untracked.PSet( input = cms.untracked.uint32(options.skipEvents) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.numEvents) )

## DEFINE SCHEDULE

process.bulkSequence = cms.Sequence(process.fatjets*
				    process.TreeFiller
				   )

process.leptonFilterSequence = cms.Sequence(process.reasonableElectrons
                                            *~process.ElectronFinder
                                            *process.reasonableMuons
                                            *~process.MuonFinder
                                            )

process.susyFilterSequence = cms.Sequence( process.smsModelFilter )

if( options.applySUSYfilter ):

    process.SuSySubstructureSequence = cms.Sequence(
						    process.susyFilterSequence*
                                                    #process.leptonFilterSequence*
                                                    process.bulkSequence
                                                    )
    
else:
    
    process.SuSySubstructureSequence = cms.Sequence(
						    #process.leptonFilterSequence*
                                                    process.bulkSequence
                                                   )

process.path = cms.Path(process.SuSySubstructureSequence)



