
Building the Poppler Library, and the Libraries It Depends On, In Windows (64 Bit)
----------------------------------------------------------------------------------
Prerequisites: 1) Qt 5.8 64 bit libraries and qmake are installed

1. Install Visual Studio 2015
2. Define the critical environment variables using these lines after replacing <root>:
   >set PBBUILD64=<root>\engauge-digitizer\dev\windows\poppler-64bit-build
   >set PBLIBS64=<root>\engauge-digitizer\dev\windows\poppler-64bit-libs
   >set PBTARBALLS=<root>\engauge-digitizer\dev\windows\poppler-tarballs
3. Download and install nasm=-2.14rc0-installer-x64.exe
   a. Add directory containing nasm.exe to PATH
4. Extract the following from %PBTARBALLS% into %PBBUILD64% (with version numbers recommended by 
   http://www.linuxfromscratch.org/blfs/view/cvs/general/poppler.html):
   a. cmake-3.8.0-win64-x64.msi (creates solution files for visual studio)
   b. fontconfig-master.zip (from github/ShiftMediaProject/fontconfig which has a Windows 
      solution file. For poppler)
   c. freetype-2.9.tar.gz (for fontconfig)
   d. libiconv-win-build.zip (from github/kiyolee/libconv-win-build. Optional for fontconfig)
   e. libjpeg-turbo-1.5.3.tar.gz (for poppler)
   f. libpng-1.6.34.tar.gz (for poppler)
   g. libxml2-2.9.4.tar.gz (for fontconfig)
   h. openjpeg-2.3.0.tar.gz (for poppler)
   i. poppler-0.62.0.tar.xz
   j. zlib-1.2.8.tar.gz (for libpng)
5. For cmake
   a. Run cmake-3.8.0-win64-x64.msi
   b. Put cmake.exe into PATH in Control Panel / System / Advanced Settings / Environment Variables
6. For openjpeg,
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD64%/openjpeg-0.62.0
   c. >mkdir build
   d. >cd build
   e. >cmake -G "Visual Studio 14 2015 Win64" ..
   f. Start "Visual Studio 2015"
   g. File / Open / Project Solution
   h. <PBBUILD64>/openjpeg-0.62.0/build/OPENJPEG.sln
   i. Change dropdown at top from Debug to Release
   j. Verify other dropdown at top says x64
   k. Select "ALL_BUILD" in Solution Explorer window
   l. Build / Build Solution (creates files in openjpeg-0.62.0/build/bin/Release)
7. For zlib
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD64%/zlib-1.2.8
   c. >mkdir build
   d. >cd build
   e. >cmake -G "Visual Studio 14 2015 Win64" ..
   f. Start "Visual Studio 2015"
   g. File / Open / Project Solution
   h. <PBBUILD64>/zlib-1.2.8/build/zlib.sln
   i. Change dropdown at top from Debug to Release
   j. Verify other dropdown at top says x64
   k. Select zlib in Solution Explorer window
   l. Build / Build Solution (creates files in zlib-1.2.8/build/Release)
8. For libpng
   a. Start "Visual Studio 2015"
   b. File / Open / Project Solution
   c. <PBBUILD64>/libpng-1.6.34/projects/vstudio/vstudio.sln
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
   f. Build zlib:
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
            g. Select "<PBBUILD64>/zlib-1.2.8/build"
            h. Select "Select Folder" button
            i. Select "Ok" button
            j. Select "Ok" button
         v. Right click on "zlib" in Solution Explorer and pick "Build". This builds zlib.lib
   g. Build libpng:
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
            g. Select "<PBBUILD64>/zlib-1.2.8/build"
            h. Select "Select Folder" button
            i. Select "Ok" button
            j. Select "Ok" button
         v. Add to the Library Directories
            a. Select "Library Directories"
            b. Select "arrow down" button to the right of "Library Directories"
            c. Select "New Line" button which looks like a yellow folder with a yellow asterisk on it
            d. Select "..." to select a directory
            e. Select "<PBBUILD64>/zlib-1.2.8/build/Release"
            f. Select "Select Folder" button
            g. Select "Ok" button
            h. Select "Ok" button
       xvi. Right click on "libpng" in Solution Explorer and pick "Build". This builds
            libpng-1.6.34/projects/vstudio/x64/Release/libpng16.lib and zlib.lib. If there is a linking
            problem, especially if the linking issue involves unexpected underscores before the function
            names supplied by the zlib package, then one of the two libraries was mistakenly built
            for 32 bits instead of 64 bits - so repeat the previous steps making sure to pick 64 bits.
9. For libjpeg-turbo
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD64%/libjpeg-turbo-1.5.3
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
   j. <PBBUILD64>/libjpeg-turbo-1.5.3/build/libjpeg-turbo.sln
   k. Change dropdown at top from Debug to Release
   l. Verify other dropdown at top says x64
   m. Select "Solution / ALL_BUILD" in Solution Explorer window
   n. Build / Build Solution (creates files in libjpeg-turbo-1.5.3/build/Release and 
                              libjpeg-turbo-1.5.3/build/sharedlib/Release)
10. For freetype
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution
   c. Freetype-2.9 / builds / windows / vc2010 / freetype.sln
   d. Change dropdown at top from Debug to Release
   e. Change other dropdown at top to say x64
   f. Right click on freetype in Solution Explorer window
   g. Properties
   h. Build (creates freetype-2.9 / objs / x64 / vc2010 / Release / freetype.lib and freetype.dll)
   i. >cd objs / x64 / Release
   j. >copy freetype.lib libfreetype.lib (expected by fontconfig)
11. For libiconv-win-build
   a. Start "Visual Studio 2015"
   b. File / Open / ProjectSolution
   c. Libiconv-win-build-master / build-VS2015 / libiconv.sln
   d. Change dropdown at top from Debug to Release
   e. Change other dropdown at top to say x64
   f. Select dll / libiconv in Solution Explorer window and select BUILD (builds build-VS2015 / 
      x64 / Release / libiconv.dll)
   g. Select static / libiconv-static in Solution Explorer window and select Build (builds 
      build-VS2015 / x64 / Release / libiconv.lib)
   h. >cd build-VS2015 / x64 / Release
   i. >copy libiconv.lib iconv.lib (filename expected by libxml2)
12. For libxml2 we use nmake, since the Visual Studio project file is broken. Following 
    http://marlowa.blogspot.com/2013/07/how-to-build-libxml2-on-windows-using.html
   a. start Qt 64 bit window for VS 2015
   b. >set PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC:%PATH%
   c. >set PATH=C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\bin:%PATH%
   d. >set PATH=%PBBUILD64%\libiconv-win-build-master\build-VS2015\x64\Release:%PATH%
   e. >cd win32
   f. >cscript configure.js compiler=msvc include=%PBBUILD64%\libiconv-win-build-master\include lib=%PBBUILD64%\libiconv-win-build-master\build-vs2015\x64\Release debug=no (this creates file config.msvc)
   g. edit file Makefile.msvc
   h. After line "CFLAGS=$(CFLAGS) /D_CRT_SECURE_NO_DEPRECATE /D_CRT_NONSTDC_NO_DEPRECATED", add the 
      line "CFLAGS=$(CFLAGS) /D_SECURE_SCL=0 /D_SCL_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_DEPRECATE"
   i. Save file and exit editor
   j. >vcvarsall.bat
   k. >nmake (this creates win32/bin.msvc/libxml2.dll and libxml2.lib)
13. For fontconfig (using ShiftMediaSolution release with its support for Windows)
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
        ii. add path to <PBBUILD64>/freetype-2.9/include
       iii. add path to <PBBUILD64>/libiconv-win-build-master/include
        iv. add path to <PBBUILD64>/libxml2-2.9.7/include
   j. VC++ Directories
         i. Library Directories
        ii. add <PBBUILD64>/libiconv-win-build-master/build-VS2015/Release
       iii. add <PBBUILD64>/freetype-2.9/objs/x64/Release
        iv. add <PBBUILD64>/libxml2-2.9.7/win32/bin.msvc
   k. Right click on libconfig in Solution Explorer window
   l. Build (creates SMP/msvc/lib/x64/libfontconfig.lib)
14. For poppler
   a. start Qt 64 bit window for VS 2015
   b. >cd %PBBUILD64%/poppler-0.62.0
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
   g. following lines define the environment variables:
      >set FREETYPE_INCLUDE_DIRS="%PBBUILD64%\freetype-2.9\include; %PBBUILD64%\freetype-2.9\include\freetype"
      >set FREETYPE_LIBRARY="%PBBUILD64%\freetype-2.9\objs\x64\Release\freetype.lib"
      >set ICONV_LIBRARY="%PBBUILD64%\libiconv-win-build-master\build-VS2015\Release\libiconv.lib"
      >set JPEG_INCLUDE_DIR="%PBBUILD64%\libjpeg-turbo-1.5.3"
      >set JPEG_LIBRARY="%PBBUILD64%\libjpeg-turbo-1.5.3\build\Release\jpeg-static.lib"
      >set LIBOPENJPEG2_INCLUDE_DIR="%PBBUILD64%\openjpeg-2.3.0\src\lib\openjp2"
      >set LIBOPENJPEG2_LIBRARY="%PBBUILD64%\openjpeg-2.3.0\build\bin\Release\openjp2.lib"
      >set PNG_INCLUDE_DIR="%PBBUILD64%\libpng-1.6.34"
      >set PNG_LIBRARY="%PBBUILD64%\libpng-1.6.34\projects\vstudio\x64\Release\libpng16.lib"
      >set ZLIB_INCLUDE_DIR="%PBBUILD64%\zlib-1.2.8"
      >set ZLIB_LIBRARY="%PBBUILD64%\zlib-1.2.8\build\Release\zlib.lib"
   h. >cmake -G "Visual Studio 14 2015 Win64" .. -DFREETYPE_INCLUDE_DIRS=%FREETYPE_INCLUDE_DIRS% -DFREETYPE_LIBRARY=%FREETYPE_LIBRARY% -DICONV_LIBRARIES=%ICONV_LIBRARY% -DJPEG_INCLUDE_DIR=%JPEG_INCLUDE_DIR% -DJPEG_LIBRARY=%JPEG_LIBRARY% -DLIBOPENJPEG2_INCLUDE_DIRS=%LIBOPENJPEG2_INCLUDE_DIR% -DLIBOPENJPEG2_LIBRARIES=%LIBOPENJPEG2_LIBRARY% -DPNG_PNG_INCLUDE_DIR=%PNG_INCLUDE_DIR% -DPNG_LIBRARY=%PNG_LIBRARY% -DZLIB_INCLUDE_DIR=%ZLIB_INCLUDE_DIR% -DZLIB_LIBRARY=%ZLIB_LIBRARY%
      (note there are several unexpected spellings!)
   i. Start "Visual Studio 2015"
   j. File / Open / ProjectSolution 
   k. poppler-0.62.0\build\poppler.sln
   l. Change dropdown at top from Debug to Release
   m. Verify the other dropdown at top says x64
   n. Right click on poppler in Solution Explorer window
         i. Properties
        ii. Select "VC++ Directories"
       iii. Select "Include Directories"
        iv. Select "arrow down" button to the right of "Include Directories"
         v. Select "<Edit>"
        vi. Add <PBBUILD64>\freetype-2.9\include
       vii. Add <PBBUILD64>\libjpeg-turbo-1.5.3
      viii. Add <PBBUILD64>\libjpeg-turbo-1.5.3\build
        ix. Add <PBBUILD64>\libpng-1.6.34
         x. Add <PBBUILD64>\openjpeg-2.3.0\build\src\lib\openjp2
        xi. Add <PBBUILD64>\zlib-1.2.8\
       xii. Add <PBBUILD64>\zlib-1.2.8\build
      xiii. Build (this creates build\Release\poppler.lib)
   o. Right click on poppler-qt5 in Solution Explorer window
         i. Properties
        ii. Select "VC++ Directories"
       iii. Select "Include Directories"
        iv. Select "arrow down" button to the right of "Include Directories"
         v. Select "<Edit>"
        vi. Add <PBBUILD64>\freetype-2.9\include
       vii. Add <PBBUILD64>\libjpeg-turbo-1.5.3
      viii. Add <PBBUILD64>\libjpeg-turbo-1.5.3\build
        ix. Add <PBBUILD64>\libpng-1.6.34
         x. Add <PBBUILD64>\openjpeg-2.3.0\build\src\lib\openjp2
        xi. Add <PBBUILD64>\zlib-1.2.8\
       xii. Add <PBBUILD64>\zlib-1.2.8\build
      xiii. Build (this creates build\qt5/src/Release\poppler-qt5.lib)
15. Copy built files to %PBLIBS64%/lib
    >copy/Y %PBBUILD64%\freetype-2.9\objs\x64\Release\freetype.dll           %PBLIBS64%\lib
    >copy/Y %PBBUILD64%\openjpeg-2.3.0\build\bin\Release\openjp2.dll         %PBLIBS64%\lib
    >copy/Y %PBBUILD64%\poppler-0.62.0\build\qt5\src\Release\poppler-qt5.lib %PBLIBS64%\lib
    >copy/Y %PBBUILD64%\poppler-0.62.0\build\qt5\src\Release\poppler-qt5.dll %PBLIBS64%\lib
    >copy/Y %PBBUILD64%\poppler-0.62.0\build\Release\poppler.lib             %PBLIBS64%\lib
    >copy/Y %PBBUILD64%\zlib-1.2.8\build\Release\zlib.dll                    %PBLIBS64%\lib
16. To build with poppler, make sure PBBUILD64 and PBLIB are defined then use the following lines:
    >set FFTW_HOME=%PBBUILD64%\..\unzip_fftw\lib64
    >set LOG4CPP_HOME=%PBBUILD64%\..\unzip_log4cpp\lib
    >set POPPLER_INCLUDE=%PBLIBS64%\include
    >set POPPLER_LIB=%PBLIBS64%\lib
    >vcvarsall amd64
    >cd <root>\engauge-digitizer         (after replacing <root>)
    >qmake CONFIG+=pdf engauge.pro
    >nmake
    >copy/Y %PBLIBS64%\lib\*.dll bin
