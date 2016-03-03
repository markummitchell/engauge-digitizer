/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CHECKLIST_LINE_EDIT_H
#define CHECKLIST_LINE_EDIT_H

#include <QLineEdit>

/// Adds key event handling to QLineEdit
class ChecklistLineEdit : public QLineEdit
{
  Q_OBJECT;

 public:
  /// Single constructor
  ChecklistLineEdit();

  /// Intercept the key press event
  virtual void keyReleaseEvent (QKeyEvent *event);

 signals:
  /// Signal that user has just released a key
  void signalKeyRelease();
};

#endif // CHECKLIST_LINE_EDIT_H
