#!/bin/sh

PLATFORM=${IMPERAS_HOME}/ImperasLib/source/arm.ovpworld.org/platform/ARMv8-A-FMv1/1.0/platform

if [ -d $PLATFORM ]; then

  ANSWER=
  echo "Open a browser on platform directory [y/N]"
  read ANSWER
  if [ "${ANSWER}" = "y" ] || [ "${ANSWER}" = "Y" ] ; then
  
    if [ -x /usr/bin/firefox ]; then 
      firefox file:${PLATFORM}
    else 
      echo "Open directory ${PLATFORM} in a terminal to view platform source"
    fi
  fi

else
  echo "Platform source not found in this installation, please check required installation packages for $PLATFORM" 
fi