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
  TutorialStateAbstractBase (context),
  m_title (nullptr),
  m_background (nullptr),
  m_text0 (nullptr),
  m_text1 (nullptr),
  m_text2 (nullptr),
  m_text3 (nullptr),
  m_previous (nullptr)
{
}

void TutorialStateChecklistWizardAbstract::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateChecklistWizardAbstract::begin ()";

  context().tutorialDlg().scene().clear ();

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

  // It is not safe to remove and deallocate items here since an active TutorialButton
  // may be on the stack. So we clear the scene as the first step in the next begin()
}

TutorialButton *TutorialStateChecklistWizardAbstract::previous()
{
  return m_previous;
}
