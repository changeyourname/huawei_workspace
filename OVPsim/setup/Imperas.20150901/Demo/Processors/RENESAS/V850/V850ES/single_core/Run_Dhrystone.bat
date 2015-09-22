@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O2-g.elf ^
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850ES ^
     --numprocessors 1          %*     -argv 10000000

:end
pause
