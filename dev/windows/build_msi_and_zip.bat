call C:\"Program Files (x86)"\"Microsoft Visual Studio 12.0"\VC\vcvarsall.bat x86

set QTDIRS=bearer iconengines imageformats platforms printsupport sqldrivers
set QTLIBS=Qt5CLucene Qt5Core Qt5Gui Qt5Help Qt5Network Qt5PrintSupport Qt5Sql Qt5Widgets Qt5Xml

set ENGAUGE_CONFIG='pdf'
set QTLIBEXT='.lib'
set LOG4CPPDLLINK='https://dl.dropboxusercontent.com/u/1147076/log4cpp-1.1.1.zip'

set SCRIPTDIR=%cd%
set RESULTDIR="%SCRIPTDIR%\engauge-build"
mkdir "%RESULTDIR%"

rem Directory containing engauge.pro
set APPVEYOR_BUILD_FOLDER="%SCRIPTDIR%\..\.."

rem Nominal Qt installation is QTDIR="C:\Qt\5.6\msvc2013" or QTDIR="C:\Qt\5.7\msvc2013"
set PATH=%QTDIR%\bin;%PATH%

mkdir "%APPVEYOR_BUILD_FOLDER%"
cd "%APPVEYOR_BUILD_FOLDER%"
curl "%LOG4CPPDLLINK%" -o log4cpp-1.1.1.zip
7z x log4cpp-1.1.1.zip -aoa
mkdir fftw-3.3.4-dll32
cd fftw-3.3.4-dll32
curl 'ftp://ftp.fftw.org/pub/fftw/fftw-3.3.4-dll32.zip' -o fftw-3.3.4-dll32.zip
7z x fftw-3.3.4-dll32.zip -aoa
lib /def:libfftw3-3.def
lib /def:libfftw3f-3.def
lib /def:libfftw3l-3.def
mkdir include
mkdir lib
move fftw3.h include
move *dll lib
move *def lib
move *.lib lib
cd "%APPVEYOR_BUILD_FOLDER%"
curl 'https://dl.dropboxusercontent.com/u/1147076/poppler-qt5.zip' -o poppler-qt5.zip
7z x poppler-qt5.zip -aoa

cd "%APPVEYOR_BUILD_FOLDER%"
set LOG4CPP_HOME="%APPVEYOR_BUILD_FOLDER%\log4cpp-1.1.1"
set FFTW_HOME="%APPVEYOR_BUILD_FOLDER%\fftw-3.3.4-dll32"
set POPPLER_INCLUDE="%APPVEYOR_BUILD_FOLDER%\poppler-qt5\include\poppler\qt5"
set POPPLER_LIB="%APPVEYOR_BUILD_FOLDER%\poppler-qt5"
qmake engauge.pro "CONFIG+=%ENGAUGE_CONFIG%"
rem move Makefile Makefile.orig
rem ps: gc Makefile.orig | %{ $_ -replace '551.lib', %QTLIBEXT% } > Makefile
nmake

cd "%APPVEYOR_BUILD_FOLDER%"
mkdir "%RESULTDIR%"\documentation
for %%I in (%QTDIRS%) do mkdir "%RESULTDIR%\%%I" 
for %%I in (%QTDIRS%) do copy %QTDIR%\plugins\%%I\*.dll "%RESULTDIR%\%%I"
for %%I in (%QTLIBS%) do copy %QTDIR%\bin\%%I.dll "%RESULTDIR%"
del /S *d.dll
copy bin\engauge.exe "%RESULTDIR%"
copy log4cpp-1.1.1\lib\log4cpp.dll "%RESULTDIR%"
copy fftw-3.3.4-dll32\lib\libfftw3-3.dll "%RESULTDIR%"
copy "%APPVEYOR_BUILD_FOLDER%"\poppler-qt5\*.dll "%RESULTDIR%"
copy LICENSE "%RESULTDIR%"
cd "%APPVEYOR_BUILD_FOLDER%"\help
qcollectiongenerator engauge.qhcp -o engauge.qhc
move engauge.qch "%RESULTDIR%"\documentation
move engauge.qhc "%RESULTDIR%"\documentation
cd ..
7z a "%RESULTDIR%.7z" "%RESULTDIR%"
