@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O2-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_00 ^
     --numprocessors 4     --parameter endian=big     %*     -argv 300000

:end
pause
