@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.ARM7-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant ARMv4T ^
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 39

:end
pause
