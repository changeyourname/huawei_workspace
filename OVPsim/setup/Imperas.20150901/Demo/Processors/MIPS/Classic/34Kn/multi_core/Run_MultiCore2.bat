@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.CS_MIPS32LE-O1-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant 34Kn ^
     --numprocessors 2 --hishare 0x01ffff --loshare 0x0   --parameter endian=little --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %* 

:end
pause
