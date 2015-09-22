@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.CS_MIPS32-O3-g.elf ^
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 ^
     --numprocessors 1 --addressbits 37    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %*     -argv 39

:end
pause
