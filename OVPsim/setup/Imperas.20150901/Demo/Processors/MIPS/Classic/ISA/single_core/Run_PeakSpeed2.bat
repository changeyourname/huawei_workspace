@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.MIPS32LE-O0-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA ^
     --numprocessors 1     --parameter endian=little     %*     -argv 100000000

:end
pause
