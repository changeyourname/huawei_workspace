@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.ARM_CORTEX_M0-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M0plus ^
     --numprocessors 1     --parameter UAL=1 --parameter endian=little    %*     -argv 8

:end
pause
