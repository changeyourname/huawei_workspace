@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O0-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 ^
     --numprocessors 4          %*     -argv 1000000

:end
pause
