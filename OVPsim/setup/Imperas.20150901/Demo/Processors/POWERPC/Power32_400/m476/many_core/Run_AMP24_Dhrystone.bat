@echo off
;rem Run_AMP24_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O0-g.elf ^
    --processorvendor power.ovpworld.org --processorname powerpc32_400 --variant m476 ^
     --numprocessors 24     --parameter endian=big     %*     -argv 500000

:end
pause
