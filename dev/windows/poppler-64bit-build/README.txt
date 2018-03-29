
Building the Poppler Library, and the Libraries It Depends On, In Windows (64 Bit)

1. Install Visual Studio 2015
2. >set PBBUILD=<root>\engauge-digitizer\dev\windows\poppler-64bit-build
3. >set PBLIBS=<root>\engauge-digitizer\dev\windows\poppler-64bit-libs
4. Download and install nasm=-2.14rc0-installer-x64.exe
   a. Add directory containing nasm.exe to PATH
5. Install the yasm assembler into Visual Studio 2015 according to steps at 
   https://www.tortall.net/projects/yasm/manual/html/vsyasm.html 
6. Extract the following into %PBBUILD% (with version numbers recommended by 
   http://www.linuxfromscratch.org/blfs/view/cvs/general/poppler.html):
   a. Cmake-3.8.0-win64-x64.msi (creates solution files for visual studio)
   b. Fontconfig-master.zip (from github/ShiftMediaProject/fontconfig which has a Windows 
      solution file. For poppler)
   c. Freetype-2.9.tar.gz (for fontconfig)
   d. Libiconv-win-build.zip (from github/kiyolee/libconv-win-build. Optional for fontconfig)
   e. Libjpeg-turbo-1.5.3.tar.gz (for poppler)
   f. Libpng-1.6.34.tar.gz (for poppler)
   g. Libxml2-2.9.4.tar.gz (for fontconfig)
   h. Openjpeg-2.3.0.tar.gz (for poppler)
   i. Poppler-0.62.0.tar.xz
   j. Zlib-1.2.8.tar.gz (for libpng)
7. For cmake
   a. Run the cmake-3.8.0-win64-x64.msi
   b. Put cmake.exe into PATH in Control Panel / System / Advanced Settings / Environment Variables
8. For openjpeg,
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD%/openjpeg-0.62.0
   c. >mkdir build
   d. >cd build
   e. >cmake ..
   f. Start "Visual Studio 2015"
   g. File / Open / Project Solution
   h. <PBBUILD>/openjpeg-0.62.0/build/ALL-BUILD.sln
   i. Change dropdown at top from Debug to Release
   j. Select "Solution OPENJPEG" in Solution Explorer window
   k. Build / Build Solution (creates files in openjpeg-0.62.0/build/bin/Release)
9. For zlib
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD%/zlib-1.2.8
   c. >mkdir build
   d. >cd build
   e. >cmake ..
   f. Start "Visual Studio 2015"
   g. File / Open / Project Solution
   h. Change dropdown at top from Debug to Release
   i. <PBBUILD>/openjpeg-0.62.0/build/ALL-BUILD.sln
   j. Select zlib in Solution Explorer window
   k. Build / Build Solution (creates files in zlib-1.2.8/build/Release)
10. For libpng
   a. Start "Visual Studio 2015"
   b. File / Open / Project Solution
   c. <PBBUILD>/libpng-1.6.34/projects/vstudio/vstudio.sln
   d. Change dropdown at top from Debug to Release
   e. Build zlib:
         i. Select "zlib" in Solution Explorer
        ii. Right click on "zlib" and select "Properties"
       iii. Select "VC++ Directories"
        iv. Select "Include Directories"
         v. Select "arrow down" button to the right of "Include Directories"
        vi. Select "<Edit>"
       vii. Select "New Line" button which looks like a yellow folder with a yellow asterisk on it
      viii. Select "..." to select a directory
        ix. Select "<PBBUILD>/zlib-1.2.8/build"
         x. Select "Select Folder" button
        xi. Select "Ok" button
       xii. Select "Ok" button
      xiii. Right click on "zlib" in Solution Explorer and pick "Build". This builds zlib.lib
   f. Build libpng:
         i. Select "libpng" in Solution Explorer
        ii. Right click on "libpng" and select "Properties"
       iii. Select "VC++ Directories"
        iv. Select "Include Directories"
         v. Select "arrow down" button to the right of "Include Directories"
        vi. Select "<Edit>"
       vii. Select "New Line" button which looks like a yellow folder with a yellow asterisk on it
      viii. Select "..." to select a directory
        ix. Select "<PBBUILD>/zlib-1.2.8/build"
         x. Select "Select Folder" button
        xi. Select "Ok" button
       xii. Select "Ok" button
      xiii. Right click on "libpng" in Solution Explorer and pick "Build". This builds libpng16.dll
11. For libjpeg-turbo
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD%/libjpeg-turbo-1.5.3
   c. Edit simd/CMakeLists.txt
         i. Comment out the "if (NOT DEFINED NASM)" line and its corresponding "endif()" line, 
            then save the file. This is required since coming into this script NASM=NASM-NOTFOUND
            so find_program never searches for NASM)
   d. >mkdir build
   e. >cd build
   f. (Before continuing, make sure NASM is installed and NASM.exe is on the PATH, so CMake knows 
      how to build jsimdcpu.asm)
   g. >cmake .. (if you see the line NASM=NASM-NOTFOUND then NASM was not properly installed or the 
      simd/CMakeLists.txt file was not correctly edited). Note that simd/CMakeLists.txt is doing 
      the search for nasm, then yasm)
   h. Start "Visual Studio 2015"
   i. File / Open / Project Solution
   j. <PBBUILD>/libjpeg-turbo-1.5.3/build/libjpeg-turbo.sln
   k. Change dropdown at top from Debug to Release
   l. Right click on ALL_BUILD/simd/CMakeRules/jsimdcpu.obj.rule in Solution Explorer window
   m. Select Properties
   n. Select General
   o. Edit co
   p. Select "Solution ‘ALL_BUILD" in Solution Explorer window
   q. Build / Build Solution (creates files in libjpeg-turbo-1.5.3/build/Release and 
                              libjpeg-turbo-1.5.3/build/sharedlib/Release)
