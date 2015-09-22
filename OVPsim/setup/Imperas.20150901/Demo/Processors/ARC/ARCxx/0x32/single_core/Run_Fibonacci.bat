@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.ARC600-O3-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 ^
     --numprocessors 1          %*     -argv 39

:end
pause
