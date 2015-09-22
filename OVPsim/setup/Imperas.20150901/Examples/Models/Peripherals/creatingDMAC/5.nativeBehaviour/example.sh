#!/bin/sh

# Check Installation supports this example
if [ -e ../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

if [ -e ${IMPERAS_HOME}/bin/${IMPERAS_ARCH}/igen.exe ]; then

igen.exe --batch         peripheral/pse/dmac.tcl      \
         --writec        peripheral/pse/dmac          \
         --writexml      peripheral/pse/dmac.igen.xml \
         --overwrite
        
else

echo "To run this template generation tool requires an installation of the Imperas Professional Tools"
echo "Please contact info@imperas.com or visit www.imperas.com for further information"
echo "on multicore debug, verification and analysis solutions"

fi

make -C application     
make -C platform         NOVLNV=1

make -C peripheral/pse   NOVLNV=1 
make -C peripheral/model NOVLNV=1 

platform/platform.${IMPERAS_ARCH}.exe --program application/dmaTest.elf

