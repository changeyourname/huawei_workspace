@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_MIPS32-O0-g.elf ^
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 ^
     --numprocessors 1 --addressbits 37    --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %*     -argv 100000000

:end
pause
