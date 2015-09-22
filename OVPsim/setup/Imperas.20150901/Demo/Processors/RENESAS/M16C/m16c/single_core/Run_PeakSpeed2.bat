@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed1_m16c/peakSpeed1_m16c.M16C-O0-g.elf ^
    --processorvendor posedgesoft.ovpworld.org --processorname m16c --variant m16c ^
     --numprocessors 1          %*     -argv 10000000

:end
pause
