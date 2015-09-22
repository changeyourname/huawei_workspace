@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.ARC600-O1-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 600 ^
     --numprocessors 1     --parameter opt-rf16=0     %*     -argv 11

:end
pause
