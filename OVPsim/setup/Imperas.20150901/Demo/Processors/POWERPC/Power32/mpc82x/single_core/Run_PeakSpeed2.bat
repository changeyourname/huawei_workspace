@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.POWERPC32-O0-g.elf ^
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x ^
     --numprocessors 1     --parameter endian=big     %*     -argv 500000000

:end
pause
