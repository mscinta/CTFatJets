import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
           '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_10_1_3bD.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_11_1_Sm3.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_12_1_wMD.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_13_1_WvK.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_14_1_DCO.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_15_1_WyQ.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_16_1_9Lu.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_17_1_HSQ.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_18_1_0WE.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_19_1_my5.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_1_1_kon.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_20_1_x3e.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_21_1_JJw.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_2_1_WOP.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_3_1_6P7.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_4_1_tlR.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_5_1_0YO.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_6_1_krS.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_7_1_LOn.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_8_1_7n0.root',
                  '/store/user/lpcsusyhad/53X_ntuples/lhx/TTZJets_8TeV-madgraph_v2/TTZJets_8TeV-madgraph_PU_S10_START53_V7A-v1_NOCUTS_20Dec2012V2/0a0be23c0c67ac229a1c46c7277cb389/susypat_9_1_mbN.root' ] );


secFiles.extend( [
                   ] )

