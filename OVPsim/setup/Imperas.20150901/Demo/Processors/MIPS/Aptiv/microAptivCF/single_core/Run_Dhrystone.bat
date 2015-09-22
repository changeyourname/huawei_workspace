@echo off
;rem Run_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_UMIPS-O3-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant microAptivCF ^
     --numprocessors 1     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %*     -argv 10000000

:end
pause
