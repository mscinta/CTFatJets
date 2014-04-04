#!/bin/bash

date

source /uscmst1/prod/sw/cms/bashrc prod
workerNodeDir=`pwd`
echo $workerNodeDir
cd /uscms_data/d3/mgs86/CMSSW_5_3_12_patch3/src/MScinta/CTFatJets/test/
eval `scram runtime -sh`
cd -
echo "-------------------------------------"
echo "FILES ON WORKER NODE BEFORE EXECUTION"
echo "-------------------------------------"
ls 

cmsRun CTFatJets.py inputFilesConfig=QCDsample_susyPAT outputFile=QCDsample_LPCSUSYPAT applySUSYfilter=False numEvents=2000

echo "------------------------------------"
echo "FILES ON WORKER NODE AFTER EXECUTION"
echo "------------------------------------"
ls 
