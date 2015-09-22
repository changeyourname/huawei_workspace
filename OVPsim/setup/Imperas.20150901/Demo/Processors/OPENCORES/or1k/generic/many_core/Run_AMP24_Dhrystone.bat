@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.OR1K-O3-g.elf ^
    --processorvendor ovpworld.org --processorname or1k --variant generic ^
     --numprocessors 24          %*     -argv 800000

:end
pause
