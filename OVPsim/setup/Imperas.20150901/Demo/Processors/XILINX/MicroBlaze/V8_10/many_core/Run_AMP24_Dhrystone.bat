@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O2-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_10 ^
     --numprocessors 24     --parameter endian=big     %*     -argv 800000

:end
pause
