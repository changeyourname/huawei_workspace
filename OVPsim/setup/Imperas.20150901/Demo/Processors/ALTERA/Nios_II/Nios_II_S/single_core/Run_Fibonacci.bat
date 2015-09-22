@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.CS_NIOS2-O3-g.elf ^
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S ^
     --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    %*     -argv 39

:end
pause
