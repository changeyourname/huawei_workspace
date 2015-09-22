@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.POWERPC32-O1-g.elf ^
    --processorvendor power.ovpworld.org --processorname powerpc32 --variant mpc82x ^
    --gdbconsole --numprocessors 1     --parameter endian=big    --gdbinit dhrystone.gdb %* 

:end
pause
