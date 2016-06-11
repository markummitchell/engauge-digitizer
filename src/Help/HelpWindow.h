/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef HELP_WINDOW_H
#define HELP_WINDOW_H

#include <QDockWidget>

/// Dockable help window. Despite a lot of work trying to work with the OSX sandbox, support for the
/// sandbox was never completed since QHelpEngine requires WRITE-access to the collection file. Even
/// trying to create a temporary directory does not work since copying would involve QHelpEngine::copyCollectionFile
/// which copys from the CURRENT collection file (versus just some arbitrary file name)
class HelpWindow : public QDockWidget
{
  Q_OBJECT;

 public:
  /// Single constructor
  HelpWindow (QWidget *parent);

 private:
  HelpWindow ();

#ifndef OSX_RELEASE
  QString helpPath() const;
#endif

};

#endif // HELP_WINDOW_H
