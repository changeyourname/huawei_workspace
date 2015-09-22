@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.OR1K-O1-g.elf ^
    --processorvendor ovpworld.org --processorname or1k --variant generic ^
    --gdbconsole --numprocessors 1         --gdbinit dhrystone.gdb %* 

:end
pause
