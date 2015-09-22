@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.CS_NIOS2-O1-g.elf ^
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S ^
     --numprocessors 2 --hishare 0x100fffff --loshare 0x00000000   --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    %* 

:end
pause
