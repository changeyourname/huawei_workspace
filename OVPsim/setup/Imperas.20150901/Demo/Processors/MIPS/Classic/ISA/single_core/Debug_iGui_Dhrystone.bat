@echo off
;rem Debug_iGui_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.MIPS32LE-O1-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant ISA ^
    --gdbgui --numprocessors 1     --parameter endian=little    --gdbinit dhrystone.gdb %* 

:end
pause
