@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci_microblaze/fibonacci_microblaze.MICROBLAZE-O3-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V8_20 ^
     --numprocessors 1     --parameter endian=big     %*     -argv 39

:end
pause
