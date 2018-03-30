
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
   e. >cmake -G "Visual Studio 14 2015 Win64" ..
   f. Start "Visual Studio 2015"
   g. File / Open / Project Solution
   h. <PBBUILD>/openjpeg-0.62.0/build/OPENJPEG.sln
   i. Change dropdown at top from Debug to Release
   j. Verify other dropdown at top says x64
   k. Select "ALL_BUILD" in Solution Explorer window
   l. Build / Build Solution (creates files in openjpeg-0.62.0/build/bin/Release)
9. For zlib
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD%/zlib-1.2.8
   c. >mkdir build
   d. >cd build
   e. >cmake -G "Visual Studio 14 2015 Win64" ..
   f. Start "Visual Studio 2015"
   g. File / Open / Project Solution
   h. <PBBUILD>/zlib-1.2.8/build/zlib.sln
   i. Change dropdown at top from Debug to Release
   j. Verify other dropdown at top says x64
   k. Select zlib in Solution Explorer window
   l. Build / Build Solution (creates files in zlib-1.2.8/build/Release)
10. For libpng
   a. Start "Visual Studio 2015"
   b. File / Open / Project Solution
   c. <PBBUILD>/libpng-1.6.34/projects/vstudio/vstudio.sln
   d. Change dropdown at top from Debug to Release
   e. Other dropdown at top offers only Win32 but we want x64
         i. Click on the dropdown
        ii. Click on Configuration Manager
       iii. Click on Win32 in the zlib line
        iv. Click on <New>
         v. For New Platform click on x64
        vi. Ok
       vii. Close
      viii. Verify dropdown at top now says x64
   e. Build zlib:
         i. Select "zlib" in Solution Explorer
        ii. Right click on "zlib" and select "Properties"
       iii. Platform dropdown probably says Win32 but we want x64
            a. Click on Configuration Manager button
            b. Click on cell in Platform column and zlib row. This makes a previously invisible
               dropdown button appear
            c. Click on the dropdown button in Platform column and zlib row
            d. Select x64 for New Platform
            e. Unselect the "Create new solution platforms". This step is required if x64 has
               been selected for any other rows in the Configuration Manager table
            f. Ok
            g. Close
        iv. Add to the Include Directories
            a. Select "VC++ Directories"
            b. Select "Include Directories"
            c. Select "arrow down" button to the right of "Include Directories"
            d. Select "<Edit>"
            e. Select "New Line" button which looks like a yellow folder with a yellow asterisk on it
            f. Select "..." to select a directory
            g. Select "<PBBUILD>/zlib-1.2.8/build"
            h. Select "Select Folder" button
            i. Select "Ok" button
            j. Select "Ok" button
         v. Right click on "zlib" in Solution Explorer and pick "Build". This builds zlib.lib
   f. Build libpng:
         i. Select "libpng" in Solution Explorer
        ii. Right click on "libpng" and select "Properties"
       iii. Platform dropdown probably says Win32 but we want x64
            a. Click on Configuration Manager button
            b. Click on cell in Platform column and libpng row. This makes a previously invisible
               dropdown button appear
            c. Click on the dropdown button in Platform column and libpng row
            d. Select x64 for New Platform
            e. Unselect the "Create new solution platforms". This step is required if x64 has
               been selected for any other rows in the Configuration Manager table
            f. Ok
            g. Close
        iv. Add to the Include Directories
            a. Select "VC++ Directories"
            b. Select "Include Directories"
            c. Select "arrow down" button to the right of "Include Directories"
            d. Select "<Edit>"
            e. Select "New Line" button which looks like a yellow folder with a yellow asterisk on it
            f. Select "..." to select a directory
            g. Select "<PBBUILD>/zlib-1.2.8/build"
            h. Select "Select Folder" button
            i. Select "Ok" button
            j. Select "Ok" button
         v. Add to the Library Directories
            a. Select "Library Directories"
            b. Select "arrow down" button to the right of "Library Directories"
            c. Select "New Line" button which looks like a yellow folder with a yellow asterisk on it
            d. Select "..." to select a directory
            e. Select "<PBUILD>/zlib-1.2.8/projects/vstudio/x64/Release"
            f. Select "Select Folder" button
            g. Select "Ok" button
            h. Select "Ok" button
       xvi. Right click on "libpng" in Solution Explorer and pick "Build". This builds
            libpng-1.6.34/projects/vstudio/x64/Release/libpng16.lib and zlib.lib. If there is a linking
            problem, especially if the linking issue involves unexpected underscores before the function
            names supplied by the zlib package, then one of the two libraries was mistakenly built
            for 32 bits instead of 64 bits - so repeat the previous steps making sure to pick 64 bits.
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
   g. >cmake -G "Visual Studio 14 2015 Win64" ..    (if you see the line NASM=NASM-NOTFOUND then 
      NASM was not properly installed or the simd/CMakeLists.txt file was not correctly edited). 
      Note that simd/CMakeLists.txt is doing the search for nasm, then yasm)
   h. Start "Visual Studio 2015"
   i. File / Open / Project Solution
   j. <PBBUILD>/libjpeg-turbo-1.5.3/build/libjpeg-turbo.sln
   k. Change dropdown at top from Debug to Release
   l. Verify other dropdown at top says x64
   q. Select "Solution / ALL_BUILD" in Solution Explorer window
   r. Build / Build Solution (creates files in libjpeg-turbo-1.5.3/build/Release and 
                              libjpeg-turbo-1.5.3/build/sharedlib/Release)
