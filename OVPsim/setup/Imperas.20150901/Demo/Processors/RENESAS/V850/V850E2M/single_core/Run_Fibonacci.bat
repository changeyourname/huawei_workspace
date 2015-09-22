@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.V850-O3-g.elf ^
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2M ^
     --numprocessors 1          %*     -argv 39

:end
pause