12. For freetype
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution
   c. Freetype-2.9 / builds / win32 / vc2010
   d. Change dropdown at top from Debug to Release
   e. Right click on freetype in Solution Explorer window
   f. Properties
   g. Make sure Configuration dropdown at top says Release
   h. Build (creates freetype-2.9 / objs /win32 / vc2010 / Release / freetype.lib and freetype.dll)
   i. >cd objs / win32 / vc2010 / Release
   j. >copy freetype.lib libfreetype.lib (expected by fontconfig)
13. For libiconv-win-build
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution
   c. Libiconv-win-build-master / build-VS2015 / libiconv.sln
   d. Change dropdown at top from Debug to Release
   e. Select dll / libiconv in Solution Explorer window and select BUILD (builds build-VS2015 / 
      Release / libiconv.dll)
   f. Select static / libiconv-static in Solution Explorer window and select Build (builds 
      build-VS2015 / Release / libiconv.lib)
   g. >cd build-VS2015 / Release
   h. >copy libiconv.lib iconv.lib (filename expected by libxml2)
14. For libxml2 we use nmake, since the Visual Studio project file is broken. Following 
    http://marlowa.blogspot.com/2013/07/how-to-build-libxml2-on-windows-using.html
   a. start Qt 64 bit window for VS 2015
   b. set PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC:%PATH%
   c. set PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin:%PATH%
   d. set PATH=%PBBUILD%\libiconv-win-build-master\build-VS2015\Debug:%PATH%
   e. >cd win32
   f. >cscript configure.js compiler=msvc include=%PBBUILD%\libiconv-win-build-master\include
      lib=%PBBUILD%\libiconv-win-build-master\build-vs2015\debug debug=no (this creates file config.msvc)
   g. edit file Makefile.msvc
   h. After line "CFLAGS=$(CFLAGS) /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATED", add the 
      line "CFLAGS=$(CFLAGS) /D_SECURE_SCL=0 /D_SCL_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_DEPRECATE"
   i. Save file and exit editor
   j. >vcvarsall.bat
   k. >nmake (this creates win32/bin.msvc/libxml2.dll and libxml2.lib)
15. For fontconfig (using ShiftMediaSolution release with its support for Windows)
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution 
   c. Fontconfig-master / SMP / libfontconfig.sln
   d. Change dropdown at top from Debug to Release
   e. Right click on libfontconfig in Solution Explorer window
   f. Properties
   g. Make sure Configuration dropdown at top says Release
   h. General
         i. Output Directory
        ii. change from $(ProjectDir)..\..\..\msvc\ to $(ProjectDir)\msvsc\
   i. C/C++
         i. Additional Include Directories
        ii. add path to <PBBUILD>/freetype-2.9/include
       iii. add path to <PBBUILD>/libiconv-win-build-master/include
        iv. add path to <PBBUILD>/libxml2-2.9.7/include
         v. Right click on libconfig in Solution Explorer window
   j. VC++ Directories
         i. Library Directories
        ii. add <PBBUILD>/libiconv-win-build-master/build-VS2015/Release
       iii. add <PBBUILD>/freetype-2.9/objs/Win32/Release
        iv. add <PBBUILD>/libxml2-2.9.7/win32/bin.msvc
   k. Build (creates SMP/msvc/lib/x64/libfontconfig.lib)
