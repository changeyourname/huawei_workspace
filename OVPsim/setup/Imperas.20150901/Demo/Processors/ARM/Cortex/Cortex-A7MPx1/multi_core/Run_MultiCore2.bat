@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.ARM_CORTEX_A-O1-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant Cortex-A7MPx1 ^
     --numprocessors 2 --hishare 0x000fffff --loshare 0x0   --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %* 

:end
pause
