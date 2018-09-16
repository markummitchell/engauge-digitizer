/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MAIN_CREATE_STATUS_BAR_H
#define MAIN_CREATE_STATUS_BAR_H

#include <QObject>

class MainWindow;

/// Class to create status bar for MainWindow class. This is derived from QObject 
/// so the tr function can be accessed more easily
class MainCreateStatusBar : public QObject
{
public:
  /// Single constructor.
  MainCreateStatusBar();

  /// Create QStatusBar
  void create (MainWindow &mw);

};

#endif // MAIN_CREATE_STATUS_BAR_H
