@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.OR1K-O0-g.elf ^
    --processorvendor ovpworld.org --processorname or1k --variant generic ^
     --numprocessors 1          %*     -argv 300000000

:end
pause
