#!/bin/bash

date

source /uscmst1/prod/sw/cms/bashrc prod
workerNodeDir=`pwd`
echo $workerNodeDir
cd /uscms_data/d2/awhitbe1/workArea/RA2studies/CMSSW_5_3_8_patch1/src/AWhitbeck/SuSySubstructure/test/
eval `scram runtime -sh`
cd -
echo "-------------------------------------"
echo "FILES ON WORKER NODE BEFORE EXECUTION"
echo "-------------------------------------"
ls 

cmsRun SuSySubstructureAnalysis.py outputFile=<SAMPLE>_<INDEX> applySUSYfilter=False files=<FILELIST>

echo "------------------------------------"
echo "FILES ON WORKER NODE AFTER EXECUTION"
echo "------------------------------------"
ls 
