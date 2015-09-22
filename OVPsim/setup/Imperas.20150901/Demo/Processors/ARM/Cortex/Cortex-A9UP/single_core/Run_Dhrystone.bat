@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_A-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A9UP ^
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 2000000

:end
pause
