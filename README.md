<h2>This Software Is In Beta Test! All feedback welcome</h2>

engauge6
========

Rewrite of Engauge Digitizer from Qt3/Qt4 to Qt5

Status
------
This project aims to replace the 10 year old Engauge Digitizer software project that lives on sourceforge.net, with a newer version. The replacement is required since the Qt3 toolkit that Engauge relies on is disappearing. Engauge6 uses the new Qt5 library which should be available for many years.

As of September 2015, Engauge6 has:

* Over 25,000 lines of Engauge6 C++ code in github
* Beta functionality - so user testing is welcome
* Issue tracking in the github issue tracker
* GitHub wiki for informal communication, and GitHub issue tracker for requirements, bugs, etc.

Developers and users are encouraged to offer their suggestions and comments!

Features
--------
Ideas for new features in Engauge6:

1. Call OpenCV (or ?) to automatically recognize axes and axis coordinates

New features already added to Engauge6:

1. Undo/redo of all operations means recovering from mistakes and experimenting with options is painless
2. Wizard provides an interactive tutorial to explain the basic steps
3. Wizard creates a checklist guide to interactively leads user through steps from file import to file export
4. Cubic spline interpolation between points gives more accurate curves with fewer points
5. Axes Checker briefly highlights the axes when they are defined or modified, to reveal entry mistakes
6. Graph coordinates can be specified as date and time value, or as degrees, minutes and seconds
7. All settings dialogs are resizable so they can be enlarged as necessary to display more information
8. Import by drag-and-drop
9. Replacement of Qt3 (which is at its end of life) by Qt5
10. Much better zooming, with a fill mode that automatically zooms in on image features, and rezooms when the
    application window is resized
11. Color picking straight from the original image
12. Uploadable error report generated when a programming error is encountered, for identifying problems and improving
    user support
13. Test suite for regression testing minimizes code breakage as new features are added
