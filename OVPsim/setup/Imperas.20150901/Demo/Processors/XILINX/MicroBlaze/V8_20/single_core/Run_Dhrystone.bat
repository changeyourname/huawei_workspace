@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_20 ^
     --numprocessors 1     --parameter endian=big     %*     -argv 10000000

:end
pause
