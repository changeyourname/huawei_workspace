@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32LE-O3-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 24KEf ^
     --numprocessors 24     --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %*     -argv 800000

:end
pause
