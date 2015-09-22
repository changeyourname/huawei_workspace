@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.CS_MIPS64-O3-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5Kf ^
     --numprocessors 1     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   %*     -argv 39

:end
pause
