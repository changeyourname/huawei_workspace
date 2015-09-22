@echo off
;rem Run_QL_AMP4_Dhrystone.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%
;rem Check Installation supports this demo
if EXIST ..\..\..\..\..\..\bin\%IMPERAS_ARCH%\checkinstall.exe (
  ..\..\..\..\..\..\bin\%IMPERAS_ARCH%\checkinstall.exe  --group run --noruntime -p install.pkg --nobanner
  if ERRORLEVEL 1 ( goto end )
)
%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_NIOS2-O1-g.elf ^
    --processorvendor altera.ovpworld.org --processorname nios_ii --variant Nios_II_S ^
    --parallel --numprocessors 4     --parameter HW_DIVIDE=1 --parameter HW_MULTIPLY=1    %*     -argv 4000000

:end
pause
