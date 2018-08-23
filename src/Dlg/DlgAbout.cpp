/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgAbout.h"
#include "MainWindow.h"
#include "Version.h"

DlgAbout::DlgAbout (MainWindow &mainWindow) :
  QMessageBox (&mainWindow),
  m_mainWindow (mainWindow)
{
  setWindowTitle (tr ("About Engauge"));
  setTextFormat (Qt::RichText);

  // Do not embed single quotes in the strings below since that will interfere with the translations
  setText (QString ("<p>%1 %2 %3</p> <p>&copy; Mark Mitchell</p><p>%4</p><p>%5</p><p>%6</p><p>%7</p><p>%8:</p>"
                    "<ul>"
                     "<li><a href=\"https://github.com/markummitchell/engauge-digitizer\">%9</a></li>"
                     "<li><a href=\"https://gitter.im/markummitchell/engauge-digitizer\">%10</a></li>"
                     "</ul>"
                     "<p>FFTW 3.X.X:</p>"
                     "<ul>"
                     "<li><a href=\"http://www.fftw.org\">%11</a></li>"
                     "</ul>"
                     "<p>OpenJPEG 2.X:</p>"
                     "<ul>"
                     "<li><a href=\"http://www.openjpeg.org\">%12</a></li>"
                    "</ul>")
           .arg (tr ("Engauge Digitizer"))
           .arg (tr ("Version"))
           .arg (VERSION_NUMBER)
           .arg (tr ("Engauge Digitizer is an open source tool for efficiently extracting accurate numeric data from "
                     "images of graphs. The process may be considered as inverse graphing. When you engauge a document, "
                     "you are converting pixels into numbers."))
           .arg (tr ("This is free software, and you are welcome to redistribute it under "
                     "certain conditions according to the GNU General Public License Version 2,"
                     "or (at your option) any later version."))
           .arg (tr ("Engauge Digitizer comes with ABSOLUTELY NO WARRANTY."))
           .arg (tr ("Read the included LICENSE file for details."))
           .arg (tr ("Engauge Digitizer"))
           .arg (tr ("Project Home Page"))
           .arg (tr ("Gitter Forum"))
           .arg (tr ("Project Page"))
           .arg (tr ("Project Page")));
}
