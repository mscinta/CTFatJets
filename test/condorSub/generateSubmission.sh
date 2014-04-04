#!/bin/sh

echo "welcome!!!!!"

nEvents=9991674
eventsPerJob=100000

START=0
STOP=$eventsPerJob
while [ $START -lt $nEvents ]
  do

  #echo "START: " $START
  #echo "STOP:  " $STOP
  
  sed -e 's|<SKIP>|'$START'|g' -e 's|<NEVENTS>|'$eventsPerJob'|g'< run.tpl > run_${START}_${STOP}.sh
  sed -e 's|<EVENTRANGE>|'$START'_'$STOP'|g' < condor_submit.tpl > condor_submit_${START}_${STOP}
  
  echo "condor_submit condor_submit_${START}_${STOP}"

  START=$STOP
  STOP=$[$STOP+$eventsPerJob]

done

echo "bye!!!!!"

exit
