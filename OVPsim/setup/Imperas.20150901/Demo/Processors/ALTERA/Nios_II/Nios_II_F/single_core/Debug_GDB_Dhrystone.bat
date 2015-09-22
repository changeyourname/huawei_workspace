@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O1-g.elf ^
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_F ^
    --gdbconsole --numprocessors 1     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1   --gdbinit dhrystone.gdb %* 

:end
pause
