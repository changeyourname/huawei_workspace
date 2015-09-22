@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.ARM_CORTEX_M3-O1-g.elf ^
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv7-M ^
     --numprocessors 2 --hishare 0x000fffff --loshare 0x0   --parameter UAL=1 --parameter endian=little    %* 

:end
pause
