@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M3-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M3 ^
     --numprocessors 1     --parameter UAL=1 --parameter endian=little    %*     -argv 600000

:end
pause
