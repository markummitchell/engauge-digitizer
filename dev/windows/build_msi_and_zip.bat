@echo off

rem Usage: build_msi_and_zip.bat <norelease>
rem
rem        Call this script from the Qt 5.6 shell
rem
rem Requirements: 1) Path set to point to:
rem                  vcvarsall.bat           Microsoft Visual Studio X/vc/bin, where X=12.0 (MSVC2012) and 14.0 (MSVC2015) work
rem                  candle.exe/light.exe    Wix Toolset
rem                  zip.exe                 Gnuwin32
rem                  curl.exe                cURL
rem                  7z.exe                  7-Zip
rem                  qmake                   Qt. Typical minimal setup is provided by setup_32bit.bat
rem               2) This does NOT need the fftw3 library to be installed first, since that is
rem                  downloaded and set up automatically by this script. The DLLs supplied by the creators are used
rem               3) This does need the log4cpp library. That is easily built using qmake (just like Engauge)

set ARG1=%1

call vcvarsall.bat x86

if not defined LOG4CPP_HOME (
   echo LOG4CPP_HOME must be set and pointing to log4cpp home directory
   exit /b 
)

if not defined QTDIR (
   echo QTDIR must be set and pointing to the Qt directory
   exit /b
)

set QTDIRS=bearer iconengines imageformats platforms printsupport sqldrivers
set QTLIBS=Qt5CLucene Qt5Core Qt5Gui Qt5Help Qt5Network Qt5PrintSupport Qt5Sql Qt5Widgets Qt5Xml

set ENGAUGE_CONFIG='pdf'
set QTLIBEXT='.lib'
set FFTWLINK="ftp://ftp.fftw.org/pub/fftw/fftw-3.3.4-dll32.zip"
set POPPLERLINK="https://dl.dropboxusercontent.com/u/1147076/poppler-qt5.zip"

set SCRIPTDIR=%cd%

rem Double-double quotes are needed in next line if the directory has a space
set RESULTDIR=""%SCRIPTDIR%\Engauge Digitizer""

rem Next step removes stale files like engauge.log from the release
if "%ARG1%" neq "norelease" (
  if exist "%RESULTDIR%" del /Q /F "%RESULTDIR%" 2>nul
)
if not exist "%RESULTDIR%" mkdir "%RESULTDIR%"

rem Directory containing engauge.pro
set APPVEYOR_BUILD_FOLDER="%SCRIPTDIR%\..\.."

if not exist "%APPVEYOR_BUILD_FOLDER%" mkdir "%APPVEYOR_BUILD_FOLDER%"
cd "%APPVEYOR_BUILD_FOLDER%"

curl "%FFTWLINK%" -o fftw-3.3.4-dll32.zip
curl "%POPPLERLINK%" -o poppler-qt5.zip

rem Nominal Qt installation is QTDIR="C:\Qt\5.6\msvc2013" or QTDIR="C:\Qt\5.7\msvc2013"
set PATH=%QTDIR%\bin;%PATH%

set FFTW_HOME=fftw-3.3.4-dll32
if not exist %FFTW_HOME% mkdir %FFTW_HOME%
cd %FFTW_HOME%

7z x ../fftw-3.3.4-dll32.zip -aoa
lib /def:libfftw3-3.def
lib /def:libfftw3f-3.def
lib /def:libfftw3l-3.def
if not exist include mkdir include
if not exist lib mkdir lib
move fftw3.h include
move *dll lib
move *def lib
move *.lib lib
cd "%APPVEYOR_BUILD_FOLDER%"

7z x poppler-qt5.zip -aoa

cd "%APPVEYOR_BUILD_FOLDER%"
set FFTW_HOME="%APPVEYOR_BUILD_FOLDER%\fftw-3.3.4-dll32"
set POPPLER_INCLUDE="%APPVEYOR_BUILD_FOLDER%\poppler-qt5\include\poppler\qt5"
set POPPLER_LIB="%APPVEYOR_BUILD_FOLDER%\poppler-qt5"
lrelease engauge.pro
qmake engauge.pro "CONFIG+=%ENGAUGE_CONFIG%" "DEFINES+=WIN_RELEASE"

if not exist bin mkdir bin

rem move Makefile Makefile.orig
rem ps: gc Makefile.orig | %{ $_ -replace '551.lib', %QTLIBEXT% } > Makefile
if "%ARG1%" neq "norelease" (
  nmake clean
)

rem Make sure the log4cpp library is built with debug info to prevent 'mismatch deteced for _ITERATOR_DEBUG_LEVEL'
nmake release

if not exist bin/engauge.exe (
  echo "Executable could not be built. Stopping"
  exit /b 1
)

cd "%APPVEYOR_BUILD_FOLDER%"
if not exist "%RESULTDIR%"\documentation mkdir "%RESULTDIR%"\documentation
for %%I in (%QTDIRS%) do (
  if not exist "%RESULTDIR%\%%I" mkdir "%RESULTDIR%\%%I"
)
for %%I in (%QTDIRS%) do copy %QTDIR%\plugins\%%I\*.dll "%RESULTDIR%\%%I"
for %%I in (%QTLIBS%) do copy %QTDIR%\bin\%%I.dll "%RESULTDIR%"
if exist *d.dll del /S *d.dll
copy bin\engauge.exe "%RESULTDIR%"

copy "%LOG4CPP_HOME%\lib\log4cpp.lib" "%RESULTDIR%"

copy fftw-3.3.4-dll32\lib\libfftw3-3.dll "%RESULTDIR%"
copy "%APPVEYOR_BUILD_FOLDER%"\poppler-qt5\*.dll "%RESULTDIR%"
copy LICENSE "%RESULTDIR%"
cd "%APPVEYOR_BUILD_FOLDER%"\help
qcollectiongenerator engauge.qhcp -o engauge.qhc
move engauge.qch "%RESULTDIR%"\documentation
move engauge.qhc "%RESULTDIR%"\documentation
cd ..

copy "%APPVEYOR_BUILD_FOLDER%"\translations "%RESULTDIR%"

if "%ARG1%" neq "norelease" (
  7z a "%RESULTDIR%.7z" "%RESULTDIR%"

  echo ***creating msi
  cd "%SCRIPTDIR%"
  findStr "char *VERSION_NUMBER" ..\..\src\util\Version.cpp
  findStr "Version=" engauge.wxs | findStr /v InstallerVersion
  echo *****************************************************************
  echo * Check the version numbers above. If they are not correct, enter
  echo * Control-C to exit. Otherwise, enter the version number below...
  echo *
  echo * CAUTION - Do not use the mouse wheel at this point or else the
  echo * entered number will be blank
  echo *****************************************************************
  set /p VERNUM="Version number seen above>"
  echo Version number will be %VERNUM%

  candle engauge.wxs
  candle WixUI_InstallDir_NoLicense.wxs
  light.exe -ext WixUIExtension -ext WixUtilExtension engauge.wixobj WixUI_InstallDir_NoLicense.wixobj -o "digit-exe-windows-32-bit-installer-%VERNUM%.msi"

  echo *** creating zip
  rem "Engauge Digitizer" in next line is needed since zip crashes on %RESULTDIR% due to the space
  zip -r "digit-exe-windows-32-bit-without-installer-file-%VERNUM%.zip" "Engauge Digitizer"
)
