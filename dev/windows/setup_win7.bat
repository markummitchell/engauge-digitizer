@echo off

rem Variables must go BEFORE vcvarsall.bat which breaks all later SETs
set QTDIR=C:\Qt\5.6\msvc2015
set FFTW_HOME=%USERPROFILE%\fftw-3.3.4
set LOG4CPP_HOME=%USERPROFILE%\log4cpp_null

rem mingw
set PATH=/c/MinGW/bin;%QTDIR%/bin;%PATH%

rem PATH must point to .../Microsoft Visual Studio 14.0/vc/vcvarsall.bat
vcvarsall.bat
