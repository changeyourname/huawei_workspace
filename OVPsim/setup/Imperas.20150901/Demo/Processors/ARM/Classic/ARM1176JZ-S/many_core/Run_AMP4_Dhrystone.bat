@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM9-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM1176JZ-S ^
     --numprocessors 4     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 1000000

:end
pause
