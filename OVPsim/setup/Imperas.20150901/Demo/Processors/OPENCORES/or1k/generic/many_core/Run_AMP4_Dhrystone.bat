@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.OR1K-O3-g.elf ^
    --processorvendor ovpworld.org --processorname or1k --variant generic ^
     --numprocessors 4          %*     -argv 300000

:end
pause
