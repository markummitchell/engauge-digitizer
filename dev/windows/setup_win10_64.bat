@echo off

rem Variables must go BEFORE vcvars32.bat which breaks all later SETs
set QTDIR=C:\Qt64\5.6\msvc2013_64
set FFTW_HOME=%USERPROFILE%\fftw-3.3.4
set LOG4CPP_HOME=%USERPROFILE%\log4cpp_null

rem mingw
set PATH=%QTDIR%/bin;%PATH%

rem PATH must point to .../Microsoft Visual Studio 14.0/vc/vcvars32.bat
vcvarsall.bat
