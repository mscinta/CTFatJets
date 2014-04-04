# Starting with a skeleton process which gets imported with the following line
from PhysicsTools.PatAlgos.patTemplate_cfg import *

from PhysicsTools.PatAlgos.tools.coreTools import *

#process.source.fileNames = [
#    # RPV stop -> t jjj
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_10_1_OTN.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_11_1_fmL.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_12_1_EzE.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_13_1_JRw.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_14_1_QU7.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_15_1_G52.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_16_1_D0q.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_17_1_Hc9.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_18_1_UpA.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_19_1_P0I.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_1_1_2iH.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_20_1_rAW.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_21_1_XVV.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_22_1_lTh.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_23_1_ZpD.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_24_1_mju.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_25_1_2P7.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_26_1_Gfg.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_27_1_9L0.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_28_1_HIk.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_29_1_Zyn.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_2_1_Xqw.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_30_1_peG.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_31_1_Huv.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_32_1_ksS.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_33_1_qMf.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_34_1_dl7.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_35_1_uM1.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_36_1_eAZ.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_37_1_Z1m.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_38_1_QqX.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_39_1_N7h.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_3_1_SzV.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_40_1_Zbm.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_41_1_5MS.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_42_1_mBm.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_43_1_m6G.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_44_1_NP0.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_45_1_bHV.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_46_1_ESm.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_47_1_Sfq.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_48_1_QvW.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_49_1_sZc.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_4_1_h9J.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_50_1_k69.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_5_1_aPv.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_6_1_zdg.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_7_1_5Ql.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_8_1_JjL.root',
#    'root://cmseos:1094//eos/uscms/store/user/jhirsch/stop_tjjj_M300_M100_AOD/stop_tjjj_M300_M100_9_1_nki.root'
#    
#        ]                                                                     


process.load("MScinta.CTFatJets.T1tttt_mGo-1100to1400_mLSP-525to1000_AODSIM_cff")

process.GlobalTag.globaltag = cms.string( 'START53_V7G::All' )

from PhysicsTools.PatAlgos.patTemplate_cfg import *

#######################################
# PRIMARY VERTICES
#######################################

from PhysicsTools.SelectorUtils.pvSelector_cfi import pvSelector

process.goodOfflinePrimaryVertices = cms.EDFilter(
        "PrimaryVertexObjectFilter",
            filterParams = pvSelector.clone( maxZ = cms.double(24.0),
                                                                                  minNdof = cms.double(4.0) # this is >= 4
                                                                                  ),
            src=cms.InputTag('offlinePrimaryVertices')
            )

## IVF and BCandidate producer for Vbb cross check analysis
process.load('RecoVertex/AdaptiveVertexFinder/inclusiveVertexing_cff')

process.load("RecoJets.Configuration.GenJetParticles_cff")

#######################################
# SMS MODEL FILTER -- from Seema Sharma
#######################################

process.load('MScinta.CTFatJets.smsModelFilter_cfi')
process.smsModelFilter.SusyScanTopology = cms.string('T1tttt')
process.smsModelFilter.SusyScanMotherMass = cms.double(1150)
process.smsModelFilter.SusyScanLSPMass = cms.double(475)
process.smsModelFilter.SusyScanFracLSP = cms.double(0.0)
process.smsModelFilter.Debug = cms.bool(False)

# let it run
process.p0 = cms.Path(process.smsModelFilter
                      #*process.goodOfflinePrimaryVertices
                      #*process.inclusiveVertexing
                      *process.genParticlesForJetsNoNu
                      )

# reduce verbosity
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32(1000)

# process all the events
process.maxEvents.input = 100000
process.options.wantSummary = True

## OUPUT CONFIGURATION
process.out = cms.OutputModule("PoolOutputModule",
                                                              fileName = cms.untracked.string('genParticlesForJets.root'),
                                                              #save only events passing the full path
                                                              SelectEvents = cms.untracked.PSet( SelectEvents = cms.vstring('p0') ),
                                                              outputCommands = cms.untracked.vstring('keep *_*genParticle*_*_*')
                                                              )

process.outpath = cms.EndPath(process.out)






















