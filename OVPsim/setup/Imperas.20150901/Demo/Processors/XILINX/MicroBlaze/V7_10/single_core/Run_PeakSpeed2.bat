@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2_microblaze/peakSpeed2_microblaze.MICROBLAZE-O0-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_10 ^
     --numprocessors 1     --parameter endian=big     %*     -argv 300000000

:end
pause
