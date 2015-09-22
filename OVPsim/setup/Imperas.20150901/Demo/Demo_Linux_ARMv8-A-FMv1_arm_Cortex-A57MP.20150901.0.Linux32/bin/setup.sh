#!/bin/sh

#
# Setup file for Bourne Shell
#

# File must be sourced
if [ "$(basename -- $0 .sh)" == "setup" ]; then
    echo "This file should be sourced in a Bourne Shell"
    exit 1
fi

#
# Valid Runtime Libraries
# OVPsim CpuManager
#
function setupImperas () {
    #
    # Command Line Parse
    #
    local IH=''
    local M32=0
    while [ $# -gt 0 ]
    do
        case "$1" in
            -m32)
                M32=1;
                echo "Info: Emulate 32Bit setup"
                shift;;
              
            -help)
                echo "Usage: setupImperas [-help] [-m32] <Installation Directory>"
                echo "           -help, Print this help"
                echo "           -m32,  Run 32bit product under a 64bit OS"
                return 1
                shift;;
            
            *)
                IH=$1;
                shift;;
        esac
    done

    if [ -n "$IH" ] && [ -d ${IH} ]; then
        export IMPERAS_HOME=${IH}
        
        #
        # test if we are on Windows in a MinGW/MSys shell
        #
        if [ -n "${MSYSTEM}" ] && [ "${MSYSTEM}" = "MINGW32" ]; then
            export IMPERAS_UNAME=Windows
            export IMPERAS_SHRSUF=dll
            if [ ! -d "/c/Program Files (x86)" ] || [ ${M32} = 1 ]; then
                export IMPERAS_M32=1
                ARCHSIZE=32
            else
                export IMPERAS_M32=1
                ARCHSIZE=64
            fi
            
            #
            # Adjust path drive letter
            #
            if [ "${IMPERAS_HOME:0:1}" != "/" ]; then
                echo "Error: use msys style path ${IMPERAS_HOME}"
                setupImperas -help
                return 1
            else
                export IMPERAS_HOME=$(cd ${IMPERAS_HOME} && pwd -W)
            fi

        else

            export IMPERAS_UNAME=Linux
            export IMPERAS_SHRSUF=so
            if [ "$(uname -m)" = "i686" ] || [ ${M32} = 1 ]; then
                export IMPERAS_M32=1
                ARCHSIZE=32
            elif [ "$(uname -m)" = "x86_64" ]; then
                export IMPERAS_M32=0
                ARCHSIZE=64
            else
                echo "Error: Unsupported architecture $(uname -m)"
                setupImperas -help
                return 1
            fi
            
        fi
        
        export IMPERAS_ARCH=${IMPERAS_UNAME}${ARCHSIZE}
        export IMPERAS_VLNV=${IMPERAS_HOME}/lib/${IMPERAS_ARCH}/ImperasLib
        export PATH=${PATH}:${IH}/bin/${IMPERAS_ARCH}
        
        if [ "${IMPERAS_UNAME}" = "Linux" ]; then
            export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${IMPERAS_HOME}/bin/${IMPERAS_ARCH}
        fi
        
        if [ ! -d ${IMPERAS_HOME}/bin/${IMPERAS_ARCH} ]; then
            echo "Error: Installation Directory ${IMPERAS_HOME}/bin/${IMPERAS_ARCH} does not exist"
            setupImperas -help
            return 1
        fi

        #
        # If the runtime is not set, attempt to determine what product I am
        #
        if [ -z "${IMPERAS_RUNTIME}" ]; then
            if [ -f ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/libCpuManager.${IMPERAS_SHRSUF} ]; then
                export IMPERAS_RUNTIME=CpuManager
                echo "Info: IMPERAS_RUNTIME is undefined, defaulting to ${IMPERAS_RUNTIME}"
            fi
        fi
        #
        # Determine ISS to use
        #
        if [ -z "${IMPERAS_ISS}" ]; then
            if [ -f ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/iss.exe ]; then
                export IMPERAS_ISS=iss.exe
            elif [ -f ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/issdemo.exe ]; then
                export IMPERAS_ISS=issdemo.exe
            fi
            if [ ! -z ${IMPERAS_ISS} ]; then
                echo "Info: IMPERAS_ISS is undefined, defaulting to ${IMPERAS_ISS}"
            fi
        fi
    else
        echo "Error: No such <Installation Directory>=\"${IH}\""
        setupImperas -help
        return 1
    fi
}

echo "Function 'setupImperas' successfully added to shell:"
echo -n "   "
setupImperas -help

