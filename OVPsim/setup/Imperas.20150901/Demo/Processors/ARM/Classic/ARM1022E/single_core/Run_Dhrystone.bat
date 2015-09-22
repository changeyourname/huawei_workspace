@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM9-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM1022E ^
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 6000000

:end
pause
