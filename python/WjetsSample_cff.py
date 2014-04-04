import FWCore.ParameterSet.Config as cms

source = cms.Source("PoolSource",
                    fileNames = cms.untracked.vstring(

'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_10_1_SoJ.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_11_1_nC7.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_12_1_Mhn.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_13_1_wOZ.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_14_1_72R.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_15_1_Zhk.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_16_1_JNm.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_17_1_q1f.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_18_1_KW6.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_19_1_afq.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_1_1_zlE.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_20_1_8AB.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_21_1_fVa.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_22_1_XAf.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_23_1_tlB.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_24_1_ljf.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_25_1_kYT.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_26_1_8Yt.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_27_1_kZC.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_28_1_NV3.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_29_1_kxk.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_2_1_dr6.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_30_1_cOE.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_31_1_7po.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_32_1_yE1.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_33_1_yrj.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_34_1_16J.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_35_1_aOL.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_36_1_YL9.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_37_1_8Vr.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_38_1_DX4.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_39_1_80t.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_3_1_7gd.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_40_1_aWR.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_41_1_9qA.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_42_1_MMM.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_43_1_jZP.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_44_1_MOC.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_45_1_kUd.root',
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_46_1_ekb.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_47_1_4lx.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_48_1_WY6.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_49_1_TEw.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_4_1_D5k.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_50_1_Hbj.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_51_1_v5Y.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89genParticlesForJets_52_1_mXZ.root', 
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89/genParticlesForJets_5_1_W4K.root',  
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89genParticlesForJets_6_1_BsB.root',  
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89genParticlesForJets_7_1_H5l.root',  
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89genParticlesForJets_8_1_WqD.root',  
'dcap://cmsgridftp.fnal.gov:24125/pnfs/fnal.gov/usr/cms/WAX/11/store/user/awhitbe1/WJetsToLNu_HT-400ToInf_8TeV-madgraph_v2/WJetsToLNu_HT-400ToInf_8TeV_B2Gpattuples/2bb82e88d0aa4b02e8a4c924a176bf89genParticlesForJets_9_1_odM.root'  

)
)













































