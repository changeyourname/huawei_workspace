@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.MIPS32LE-O1-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA ^
     --numprocessors 1     --parameter endian=little     %*     -argv 11

:end
pause
