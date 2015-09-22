@echo off
;rem Run_Linpack.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/linpack/linpack.OR1K-O0-g.elf ^
    --processorvendor ovpworld.org --processorname or1k --variant generic ^
     --numprocessors 1          %*     -argv 8

:end
pause
