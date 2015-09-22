@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.ARC700-O2-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 ^
     --numprocessors 1          %*     -argv 36

:end
pause
