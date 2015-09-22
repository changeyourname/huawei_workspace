@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.CS_MIPS32-O1-g.elf ^
    --processorvendor imgtec.ovpworld.org --processorname mips32 --variant P5600 ^
     --numprocessors 2 --hishare 0x01ffff --loshare 0x0  --semihostname mips32Newlib --semihostvendor mips.ovpworld.org --addressbits 37  --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %* 

:end
pause
