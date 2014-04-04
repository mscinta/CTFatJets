import FWCore.ParameterSet.Config as cms
from commandLineParameters import *

process = cms.Process("analysis")

process.options = cms.untracked.PSet(
    SkipEvent = cms.untracked.vstring('ProductNotFound')
    )

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = options.reportEvery

process.options   = cms.untracked.PSet(
    SkipEvent   = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True)
    )

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "START53_V11::All"

##################################
# DEFINE MODULES FOR ANALYSIS
##################################

# selects events in which all tops decay hadronically ---- USE ONLY FOR GEN-LEVEL STUDIES
process.AllHadronicFilter = cms.EDFilter("AllHadronicGenFilter")

# Find events with at least one selected PAT muon/electron for vetoing

process.reasonableMuons = cms.EDFilter("CandViewSelector",
                                     src = cms.InputTag("selectedPatMuonsPF"),
                                     cut = cms.string("eta<2.5 && eta>-2.5 && pt>10.")
                                     )

process.MuonFinder = cms.EDFilter("CandViewCountFilter",
                                  src = cms.InputTag("reasonableMuons"),
                                  minNumber = cms.uint32(1)
                                  )

process.reasonableElectrons = cms.EDFilter("CandViewSelector",
                                         src = cms.InputTag("selectedPatElectronsPF"),
                                         cut = cms.string("eta<2.5 && eta>-2.5 && pt>10.")
                                         )

process.ElectronFinder = cms.EDFilter("CandViewCountFilter",
                                      src = cms.InputTag("reasonableElectrons"),
                                      minNumber = cms.uint32(1)
                                      )

# RA2 Baseline selections

process.RA2baseline = cms.EDFilter("RA2baselineSelection",
                                   jetCollection = cms.untracked.string("patJetsAK5PFPt30"),
                                   debug         = cms.untracked.bool(False)
                                   )

# official lepton filter

#process.load("MScinta.CTFatJets.RA2Leptons_cff")

#######################
# RA2 Event Filtering
#######################

#process.load("MScinta.CTFatJets.RA2CleaningFilterResults_cfg")

# CLUSTER PARTICLES

from RecoJets.JetProducers.GenJetParameters_cfi import *
from RecoJets.JetProducers.ak5GenJets_cfi import *
from RecoJets.JetProducers.ak5PFJets_cfi import *
from RecoJets.JetProducers.AnomalousCellParameters_cfi import *


#####################
# CLEAN GEN PARTICLES
#####################

process.minPtGenParticles = cms.EDFilter("PtMinCandViewSelector",
                                         src = cms.InputTag("genParticles"),
                                         ptMin = cms.double(0.001)
                                         )

process.load("RecoJets.Configuration.GenJetParticles_cff")
#genParticlesForJetsNoNu gets loaded above ---
process.genParticlesForJetsNoNu.src = cms.InputTag("genParticles")

######################

process.ak1p2GenJets = ak5GenJets.clone(src = cms.InputTag("genParticlesForJetsNoNu"),
                                        rParam = cms.double(1.2),
                                        useTrimming = cms.bool(True),
                                        rFilt = cms.double(0.2),
                                        trimPtFracMin = cms.double(0.05),
                                        useExplicitGhosts = cms.bool(False)
                                        )

process.ak1p2Jets = ak5PFJets.clone(src = cms.InputTag("pfNoPileUpIsoPF"),
                                    rParam = cms.double(1.2),
                                    useTrimming = cms.bool(True),
                                    rFilt = cms.double(0.2),
                                    trimPtFracMin = cms.double(0.05),
                                    useExplicitGhosts = cms.bool(False)
                                    )
    

# Produce subjet collection

process.fatJetSubjets = cms.EDProducer("SubjetProducer",
                                       jetCollection     = cms.untracked.string("ak1p2Jets"),
                                       clusterRadius     = cms.untracked.double(1.2),
                                       trimJets          = cms.untracked.bool(True),
                                       trimPtFracMin     = cms.untracked.double(0.05),
                                       subjetPtCut       = cms.untracked.double(30.),
                                       subjetMassCut     = cms.untracked.double(30.),
                                       subjetRcut        = cms.untracked.double(0.15),
                                       subjetPtImbalance = cms.untracked.double(0.15),
                                       debug             = cms.untracked.bool(False)
                                       )
# Calculate Substructure Variables and put into event
process.SubstructureGenJets = cms.EDProducer("SubstructureGenJets",
                                             jetCollection = cms.untracked.string("ak1p2GenJets"),
                                             clusterRadius = cms.untracked.double(1.2),
                                             trimJets      = cms.untracked.bool(True),
                                             trimPtFracMin = cms.untracked.double(0.05),
                                             debug         = cms.untracked.bool(False)
                                             )

