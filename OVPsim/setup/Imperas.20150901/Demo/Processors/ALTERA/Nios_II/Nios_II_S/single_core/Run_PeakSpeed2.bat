@echo off
;rem Run_PeakSpeed2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/peakSpeed2/peakSpeed2.CS_NIOS2-O0-g.elf ^
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S ^
     --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    %*     -argv 500000000

:end
pause
