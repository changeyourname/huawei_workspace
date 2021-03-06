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
%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.ARM9-O0-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant ARM968E-S ^
    --parallel --numprocessors 4     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %* --parallelmax    -argv 1000000

:end
pause
