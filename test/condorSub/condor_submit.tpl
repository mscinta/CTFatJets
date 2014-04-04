universe = vanilla
Executable            = run_<INDEX>.sh
Requirements          = Memory >= 199 &&OpSys == "LINUX"&& (Arch != "DUMMY" )&& Disk > 1000000
Should_Transfer_Files = YES
transfer_input_files=/uscms_data/d2/awhitbe1/workArea/RA2studies/CMSSW_5_3_8_patch1/src/AWhitbeck/SuSySubstructure/test/SuSySubstructureAnalysis.py,/uscms_data/d2/awhitbe1/workArea/RA2studies/CMSSW_5_3_8_patch1/src/AWhitbeck/SuSySubstructure/test/commandLineParameters.py
WhenToTransferOutput  = ON_EXIT_OR_EVICT
Output = out_$(Cluster).stdout
Error  = out_$(Cluster).stderr
Log    = out_$(Cluster).log
Notification    = Error
notify_user     = awhitbe1@FNAL.GOV
Queue 1
