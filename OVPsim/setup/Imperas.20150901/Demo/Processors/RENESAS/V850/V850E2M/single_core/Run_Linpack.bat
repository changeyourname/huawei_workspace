@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.V850-O2-g.elf ^
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2M ^
     --numprocessors 1          %*     -argv 11

:end
pause
