@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.V850-O1-g.elf ^
    --processorvendor renesas.ovpworld.org --processorname v850 --variant V850E2M ^
    --gdbconsole --numprocessors 1         --gdbinit dhrystone.gdb %* 

:end
pause
