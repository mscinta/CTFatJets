import os
from optparse import OptionParser

# define options
parser = OptionParser()
parser.add_option("-n", "--nFiles", dest="nFiles", default=20,
                                    help="number of files to process per job")

parser.add_option("-f","--filesConfig",dest="filesConfig", default="QCD_250HT500_LPCSUSYPAT",
                                       help="which config file to retrieve the full file list from (leave off _cff.py)")

parser.add_option("-s","--submit",dest="submit", default=False,action="store_true",
                                       help="submit jobs to condor once they are configured")

(options, args) = parser.parse_args()

# varify specified options
print "nFiles: ",options.nFiles
print "filesConfig: ",options.filesConfig
print "submit: ",options.submit

# clean up
os.system("rm condor_submit_* run_*")

# grab full file list from config files
import FWCore.ParameterSet.Config as cms
process = cms.Process("demo")
process.load("MScinta.CTFatJets."+options.filesConfig+"_cff")

# index is to count jobs for labeling input and output files
index=0
# to keep track of how many data files have been divied up
fileListLen = len(process.source.fileNames)

print "There are ",fileListLen," files in your sample"

# calculate the number of jobs necessary
nJobs = fileListLen / int( options.nFiles )
if ( fileListLen % int( options.nFiles ) != 0 ) :
    nJobs += 1

print "I will create ",nJobs," for you!"

# start loop over N jobs
for iJob in range( nJobs ) :

    # initialize list string
    list = ""

    # build string which is a list of files
    # loop over options.nFiles
    for iFile in range( int(options.nFiles) ) :

        # protection against index going out of range of
        # process.source.fileNames
        if ( iFile+iJob*int( options.nFiles ) >= fileListLen ) :
            break

        if ( iFile == 0 ) :
            list += '"'+process.source.fileNames[iFile+iJob*int( options.nFiles )]+'"'
        else :
            list += ',"'+process.source.fileNames[iFile+iJob*int( options.nFiles )]+'"'

    # replace placeholders in .tpl files
    os.system("sed -e 's|<SAMPLE>|"+options.filesConfig+"|g' -e 's|<FILELIST>|"+list+"|g' -e 's|<INDEX>|"+str(iJob)+"|g' < run.tpl > run_"+str(iJob)+".sh")
    os.system("sed -e 's|<INDEX>|"+str(iJob)+"|g' < condor_submit.tpl > condor_submit_"+str(iJob))

    # submit jobs to condor, if -s was specified
    if ( options.submit ) :
        os.system("condor_submit condor_submit_"+str(iJob))
    