16. For poppler
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD%/poppler-0.62.0
   c. edit CMakeLists.txt and add 'SET (LIBOPENJPEG2_FOUND TRUE)' after the 'find_package (LIBOPENJPEG2)'
      line. This is needed since cmake's find_package algorithm will not find a package file that is not
      needed for this build
   d. edit the following files and change 'strtok_r' to 'strtok_s':
         fofi/FoFiType1.cc
         poppler/CharCodeToUnicode.cc
         poppler/GlobalParams.cc
         poppler/PDFDoc.cc
         poppler/UnicodeMap.cc
   e. >mkdir build
   f. >cd build
   g. >set FREETYPE_INCLUDE_DIRS="%PBBUILD%\freetype-2.9\include; %PBBUILD%\freetype-2.9\include\freetype"
   h. >set FREETYPE_LIBRARY="%PBBUILD%\freetype-2.9\objs\Win32\Release\freetype.lib"
   i. >set ICONV_LIBRARY="%PBBUILD%\libiconv-win-build-master\build-VS2015\Release\libiconv.lib"
   j. >set JPEG_INCLUDE_DIR="%PBBUILD%\libjpeg-turbo-1.5.3"
   k. >set JPEG_LIBRARY="%PBBUILD%\libjpeg-turbo-1.5.3\build\Release\jpeg-static.lib"
   l. >set LIBOPENJPEG2_INCLUDE_DIR="%PBBUILD%\openjpeg-2.3.0\src\lib\openjp2"
   m. >set LIBOPENJPEG2_LIBRARY="%PBBUILD%\openjpeg-2.3.0\build\bin\Release\openjp2.lib"
   n. >set PNG_INCLUDE_DIR="%PBBUILD%\libpng-1.6.34"
   o. >set PNG_LIBRARY="%PBBUILD%\libpng-1.6.34\projects\vstudio\Release\libpng16.lib"
   p. >set ZLIB_INCLUDE_DIR="%PBBUILD%"
   q. >set ZLIB_LIBRARY="%PBBUILD%\zlib-1.2.8\build\Release\zlib.lib"
   r. >cmake .. -DFREETYPE_INCLUDE_DIRS=%FREETYPE_INCLUDE_DIRS% -DFREETYPE_LIBRARY=%FREETYPE_LIBRARY% -DICONV_LIBRARIES=%ICONV_LIBRARY% -DJPEG_INCLUDE_DIR=%JPEG_INCLUDE_DIR% -DJPEG_LIBRARY=%JPEG_LIBRARY% -DLIBOPENJPEG2_INCLUDE_DIRS=%LIBOPENJPEG2_INCLUDE_DIR% -DLIBOPENJPEG2_LIBRARIES=%LIBOPENJPEG2_LIBRARY% -DPNG_PNG_INCLUDE_DIR=%PNG_INCLUDE_DIR% -DPNG_LIBRARY=%PNG_LIBRARY% -DZLIB_INCLUDE_DIR=%ZLIB_INCLUDE_DIR% -DZLIB_LIBRARY=%ZLIB_LIBRARY%
      (note there are several unexpected spellings!)
   s. Start "Visual Studio 2015"
   t. File / Open / ProjectSolution 
   u. poppler-0.62.0\build\poppler.sln
   v. Change dropdown at top from Debug to Release
   w. Right click on poppler in Solution Explorer window
         i. Properties
        ii. Select "VC++ Directories"
       iii. Select "Include Directories"
        iv. Select "arrow down" button to the right of "Include Directories"
         v. Select "<Edit>"
        vi. Add <PBBUILD>\freetype-2.9\include
       vii. Add <PBBUILD>\libjpeg-turbo-1.5.3\build
      viii. Add <PBBUILD>\openjpeg-2.3.0\build\src\lib\openjp2
        ix. Add <PBBUILD>\zlib-1.2.8\
         x. Add <PBBUILD>\zlib-1.2.8\build
        xi. Build (this creates build\Release\poppler.lib)
   x. Right click on poppler-qt5 in Solution Explorer window
         i. Properties
        ii. Select "VC++ Directories"
       iii. Select "Include Directories"
        iv. Select "arrow down" button to the right of "Include Directories"
         v. Select "<Edit>"
        vi. Add <PBBUILD>\freetype-2.9\include
       vii. Add <PBBUILD>\libjpeg-turbo-1.5.3\build
      viii. Add <PBBUILD>\openjpeg-2.3.0\build\src\lib\openjp2
        ix. Add <PBBUILD>\zlib-1.2.8\
         x. Add <PBBUILD>\zlib-1.2.8\build
        xi. Build (this creates build\qt5/src/Release\poppler-qt5.lib)
17. Copy *.lib files to ../poppler-64bit-libs/lib
18. To build with poppler:
   a. set FFTW_HOME=%PBBUILD%\..\unzip_fftw\lib64
   b. set LOG4CPP_HOME=%PBBUILD%\..\unzip_log4cpp\lib
   b. set POPPLER_INCLUDE=<PBBUILD>\include
   c. set POPPLER_LIB=<PBBUILD>\lib
   c. vcvarsall amd64
   d. qmake CONFIG+=pdf engauge.pro
   e. nmake
