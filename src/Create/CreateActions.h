/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_ACTIONS_H
#define CREATE_ACTIONS_H

#include <QObject>

class MainWindow;

/// Class to create actions for MainWindow class. We derive from QObject and
/// use Q_OBJECT so translations work
class CreateActions : public QObject
{
  Q_OBJECT

public:
  /// Single constructor.
  CreateActions();

  /// Create QAction actions
  void create (MainWindow &mw);

private:

  void createDigitize (MainWindow &mw);
  void createEdit (MainWindow &mw);
  void createFile (MainWindow &mw);
  void createHelp (MainWindow &mw);
  void createSettings (MainWindow &mw);
  void createView (MainWindow &mw);

};

#endif // CREATE_ACTIONS_H
