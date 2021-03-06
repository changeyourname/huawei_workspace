@echo off
;rem Run_Fibonacci.bat

;rem move into the directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%
;rem Check Installation supports this demo
if EXIST ..\..\..\..\..\..\bin\%IMPERAS_ARCH%\checkinstall.exe (
  ..\..\..\..\..\..\bin\%IMPERAS_ARCH%\checkinstall.exe  --group run --noruntime -p install.pkg --nobanner
  if ERRORLEVEL 1 ( goto end )
)
%IMPERAS_ISS% --verbose --program ../../../Applications/fibonacci/fibonacci.AARCH32-O3-g.elf ^
    --processorvendor arm.ovpworld.org --processorname arm --variant AArch32 ^
     --numprocessors 1     --parameter compatibility=nopSVC --parameter UAL=1 --parameter endian=little   %*     -argv 39

:end
pause
