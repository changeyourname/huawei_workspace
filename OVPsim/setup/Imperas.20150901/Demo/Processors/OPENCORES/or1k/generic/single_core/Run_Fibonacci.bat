@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.OR1K-O3-g.elf ^
    --processorvendor ovpworld.org --processorname or1k --variant generic ^
     --numprocessors 1          %*     -argv 36

:end
pause
