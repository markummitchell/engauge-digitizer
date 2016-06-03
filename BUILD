This file gives details for building Engauge from source code. 

   *****************************************************************
   *                                                               *
   *  If you want to use Engauge immediately, and do not need to   *
   *  work with the source code, then you should refer to the      *
   *  instructions in the INSTALL file. The steps in the INSTALL   *
   *  file can take less than a few minutes, but the steps in      *
   *  this BUILD file can take hours.                              *
   *                                                               *
   *****************************************************************

Windows - Steps to build and run engauge executable:
----------------------------------------------------
These steps build and run, in Microsoft Windows, the standard engauge executable for digitizing data.

1) Install the MinGW version of the Qt Open Source toolkit from http://www.qt.io. Since the default
   Qt Open Source download supports Microsoft Visual Studio rather than MinGW, careful navigation
   of the Qt website is required to find, and then download, the Qt installation package that
   explicitly targets the MinGW compiler. The MinGW compiler provides the correct header files and system
   functions (unlike Visual Studio).

   Note that the MinGW version of the Qt Open Source toolkit provides both Qt and MinGW. There is no
   need to install a standalone version of MinGW.

   Qt Open Source 5.2.1 and 5.5.1 have been tested with Engauge. Qt Versions 5.1 and older do not offer
   features, that were added in version 5.2, that are required to build Engauge.

   HINT - At this point, the MSYS shell is available by clicking on the msys.bat shortcut on the Windows
          desktop. The MSYS shell is preferred over the Cygwin shell (if you have installed Cygwin earlier).

2) Download and build log4cpp from http://log4cpp.sourceforge.net. Version 1.1 was tested with Engauge. 
   The following minor changes were required for the code to compile:
  
   2a) In config-MinGW32.h, comment out '#define int64_t __int64' to prevent 'long long long is too long for gcc'
   2b) In DailyRollingFileAppender.cpp, insert '#include <time.h>'
   2c) In DailyRollingFileAppender.cpp, replace 'time(X)' by 'time_t(X)' where X is the argument
   2d) In DailyRollingFileAppender.cpp, replace 'localtime_s(X,Y)' by 'localtime(Y)' where X and Y are arguments

   Then following the normal configure, make and make install steps.

3) Download and build fftw from http://www.fftw.org. Version 3.3.4 was tested with Engauge.
   
   Then following the normal configure, make and make install steps.

4) Set LOG4CPP_HOME and FFTW_HOME environment variables to point to the installation directories of 
   log4cpp and fftw in the previous steps.

5) Build engauge using either the command line approach, or qtcreator. 

   The command line approach is run from the highest level Engauge directory:

   > qmake engauge.pro
   > make

   Alternately, you can use the qtcreator approach instead:

   > qtcreator
   > File / Open / open engauge.pro
   > Build / BuildAll
   > Run 

6) Build the help file

   > cd help
   > build

Linux - Steps to build and run engauge executable:
--------------------------------------------------
These steps build and run, in Linux, the standard engauge executable for digitizing data.

1) Install open source version 5 of the Qt toolkit. This is probably
   available for your operating systems as a source tarball, or many packages.
   If there is a development version of qt5, that should be installed as 
   a minimum

     --Package(s)--     --Comment--
     *qt5-dev*          Qt version 5 toolkit for building engauge

2) In a mixed Qt4 and Qt5 environment, you need to make sure that the environment
   points to the correct Qt version by using qtchooser and/or settings the
   environment variable QT_SELECT=qt5

3) Install package dependencies using your package manager. Different packages
   may be substituted, or additional packages added, according to the feedback
   supplied in step #3. The suggested list of packages for non-Debian and 
   non-Ubuntu distributions is:

     --Package(s)--     --Comment--
     libfftw3-dev       For computing fourier transforms. Tested with 3.3.3-7
     libjpeg-dev        For reading jpeg image files (optional)
     liblog4cpp-dev     For logging. Tested with 1.0.4
     libpng12-dev       For reading png image files (optional)
     libopenjpeg-dev    For reading jpeg2000 image files (optional). Compiles
                        with version 2.1.7 but not with version 2.1.3

   In Debian and Ubuntu distributions, the following packages are required for
   building Engauge for your own use:

     --Package(s)--     --Comment--
     libfftw3-dev       Required for all distributions
     libjpeg-dev        Required for all distributions
     liblog4cpp5-dev    Replaces liblog4cpp-dev that is suggested above
     libpng12-dev       Required for all distributions
     libqt5sql5-sqlite
     qtbase5-dev  
     qtbase5-dev-tools
     qttools5-dev
     qttools5-dev-tools

4) Run qmake on this file to generate make files. The qmake executable will
   display what functionality will, and what functionality will not, be included 
   in engauge as a function of the currently installed packages. Run one of these
   qmake commands in the highest level Engauge directory:

     > qmake engauge.pro                       (for release version)

   or

     > qmake CONFIG+=debug engauge.pro         (for debug version)

   By default, the release version will be built by qmake. To build a debug version
   instead, add "CONFIG+=debug" to the qmake command line.

5) Build the executable using the make files from the previous step:

     > make

6) Generate the help files

     > ../help/build

7) Run engauge

     > ../bin/engauge

Linux - Steps to build engauge test executables and perform tests
---------------------------------------------------------
These steps build and test engauge, in Linux.

1) Verify the standard version of engauge executable can be built and run

2) Run the command-line tests. Every line PASS/FAIL line should say PASS. If 
   no PASS/FAIL lines appear then the build probably failed, in which case the 
   build_and_run_all_cli_tests.log file can be examined to identify the build issues

     > cd src
     > ./build_and_run_all_cli_tests

3) Run the graphical user interface tests.

     > cd src (if not already in that directory)
     > ./build_and_run_all_gui_tests

Steps to generate doxygen documentation
---------------------------------------
This generates doxygen documentation

1) Run doxygen

     > cd src
     > doxygen

2) Open engauge6/doc/doxygen/html/index.html in your browser

Steps to generate a software metrics report
-------------------------------------------
This generates doxygen documentation

1) Run cccc

     > cd src
     > docccc

2) Open engauge6/doc/cccc/index.html in your browser
