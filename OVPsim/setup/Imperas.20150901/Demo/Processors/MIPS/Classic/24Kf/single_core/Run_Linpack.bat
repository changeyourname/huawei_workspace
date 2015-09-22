@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.CS_MIPS32LE-O0-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 24Kf ^
     --numprocessors 1     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %*     -argv 10

:end
pause
