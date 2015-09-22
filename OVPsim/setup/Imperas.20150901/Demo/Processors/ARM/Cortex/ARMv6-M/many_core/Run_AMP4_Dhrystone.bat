@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M0-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname armm --variant ARMv6-M ^
     --numprocessors 4     --parameter UAL=1 --parameter endian=little    %*     -argv 300000

:end
pause
