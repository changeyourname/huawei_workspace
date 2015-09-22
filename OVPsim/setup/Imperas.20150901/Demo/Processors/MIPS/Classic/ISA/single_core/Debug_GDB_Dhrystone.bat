@echo off
;rem Debug_GDB_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O1-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA ^
    --gdbconsole --numprocessors 1     --parameter endian=little    --gdbinit dhrystone.gdb %* 

:end
pause
