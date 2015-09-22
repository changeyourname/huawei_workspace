@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O2-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA ^
     --numprocessors 4     --parameter endian=little     %*     -argv 1000000

:end
pause
