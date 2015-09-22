@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.ARC700-O0-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 700 ^
     --numprocessors 1          %*     -argv 11

:end
pause
