@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.ARC600-O0-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 ^
     --numprocessors 1          %*     -argv 500000000

:end
pause