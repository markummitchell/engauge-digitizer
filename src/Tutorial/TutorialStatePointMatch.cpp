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
#include "TutorialStateContext.h"
#include "TutorialStatePointMatch.h"

TutorialStatePointMatch::TutorialStatePointMatch (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context)
{
}

void TutorialStatePointMatch::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStatePointMatch::begin ()";

  m_title = createTitle (tr ("Point Match"));
  m_background = createPixmapItem (":/engauge/img/panel_point_match.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem (tr ("In Point Match mode, you pick\n"
                                "one sample point, and Engauge\n"
                                "then finds all matching points.\n\n"
                                "Step 1 - Click on Point Match mode."),
                            QPoint (300, 40));
  m_text1 = createTextItem (tr ("Step 2 - Select the curve the new\n"
                                "points will belong to."),
                            QPoint (320, 140));
  m_text2 = createTextItem (tr ("Step 3 - Click on a typical point.\n"
                                "The circle turns green when it\n"
                                "contains what may be a point."),
                            QPoint (320, 200));
  m_text3 = createTextItem (tr ("Step 4 - Engauge will show a\n"
                                "matched point with a yellow cross.\n"
                                "Press the Right Arrow key to accept\n"
                                "the matched point. Repeat this step\n"
                                "until there are no more points."),
                            QPoint (320, 270));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton (tr ("Previous"),
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_next = new TutorialButton (tr ("Next"),
                               context().tutorialDlg().scene());
  m_next->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_next->size ().width (),
                               backgroundSize.height () - buttonMargin () - m_next->size ().height ()));
  connect (m_next, SIGNAL (signalTriggered ()), this, SLOT (slotNext ()));
}

void TutorialStatePointMatch::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStatePointMatch::end ()";

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
  delete m_next;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_text3 = 0;
  m_next = 0;
  m_previous = 0;
}

void TutorialStatePointMatch::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStatePointMatch::slotNext";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CHECKLIST_WIZARD_POINTS);
}

void TutorialStatePointMatch::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStatePointMatch::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}
