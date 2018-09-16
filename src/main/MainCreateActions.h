/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MAIN_CREATE_ACTIONS_H
#define MAIN_CREATE_ACTIONS_H

#include <QObject>

class MainWindow;

/// Class to create actions for MainWindow class. This is derived from QObject 
/// so the tr function can be accessed more easily
class MainCreateActions : public QObject
{
public:
  /// Single constructor.
  MainCreateActions();

  /// Create QAction actions
  void create (MainWindow &mw);

private:

  void createActionsDigitize (MainWindow &mw);
  void createActionsEdit (MainWindow &mw);
  void createActionsFile (MainWindow &mw);
  void createActionsHelp (MainWindow &mw);
  void createActionsSettings (MainWindow &mw);
  void createActionsView (MainWindow &mw);

};

#endif // MAIN_CREATE_ACTIONS_H
