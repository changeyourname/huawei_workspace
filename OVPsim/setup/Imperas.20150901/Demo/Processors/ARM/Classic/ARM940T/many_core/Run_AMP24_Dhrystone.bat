@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM9-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM940T ^
     --numprocessors 24     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 500000

:end
pause
