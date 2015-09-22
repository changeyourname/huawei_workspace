@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.CS_MIPS64-O1-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5Kf ^
     --numprocessors 2 --hishare 0x0001ffff --loshare 0x00000000   --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   %* 

:end
pause
