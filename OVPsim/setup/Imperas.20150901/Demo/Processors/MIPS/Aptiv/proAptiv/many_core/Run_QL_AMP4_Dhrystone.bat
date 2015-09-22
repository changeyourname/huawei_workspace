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
%IMPERAS_ISS% --verbose --program ../../../Applications/dhrystone/dhrystone.CS_MIPS32-O3-g.elf ^
    --processorvendor mips.ovpworld.org --processorname mips32 --variant proAptiv ^
    --parallel --numprocessors 4     --parameter endian=big --semihostname mips32Newlib --semihostvendor mips.ovpworld.org   %* --parallelmax    -argv 4000000

:end
pause
