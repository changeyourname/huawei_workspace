@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.POWERPC32-O0-g.elf ^
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 ^
     --numprocessors 1     --parameter endian=big     %*     -argv 8

:end
pause
