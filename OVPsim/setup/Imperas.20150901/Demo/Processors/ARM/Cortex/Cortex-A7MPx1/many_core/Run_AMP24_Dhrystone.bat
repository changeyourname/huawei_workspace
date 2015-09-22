@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_A-O1-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A7MPx1 ^
     --numprocessors 24     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 800000

:end
pause
