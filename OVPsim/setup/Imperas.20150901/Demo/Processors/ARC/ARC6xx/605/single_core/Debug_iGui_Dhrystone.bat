@echo off
;rem Debug_iGui_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARC600-O1-g.elf ^
    --processorvendor arc.ovpworld.org --processorname arc --variant 605 ^
    --gdbgui --numprocessors 1         --gdbinit dhrystone.gdb %* 

:end
pause
