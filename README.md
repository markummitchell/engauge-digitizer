<h2>This Software Is In Beta Test! All feedback welcome</h2>

engauge6
========

Rewrite of Engauge Digitizer from Qt3/Qt4 to Qt5

Versions
--------
October 25, 2015, version 6.0 is being upgraded to be able to read older Digitizer documents for issue #20. Upgrades for Linux package maintainers have been added.

October 23, 2015, version 6.0 of Engauge 6 was released. This is a major rewrite of the 10 year old Engauge Digitizer software project that lives on sourceforge.net. The replacement is required since the Qt3 toolkit that Engauge relies on is disappearing. Engauge6 uses the new Qt5 library which should be available for many years, and also offers many new features.

Developers and users are encouraged to offer their suggestions and comments!

Features
--------
New features in Engauge6:

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

Contributors
------------
Thanks to Zbigniew Jędrzejewski-Szmek, Tamás Nagy, Baurzhan Muftakhidinov, Tobias Winchen and other contributors and users!
