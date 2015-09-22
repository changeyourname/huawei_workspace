@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_MIPS64-O0-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5KEc ^
     --numprocessors 1     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   %*     -argv 500000000

:end
pause
