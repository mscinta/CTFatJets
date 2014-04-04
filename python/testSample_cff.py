import FWCore.ParameterSet.Config as cms

source = cms.Source("PoolSource",
                    fileNames = cms.untracked.vstring(
    'file:../../../TopQuarkAnalysis/TopPairBSM/test/tlbsm_53x_v3_mc_46_1_gql.root'
    )
                    )
