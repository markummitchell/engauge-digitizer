/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CREATE_COMMAND_STACK_SHADOW_H
#define CREATE_COMMAND_STACK_SHADOW_H

#include <QObject>

class MainWindow;

/// Class to create CmdStackShadow for MainWindow class. We derive from QObject and
/// use Q_OBJECT so translations work
class CreateCommandStackShadow : public QObject
{
  Q_OBJECT

public:
  /// Single constructor.
  CreateCommandStackShadow ();

  /// Create shadow command stack
  void create (MainWindow &mw);

};

#endif // CREATE_COMMAND_STACK_SHADOW_H
