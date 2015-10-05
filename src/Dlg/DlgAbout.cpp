#include "DlgAbout.h"
#include "MainWindow.h"
#include "Version.h"

DlgAbout::DlgAbout (MainWindow &mainWindow) :
  QMessageBox (&mainWindow),
  m_mainWindow (mainWindow)
{
  setWindowTitle (tr ("About Engauge"));
  setTextFormat (Qt::RichText);
  setText (QString ("%1 Version %2 %3")
           .arg (tr ("<p>Engauge Digitizer</b>"))
           .arg (VERSION_NUMBER)
           .arg (tr ("</p><p>&copy; 2014 Mark Mitchell</p>"
                     "<p>Engauge Digitizer is an open source tool for efficiently extracting accurate numeric data from "
                     "images of graphs. The process may be considered as \"inverse graphing\". When you \"engauge\" a document, "
                     "you are converting pixels into numbers.</p>"
                     "<p>This is free software, and you are welcome to redistribute it under "
                     "certain conditions according to the GNU General Public License Version 2,"
                     "or (at your option) any later version.</p>"
                     "<p>Engauge Digitizer comes with ABSOLUTELY NO WARRANTY.</p>"
                     "<p>Read the included LICENSE file for details.</p>"
                     "<p>Engauge Digitizer Links<p>"
                     "<ul>"
                     "<li><a href='http://digitizer.sourceforge.net'>Project Home Page</a></li>"
                     "<li><a href='http://sourceforge.net/forum/forum.php?forum_id=229857'>Help Forum<a></li>"
                     "<li><a href='http://sourceforge.net/forum/forum.php?forum_id=229856'>Open Discussion Forum</a></li>"
                     "</ul>"
                     "<p>FFTW 3.X.X Links</p>"
                     "<ul>"
                     "<li><a href='http://www.fftw.org'>Project page</a></li>"
                     "</ul>"
                     "<p>OpenJPEG 2.X Links</p>"
                     "<ul>"
                     "<li><a href='http://www.openjpeg.org'>Project page</a></li>"
                     "</ul>")));
}
