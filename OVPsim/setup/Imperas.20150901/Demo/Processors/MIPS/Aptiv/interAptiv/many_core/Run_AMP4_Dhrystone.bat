@echo off
;rem Run_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O3-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant interAptiv ^
     --numprocessors 4     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %*     -argv 4000000

:end
pause
