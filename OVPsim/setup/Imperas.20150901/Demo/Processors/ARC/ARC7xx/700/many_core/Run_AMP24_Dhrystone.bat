@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC700-O2-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 ^
     --numprocessors 24          %*     -argv 800000

:end
pause
