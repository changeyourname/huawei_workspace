@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O1-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 0x32 ^
    --gdbconsole --numprocessors 1         --gdbinit dhrystone.gdb %* 

:end
pause
