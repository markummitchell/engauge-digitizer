/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_TOOLBARS_H
#define CREATE_TOOLBARS_H

#include <QObject>

class MainWindow;

/// Class to create toolbars for MainWindow class. This is derived from QObject 
/// so the tr function can be accessed more easily
class CreateToolBars : public QObject
{
public:
  /// Single constructor.
  CreateToolBars();

  /// Create QToolbar toolbars
  void create (MainWindow &mw);

};

#endif // CREATE_TOOLBARS_H
