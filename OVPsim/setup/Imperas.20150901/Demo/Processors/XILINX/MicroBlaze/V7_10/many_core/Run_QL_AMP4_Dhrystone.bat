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
%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone_microblaze/dhrystone_microblaze.MICROBLAZE-O2-g.elf ^
    --processorvendor xilinx.ovpworld.org --processorname microblaze --variant V7_10 ^
    --parallel --numprocessors 4     --parameter endian=big     %*     -argv 4000000

:end
pause
