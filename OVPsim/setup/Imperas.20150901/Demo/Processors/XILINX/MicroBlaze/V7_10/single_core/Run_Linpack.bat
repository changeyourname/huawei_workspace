@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack_microblaze/linpack_microblaze.MICROBLAZE-O0-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_10 ^
     --numprocessors 1     --parameter endian=big     %*     -argv 10

:end
pause
