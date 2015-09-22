@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M3-O1-g.elf ^
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M4 ^
    --gdbconsole --numprocessors 1     --parameter UAL=1 --parameter endian=little   --gdbinit dhrystone.gdb %* 

:end
pause
