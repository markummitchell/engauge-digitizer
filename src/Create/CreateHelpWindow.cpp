/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CreateHelpWindow.h"
#include "HelpWindow.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QAction>

CreateHelpWindow::CreateHelpWindow()
{
}

void CreateHelpWindow::create (MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CreateHelpWindow::create";

#if !defined(OSX_DEBUG) && !defined(OSX_RELEASE)
  mw.m_helpWindow = new HelpWindow (&mw);
  mw.m_helpWindow->hide ();
  mw.addDockWidget (Qt::RightDockWidgetArea,
                    mw.m_helpWindow); // Dock area is required by addDockWidget but immediately overridden in next line
  mw.m_helpWindow->setFloating (true);

  connect (mw.m_actionHelpHelp, SIGNAL (triggered ()), mw.m_helpWindow, SLOT (show ()));
#endif
}

