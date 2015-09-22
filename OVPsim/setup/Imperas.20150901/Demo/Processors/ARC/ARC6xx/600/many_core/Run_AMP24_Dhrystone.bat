@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O0-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 ^
     --numprocessors 24     --parameter opt-rf16=0     %*     -argv 500000

:end
pause
