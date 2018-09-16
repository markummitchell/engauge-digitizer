/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "MainCreateStatusBar.h"
#include "MainWindow.h"
#include "StatusBar.h"

MainCreateStatusBar::MainCreateStatusBar()
{
}

void MainCreateStatusBar::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainCreateStatusBar::create";

  mw.m_statusBar = new StatusBar (*mw.statusBar ());
  connect (&mw, SIGNAL (signalZoom(int)), mw.m_statusBar, SLOT (slotZoom(int)));
  connect (mw.m_statusBar, SIGNAL (signalZoom (int)), &mw, SLOT (slotViewZoom (int)));
}
