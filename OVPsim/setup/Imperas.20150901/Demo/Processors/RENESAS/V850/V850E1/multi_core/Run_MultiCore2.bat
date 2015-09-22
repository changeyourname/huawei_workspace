@echo off
;rem Run_MultiCore2.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/multicore2/multicore2.V850-O1-g.elf ^
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E1 ^
     --numprocessors 2 --hishare 0x0010ffff --loshare 0x00100000        %* 

:end
pause