12. For freetype
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution
   c. Freetype-2.9 / builds / windows / vc2010
   d. Change dropdown at top from Debug to Release
   e. Change other dropdown at top to say x64
   f. Right click on freetype in Solution Explorer window
   g. Properties
   h. Build (creates freetype-2.9 / objs /win32 / vc2010 / Release / freetype.lib and freetype.dll)
   i. >cd objs / x64 / vc2010 / Release
   j. >copy freetype.lib libfreetype.lib (expected by fontconfig)
13. For libiconv-win-build
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution
   c. Libiconv-win-build-master / build-VS2015 / libiconv.sln
   d. Change dropdown at top from Debug to Release
   e. Change other dropdown at top to say x64
   f. Select dll / libiconv in Solution Explorer window and select BUILD (builds build-VS2015 / 
      Release / libiconv.dll)
   g. Select static / libiconv-static in Solution Explorer window and select Build (builds 
      build-VS2015 / Release / libiconv.lib)
   h. >cd build-VS2015 / x64 / Release
   i. >copy libiconv.lib iconv.lib (filename expected by libxml2)
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
   e. Verify other dropdown at top says x64
   f. Right click on libfontconfig in Solution Explorer window
   g. Properties
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
   c. edit CMakeLists.txt and add the following two ines after the 'find_package (LIBOPENJPEG2)' line.
      They are needed since cmake's find_package algorithm is looking for a nonexistent package file
      called FindLibOpenJp2.cmake:
         message ("Ignore previous error message that libopenjp2 was not found")
         set (LIBOPENJPEG2_FOUND TRUE)
   d. edit the following files and change 'strtok_r' to 'strtok_s':
         fofi/FoFiType1.cc
         poppler/CharCodeToUnicode.cc
         poppler/GlobalParams.cc
         poppler/PDFDoc.cc
         poppler/UnicodeMap.cc
   e. >mkdir build
   f. >cd build
   g. >set FREETYPE_INCLUDE_DIRS="%PBBUILD%\freetype-2.9\include; %PBBUILD%\freetype-2.9\include\freetype"
   h. >set FREETYPE_LIBRARY="%PBBUILD%\freetype-2.9\objs\x64\Release\freetype.lib"
   i. >set ICONV_LIBRARY="%PBBUILD%\libiconv-win-build-master\build-VS2015\Release\libiconv.lib"
   j. >set JPEG_INCLUDE_DIR="%PBBUILD%\libjpeg-turbo-1.5.3"
   k. >set JPEG_LIBRARY="%PBBUILD%\libjpeg-turbo-1.5.3\build\Release\jpeg-static.lib"
   l. >set LIBOPENJPEG2_INCLUDE_DIR="%PBBUILD%\openjpeg-2.3.0\src\lib\openjp2"
   m. >set LIBOPENJPEG2_LIBRARY="%PBBUILD%\openjpeg-2.3.0\build\bin\Release\openjp2.lib"
   n. >set PNG_INCLUDE_DIR="%PBBUILD%\libpng-1.6.34"
   o. >set PNG_LIBRARY="%PBBUILD%\libpng-1.6.34\projects\vstudio\x64\Release\libpng16.lib"
   p. >set ZLIB_INCLUDE_DIR="%PBBUILD%\zlib-1.2.8"
   q. >set ZLIB_LIBRARY="%PBBUILD%\zlib-1.2.8\build\Release\zlib.lib"
   r. >cmake -G "Visual Studio 14 2015 Win64" .. -DFREETYPE_INCLUDE_DIRS=%FREETYPE_INCLUDE_DIRS% -DFREETYPE_LIBRARY=%FREETYPE_LIBRARY% -DICONV_LIBRARIES=%ICONV_LIBRARY% -DJPEG_INCLUDE_DIR=%JPEG_INCLUDE_DIR% -DJPEG_LIBRARY=%JPEG_LIBRARY% -DLIBOPENJPEG2_INCLUDE_DIRS=%LIBOPENJPEG2_INCLUDE_DIR% -DLIBOPENJPEG2_LIBRARIES=%LIBOPENJPEG2_LIBRARY% -DPNG_PNG_INCLUDE_DIR=%PNG_INCLUDE_DIR% -DPNG_LIBRARY=%PNG_LIBRARY% -DZLIB_INCLUDE_DIR=%ZLIB_INCLUDE_DIR% -DZLIB_LIBRARY=%ZLIB_LIBRARY%
      (note there are several unexpected spellings!)
   s. Start "Visual Studio 2015"
   t. File / Open / ProjectSolution 
   u. poppler-0.62.0\build\poppler.sln
   v. Change dropdown at top from Debug to Release
   w. Verify the other dropdown at top says x64
   x. Right click on poppler in Solution Explorer window
         i. Properties
        ii. Select "VC++ Directories"
       iii. Select "Include Directories"
        iv. Select "arrow down" button to the right of "Include Directories"
         v. Select "<Edit>"
        vi. Add <PBBUILD>\freetype-2.9\include
       vii. Add <PBBUILD>\libjpeg-turbo-1.5.3
      viii. Add <PBBUILD>\libjpeg-turbo-1.5.3\build
        ix. Add <PBBUILD>\libpng-1.6.34
         x. Add <PBBUILD>\openjpeg-2.3.0\build\src\lib\openjp2
        xi. Add <PBBUILD>\zlib-1.2.8\
       xii. Add <PBBUILD>\zlib-1.2.8\build
      xiii. Build (this creates build\Release\poppler.lib)
   y. Right click on poppler-qt5 in Solution Explorer window
         i. Properties
        ii. Select "VC++ Directories"
       iii. Select "Include Directories"
        iv. Select "arrow down" button to the right of "Include Directories"
         v. Select "<Edit>"
        vi. Add <PBBUILD>\freetype-2.9\include
       vii. Add <PBBUILD>\libjpeg-turbo-1.5.3
      viii. Add <PBBUILD>\libjpeg-turbo-1.5.3\build
        ix. Add <PBBUILD>\libpng-1.6.34
         x. Add <PBBUILD>\openjpeg-2.3.0\build\src\lib\openjp2
        xi. Add <PBBUILD>\zlib-1.2.8\
       xii. Add <PBBUILD>\zlib-1.2.8\build
      xiii. Build (this creates build\qt5/src/Release\poppler-qt5.lib)
17. Copy *.lib files to ../poppler-64bit-libs/lib
18. To build with poppler:
   a. set FFTW_HOME=%PBBUILD%\..\unzip_fftw\lib64
   b. set LOG4CPP_HOME=%PBBUILD%\..\unzip_log4cpp\lib
   b. set POPPLER_INCLUDE=%PBLIBS%\include
   c. set POPPLER_LIB=%PBLIBS%\lib
   c. vcvarsall amd64
   d. qmake CONFIG+=pdf engauge.pro
   e. nmake
