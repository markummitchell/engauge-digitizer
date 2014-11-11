engauge6
========

Rewrite of Engauge Digitizer from Qt3/Qt4 to Qt5

# Status
This project aims to replace the 10 year old Engauge Digitizer software project that lives on sourceforge.net, with a newer version. The replacement is required since the Qt3 toolkit that Engauge relies on is disappearing. Engauge26 uses the new Qt5 library which should be available for many years.

As of November 9, 2014, Engauge6 has:
* 12,000 lines of Engauge6 C++ code and comments in github
* A working skeleton that can be tested. No useful output is created yet though
* Issue tracking in the github issue tracker

Developers and users are encouraged to offer their suggestions and comments!

# Features
Ideas for new features in Engauge6:

1. Call OpenCV (or ?) to automatically recognize axes and axis coordinates
2. Splash screen with tutorial video, or link to tutorial video on a webserver
3. Upload application state/logs after a crash

New features already added to Engauge2:

1. Undo/redo
2. Single settings dialog (with tabs) that is resizable preview windows
3. Import by drag-and-drop
4. Replacement of Qt3 (which is at its end of life) by Qt5
