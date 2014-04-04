#!/bin/sh

FASTJET_CONTRIB_LOCATION='http://fastjet.hepforge.org/contrib/downloads/fjcontrib-1.008.tar.gz'

# strip path and .tar.gz suffix
DIR_NAME=`echo $FASTJET_CONTRIB_LOCATION | awk -F 'http://fastjet.hepforge.org/contrib/downloads/' '{print $2}' | awk -F '.tar.gz' '{print $1}'`

wget $FASTJET_CONTRIB_LOCATION

if [ -a "${DIR_NAME}.tar.gz" ]
    then 
    
    gunzip "${DIR_NAME}.tar.gz"
    tar -xf "${DIR_NAME}.tar"

    if [ -d "${DIR_NAME}/SubjetCounting" ] 
	then 
	cp $DIR_NAME/SubjetCounting/*.cc src/.
	cp $DIR_NAME/SubjetCounting/*.hh src/.
	cp $DIR_NAME/SubjetCounting/example.cc src/SubjetCounting_example.cc_
    else
	echo "ERROR: 3rd party tool, SubjetCounting doesn't seem to exist"
    fi
    
    if [ -d "${DIR_NAME}/Nsubjettiness" ] 
	then 
	cp $DIR_NAME/Nsubjettiness/*.cc src/.
	cp $DIR_NAME/Nsubjettiness/*.hh src/.
	cp $DIR_NAME/Nsubjettiness/example.cc src/Nsubjetiness_example.cc_
    else
	echo "ERROR: 3rd party tool, Nsubjettiness doesn't seem to exist"
    fi

    rm -r $DIR_NAME
    rm "${DIR_NAME}.tar"

else

    echo "FILE NOT FOUND... PLEASE CHECK LOCATION: ${FASTJET_CONTRIB_LOCATION}"

fi
    
exit
