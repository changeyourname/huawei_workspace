@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.CS_NIOS2-O0-g.elf ^
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S ^
     --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    %*     -argv 10

:end
pause
