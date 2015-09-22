@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS64-O0-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips64 --variant 5Kc ^
     --numprocessors 24     --parameter endian=big --semihostname mips64Newlib --semihostvendor mips.ovpworld.org   %*     -argv 800000

:end
pause
