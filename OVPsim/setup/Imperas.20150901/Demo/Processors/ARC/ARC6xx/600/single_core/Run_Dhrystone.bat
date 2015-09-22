@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O2-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 ^
     --numprocessors 1     --parameter opt-rf16=0     %*     -argv 6000000

:end
pause
