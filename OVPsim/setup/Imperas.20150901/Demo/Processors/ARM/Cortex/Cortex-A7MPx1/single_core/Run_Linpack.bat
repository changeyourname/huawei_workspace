@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.ARM_CORTEX_A-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A7MPx1 ^
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 11

:end
pause
