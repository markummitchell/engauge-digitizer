/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include "MainCreateTutorial.h"
#include "MainWindow.h"
#include "TutorialDlg.h"

MainCreateTutorial::MainCreateTutorial()
{
}

void MainCreateTutorial::create(MainWindow &mw)
{
  LOG4CPP_INFO_S ((*mainCat)) << "MainCreateTutorial::create";

  mw.m_tutorialDlg = new TutorialDlg (&mw);
  mw.m_tutorialDlg->setModal (true);
  mw.m_tutorialDlg->setMinimumSize (500, 400);
  mw.m_tutorialDlg->hide();
}