process.Substructure = cms.EDProducer("Substructure",
                                      jetCollection = cms.untracked.string("ak1p2Jets"),
                                      clusterRadius = cms.untracked.double(1.2),
                                      trimJets      = cms.untracked.bool(True),
                                      trimPtFracMin = cms.untracked.double(0.05),
                                      debug         = cms.untracked.bool(False)
                                      )

# FILLS TREES WITH THE RELEVANT VARIABLES FOR SUM JET MASS

process.GenTreeFiller = cms.EDAnalyzer("GenJetTreeFiller",
                                       jetCollection = cms.untracked.string("ak5GenJetsNoNu:ak1p2GenJets"),
                                       debug         = cms.untracked.bool(False)
                                       )

process.TreeFiller = cms.EDAnalyzer("AnalysisTreeFiller",
                                    jetCollection = cms.untracked.string("patJetsAK5PFPt30:ak1p2Jets"),
                                    pseudoParticleCollection = cms.untracked.string("fatJetSubjets"),
                                    debug         = cms.untracked.bool(False)
                                    )

#######################################                                                                                                      
# SMS MODEL FILTER -- from Seema Sharma                                                                                                      
#######################################                                                                                                      

process.load('MScinta.CTFatJets.smsModelFilter_cfi')
process.smsModelFilter.SusyScanTopology = cms.string(options.SUSYtopo)
process.smsModelFilter.SusyScanMotherMass = cms.double(options.mGo)
process.smsModelFilter.SusyScanLSPMass = cms.double(options.mLSP)
process.smsModelFilter.SusyScanFracLSP = cms.double(0.0)
process.smsModelFilter.Debug = cms.bool(False)

## CONFIGURE TFILESERVICE

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string(options.outputFile+"_SumJetMass_AnalysisTree.root"),
                                   closeFileFast = cms.untracked.bool(True)
                                   )

##  LOAD DATAFILES
if options.inputFilesConfig!="" :
    process.load("MScinta.CTFatJets."+options.inputFilesConfig+"_cff")

if options.files!=[] :   
    readFiles = cms.untracked.vstring()
    readFiles.extend( options.files )
    process.source = cms.Source("PoolSource",
                                fileNames = readFiles )

##  EVENTS TO PROCESS
process.skipEvents = cms.untracked.PSet( input = cms.untracked.uint32(options.skipEvents) )
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(options.numEvents) )

##  DEFINE SCHEDULE

process.bulkSequence = cms.Sequence(process.ak1p2Jets
                                    *process.fatJetSubjets
                                    *process.Substructure
                                    *process.TreeFiller
                                    #*process.minPtGenParticles
                                    *process.genParticlesForJetsNoNu
                                    *process.ak1p2GenJets
                                    *process.SubstructureGenJets
                                    *process.GenTreeFiller
                                    )

if( options.useGenJets ):

    process.leptonFilterSequence = cms.Sequence( process.AllHadronicFilter )

else:

    process.leptonFilterSequence = cms.Sequence(process.reasonableElectrons#*process.minPtElectrons
                                                *~process.ElectronFinder
                                                *process.reasonableMuons#*process.minPtMuons
                                                *~process.MuonFinder
                                                )

process.susyFilterSequence = cms.Sequence( process.smsModelFilter )

if( options.applySUSYfilter ):

    process.SuSySubstructureSequence = cms.Sequence( process.susyFilterSequence*
                                                     #process.ra2ElectronVeto*
                                                     #process.ra2PFMuonVeto*
                                                     process.leptonFilterSequence*
                                                     #process.RA2baseline*
                                                     #process.cleaningOnFilterResults*
                                                     process.bulkSequence
                                                     )
    
else:
    
    process.SuSySubstructureSequence = cms.Sequence( #process.ra2ElectronVeto*
                                                     #process.ra2PFMuonVeto*
                                                     process.leptonFilterSequence*
                                                     #process.RA2baseline*
                                                     #process.cleaningOnFilterResults*
                                                     process.bulkSequence
                                                     )

process.path = cms.Path(process.SuSySubstructureSequence)

#OUPUT CONFIGURATION
#process.out = cms.OutputModule("PoolOutputModule",
#                               fileName = cms.untracked.string('test.root'),
#                               #save only events passing the full path
#                               #SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p') ),
#                               outputCommands = cms.untracked.vstring('keep *_*Jet*_*_*',
#                                                                      'keep *_*Substructure*_*_*')
#                               )
#
#process.outpath = cms.EndPath(process.out)
