/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_MENUS_H
#define CREATE_MENUS_H

#include <QObject>

class MainWindow;

/// Class to create QDockWidget items for MainWindow class. This is derived from QObject
/// so the tr function can be accessed more easily
class CreateDockableWidgets : public QObject
{
public:
  /// Single constructor.
  CreateDockableWidgets();

  /// Create QMenu menu items
  void create (MainWindow &mw);

};

#endif // CREATE_MENUS_H
