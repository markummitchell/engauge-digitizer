rem Usage: build_msi_and_zip.bat <norelease>

set ARG1=%1

call C:\"Program Files (x86)"\"Microsoft Visual Studio 12.0"\VC\vcvarsall.bat x86

set QTDIRS=bearer iconengines imageformats platforms printsupport sqldrivers
set QTLIBS=Qt5CLucene Qt5Core Qt5Gui Qt5Help Qt5Network Qt5PrintSupport Qt5Sql Qt5Widgets Qt5Xml

set ENGAUGE_CONFIG='pdf'
set QTLIBEXT='.lib'
set LOG4CPPDLLINK="https://dl.dropboxusercontent.com/s/gyqcfg2xpm4jjby/log4cpp_null.zip"
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

curl "%LOG4CPPDLLINK%" -o log4cpp_null.zip
curl "%FFTWLINK%" -o fftw-3.3.4-dll32.zip
curl "%POPPLERLINK%" -o poppler-qt5.zip

rem Nominal Qt installation is QTDIR="C:\Qt\5.6\msvc2013" or QTDIR="C:\Qt\5.7\msvc2013"
set PATH=%QTDIR%\bin;%PATH%

7z x log4cpp_null.zip -aoa

if not exist fftw-3.3.4-dll32 mkdir fftw-3.3.4-dll32
cd fftw-3.3.4-dll32

7z x fftw-3.3.4-dll32.zip -aoa
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
rem move Makefile Makefile.orig
rem ps: gc Makefile.orig | %{ $_ -replace '551.lib', %QTLIBEXT% } > Makefile
if "%ARG1%" neq "norelease" (
  nmake clean
)
nmake

cd "%APPVEYOR_BUILD_FOLDER%"
if not exist "%RESULTDIR%"\documentation mkdir "%RESULTDIR%"\documentation
for %%I in (%QTDIRS%) do (
  if not exist "%RESULTDIR%\%%I" mkdir "%RESULTDIR%\%%I"
)
for %%I in (%QTDIRS%) do copy %QTDIR%\plugins\%%I\*.dll "%RESULTDIR%\%%I"
for %%I in (%QTLIBS%) do copy %QTDIR%\bin\%%I.dll "%RESULTDIR%"
del /S *d.dll
copy bin\engauge.exe "%RESULTDIR%"

copy "%APPVEYOR_BUILD_FOLDER%\log4cpp_null\lib\log4cpp.dll" "%RESULTDIR%"

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
  set /p VERNUM="If the version numbers are correct, enter the version number seen above to continue and build releases>"
  echo "Version number will be %VERNUM%"

  candle engauge.wxs
  candle WixUI_InstallDir_NoLicense.wxs
  light.exe -ext WixUIExtension -ext WixUtilExtension engauge.wixobj WixUI_InstallDir_NoLicense.wixobj -o "digit-exe-windows-32-bit-installer-%VERNUM%.msi"

  echo *** creating zip
  rem "Engauge Digitizer" in next line is needed since zip crashes on %RESULTDIR% due to the space
  zip -r "digit-exe-windows-32-bit-without-installer-file-%VERNUM%.zip" "Engauge Digitizer"
)
