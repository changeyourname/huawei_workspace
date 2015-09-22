@echo off
;rem Debug_iGui_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM_CORTEX_M0-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname armm --variant Cortex-M1 ^
    --gdbgui --numprocessors 1     --parameter UAL=1 --parameter endian=little   --gdbinit dhrystone.gdb %* 

:end
pause
