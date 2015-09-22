#!/bin/sh

# Check Installation supports this demo
if [ -e ../../../bin/${IMPERAS_ARCH}/checkinstall.exe ]; then
  ../../../bin/${IMPERAS_ARCH}/checkinstall.exe -p install.pkg --nobanner || exit
fi

# Ensure control file used is controlled by this script
export IMPERAS_TOOLS=enable-multicorehost.ic

# Enable multicorehost execution
echo "# MultiCore Host Parallel"    > $IMPERAS_TOOLS
echo "--parallel"                  >> $IMPERAS_TOOLS
echo "--quantum 0.00001"           >> $IMPERAS_TOOLS

# Run for 15 seconds (simulated time)
echo "--finishtime 15"             >> $IMPERAS_TOOLS

PLATFORM=ARMv8-A-FMv1
PLATFORMVLNV=${IMPERAS_VLNV}/arm.ovpworld.org/platform/${PLATFORM}/1.0/platform.${IMPERAS_ARCH}.exe

# Execute some user applications once boot complete
${PLATFORMVLNV} --output imperas.log --verbose \
 \
 --startaddress 0x80000000 \
 \
 --override ${PLATFORM}/smartLoader/kernel=Image \
 --override ${PLATFORM}/smartLoader/append=\"rdinit=/etc/init.d/rcS.bench\" \
 --override ${PLATFORM}/smartLoader/initrd=initrd.arm64.img \
 --override ${PLATFORM}/smartLoader/dtb=foundation-v8.dtb \
 \
 --override ${PLATFORM}/uart0/console=1 \
 --override ${PLATFORM}/uart1/console=1
 
