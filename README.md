engauge6
========

The Engauge Digitizer tool accepts image files (like PNG, JPEG and TIFF) containing graphs, and recovers the data points from those graphs. The resulting data points are usually used as input to other software applications. Conceptually, Engauge Digitizer is the opposite of a graphing tool that converts data points to graphs.

Engauge Digitizer is distributed with most Linux distributions. Downloads of the most recent 
[releases](https://github.com/markummitchell/engauge6/releases) are available for Linux and Windows. 

This tool is widely used. Users range from one-time users digitizing a single image file, to large government and commercial organizations managing databases of thousands of image files.

Versions
--------
Version 6.2 (11/4/2015) now accepts dragged DIG files, and adds a ZIP file for installing in Windows without administrator
access privileges.

Version 6.1 (10/31/2015) can load DIG files from earlier versions of Engauge Digitizer.

Version 6.0 (10/23/2015) of Engauge 6 was released. This is a major rewrite of the 10 year old Engauge Digitizer software project that lives on sourceforge.net. The replacement is required since the Qt3 toolkit that Engauge relies on is disappearing. Engauge6 uses the new Qt5 library which should be available for many years, and also offers many new features.

Developers and users are encouraged to offer their suggestions and comments!

Features
--------
New features in Engauge6:

1. Undo/redo of all operations means recovering from mistakes and experimenting with options is painless
2. MSI installer for Windows operating system
3. Wizard provides an interactive tutorial to explain the basic steps
4. Wizard creates a checklist guide to interactively leads user through steps from file import to file export
5. Cubic spline interpolation between points gives more accurate curves with fewer points
6. Axes Checker briefly highlights the axes when they are defined or modified, to reveal entry mistakes
7. Graph coordinates can be specified as date and time value, or as degrees, minutes and seconds
8. Multiple coordinate systems in the same image can be digitized in advanced mode
9. Axes with only one known coordinate (floating axes) can be digitized in advanced mode
10. All settings dialogs are resizable so they can be enlarged as necessary to display more information
11. Import by drag-and-drop
12. Replacement of Qt3 (which is at its end of life) by Qt5
13. Much better zooming, with a fill mode that automatically zooms in on image features, and rezooms when the
    application window is resized
14. Color picking straight from the original image
15. Uploadable error report generated when a programming error is encountered, for identifying problems and improving
    user support
16. Test suite for regression testing minimizes code breakage as new features are added

Installation
------------
Engauge can be installed using packages for all popular distributions of Linux (easiest method), or by downloading
pre-built binaries for Windows and Linux (slightly less easy). The pre-built binaries are available from the engauge6
project at github.com, in the [Releases page](https://github.com/markummitchell/engauge6/releases). The final option 
for installing is to build the software from the source
code (very difficult). Building the software from the source code is accomplished by following the steps in the BUILD
file that is found in the main directory. The build process can take as little as 15 minutes in Linux or as long as 
several hours in Microsoft Windows.

Contributors
------------
Thanks to Zbigniew Jędrzejewski-Szmek, Tamás Nagy, Baurzhan Muftakhidinov, Tobias Winchen and other contributors and users!
