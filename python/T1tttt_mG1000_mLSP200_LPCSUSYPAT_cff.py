import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job0.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job3.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job6.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job9.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job1.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job4.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job7.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job2.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job5.root',
           '/store/user/lpcsusyhad/lacroix/2012SEP05/T1tttt/T1tttt_mG1000_mLSP200_NOCUTS_09Aug2012V1/susypat_T2tt_1000_200_job8.root'

           ] );


secFiles.extend( [
                   ] )











