@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci_m16c/fibonacci_m16c.M16C-O2-g.elf ^
    --processorvendor posedgesoft.ovpworld.org --processorname m16c --variant m16c ^
     --numprocessors 1          %*     -argv 30

:end
pause
