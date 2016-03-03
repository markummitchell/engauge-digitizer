/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QDockWidget>

/// Dockable help window
class HelpWindow : public QDockWidget
{
  Q_OBJECT;

 public:
  /// Single constructor
  HelpWindow (QWidget *parent);

 private:
  HelpWindow ();

  QString helpPath() const;

};

#endif // HELP_WINDOW_H
