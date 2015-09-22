@echo off
;rem Debug_iGui_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O1-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_00 ^
    --gdbgui --numprocessors 1     --parameter endian=big    --gdbinit dhrystone_microblaze.gdb %* 

:end
pause
