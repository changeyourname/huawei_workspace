@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.V850-O0-g.elf ^
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2R ^
     --numprocessors 1          %*     -argv 300000000

:end
pause
