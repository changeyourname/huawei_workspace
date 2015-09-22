@echo off

;rem move into the Example Directory
set BATCHDIR=%~dp0%
cd /d %BATCHDIR%

;rem Check Installation supports this demo
if EXIST ..\..\..\bin\%IMPERAS_ARCH%\checkinstall.exe (
  ..\..\..\bin\%IMPERAS_ARCH%\checkinstall.exe -p install.pkg --nobanner
  if ERRORLEVEL 1 (
    pause
    exit
  )
)

set CROSS=OR1K

mingw32-make -C application CROSS=%CROSS%
mingw32-make -C platform


platform\platform.%IMPERAS_ARCH%.exe --program application\application.%CROSS%.elf

pause
