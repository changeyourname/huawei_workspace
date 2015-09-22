@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O2-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 605 ^
     --numprocessors 1          %*     -argv 10000000

:end
pause
