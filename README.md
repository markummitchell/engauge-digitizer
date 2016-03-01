[![Travis build Status](https://travis-ci.org/markummitchell/engauge-digitizer.svg?branch=master)](https://travis-ci.org/markummitchell/engauge-digitizer) 
[![AppVeyor build status](https://ci.appveyor.com/api/projects/status/1o7p8iu8qxq0p7ri/branch/master?svg=true)](https://ci.appveyor.com/project/markummitchell/engauge-digitizer/branch/master)

engauge-digitizer
=================

[![Join the chat at https://gitter.im/markummitchell/engauge-digitizer](https://badges.gitter.im/markummitchell/engauge-digitizer.svg)](https://gitter.im/markummitchell/engauge-digitizer?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)

The Engauge Digitizer tool accepts image files (like PNG, JPEG and TIFF) containing graphs, and recovers the data points from those graphs. The resulting data points are usually used as input to other software applications. Conceptually, Engauge Digitizer is the opposite of a graphing tool that converts data points to graphs.

Engauge Digitizer is distributed with most Linux distributions. Downloads of the most recent 
[releases](https://github.com/markummitchell/engauge-digitizer/releases) are available for Linux and Windows. 

This tool is widely used. Users range from one-time users digitizing a single image file, to large government and commercial organizations managing databases of thousands of image files.

Interested in translating Engauge to another language? We welcome translations of file engauge.ts to [other languages](http://doc.qt.io/qt-5/linguist-programmers.html).

Released Versions
-----------------
Version 6.2 (11/4/2015) now accepts dragged DIG files, and adds a ZIP file for installing in Windows without administrator
access privileges.

Version 6.1 (10/31/2015) can load DIG files from earlier versions of Engauge Digitizer.

Version 6.0 (10/23/2015) of Engauge 6 was released. This is a major rewrite of the 10 year old Engauge Digitizer software project that lives on sourceforge.net. The replacement is required since the Qt3 toolkit that Engauge relies on is disappearing. Engauge-Digitizer uses the new Qt5 library which should be available for many years, and also offers many new features.

Developers and users are encouraged to offer their suggestions and comments!

Features
--------
Features in released versions of Engauge-Digitizer:

1. Automated line and point extraction rapidly digitizes data
2. Image processing for separating important details from background information
3. Undo/redo of all operations means recovering from mistakes and experimenting with options is painless
4. MSI installer for Windows operating system
5. Wizard provides an interactive tutorial to explain the basic steps
6. Wizard creates a checklist guide to interactively leads user through steps from file import to file export
7. Cubic spline interpolation between points gives more accurate curves with fewer points
8. Axes Checker briefly highlights the axes when they are defined or modified, to reveal entry mistakes
9. Graph coordinates can be specified as date and time values, or as degrees, minutes and seconds
10. Import by drag-and-drop
11. Test suite for regression testing minimizes code breakage as new features are added

Features coming in upcoming version 7:

1. Multiple coordinate systems in the same image can be digitized in advanced mode
2. Axes with only one known coordinate (floating axes) can be digitized in advanced mode
3. File import by pasting

Installation
------------
Engauge can be installed using packages for all popular distributions of Linux (easiest method), or by downloading
pre-built binaries for Windows and Linux (slightly less easy). The pre-built binaries are available from the engauge-digitizer
project at github.com, in the [Releases page](https://github.com/markummitchell/engauge-digitizer/releases). The final option 
for installing is to build the software from the source
code (very difficult). Building the software from the source code is accomplished by following the steps in the BUILD
file that is found in the main directory. The build process can take as little as 15 minutes in Linux or as long as 
several hours in Microsoft Windows.

Contributors
------------
Thanks to Zbigniew Jędrzejewski-Szmek, Tamás Nagy, Baurzhan Muftakhidinov, Tobias Winchen and other contributors and users!
