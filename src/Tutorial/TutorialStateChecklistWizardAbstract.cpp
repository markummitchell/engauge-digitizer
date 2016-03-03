/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateChecklistWizardAbstract.h"
#include "TutorialStateContext.h"

TutorialStateChecklistWizardAbstract::TutorialStateChecklistWizardAbstract (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context)
{
}

void TutorialStateChecklistWizardAbstract::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardAbstract::begin ()";

  m_title = createTitle (tr ("Checklist Wizard and Checklist Guide"));
  m_background = createPixmapItem (":/engauge/img/panel_checklist.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem (tr ("For new Engauge users, a Checklist Wizard\n"
                                "is available when importing an image file.\n"
                                "This wizard produces a helpful checklist of\n"
                                "steps to follow to digitize the image file."),
                            QPoint (260, 30));
  m_text1 = createTextItem (tr ("Step 1 - Enable the menu option Help /\n"
                                "Checklist Guide Wizard."),
                            QPoint (285, 125));
  m_text2 = createTextItem (tr ("Step 2 - Import the file using File /\n"
                                "Import. The Checklist Wizard will appear\n"
                                "and ask some simple questions to\n"
                                "determine how the image can be\n"
                                "digitized."),
                            QPoint (285, 175));
  m_text3 = createTextItem (tr ("Additional options are available in\n"
                                "the various Settings menus.\n\n"
                                "This ends the tutorial. Good luck!"),
                            QPoint (285, 270));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton (tr ("Previous"),
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height () - buttonMargin() - m_previous->size().height()));
}

void TutorialStateChecklistWizardAbstract::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardAbstract::end ()";

  context().tutorialDlg().scene().removeItem (m_title);
  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  context().tutorialDlg().scene().removeItem (m_text3);
  // TutorialButtons removes themselves from the scene

  delete m_title;
  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_text3;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_text3 = 0;
  m_previous = 0;
}

TutorialButton *TutorialStateChecklistWizardAbstract::previous()
{
  return m_previous;
}
