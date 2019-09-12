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
#include "TutorialStateSegmentFill.h"

TutorialStateSegmentFill::TutorialStateSegmentFill (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context),
  m_title (nullptr),
  m_background (nullptr),
  m_text0 (nullptr),
  m_text1 (nullptr),
  m_text2 (nullptr),
  m_previous (nullptr),
  m_next (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::TutorialStateSegmentFill";
}

void TutorialStateSegmentFill::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::begin ()";

  context().tutorialDlg().scene().clear ();

  m_title = createTitle (tr ("Segment Fill"));
  m_background = createPixmapItem (":/engauge/img/panel_segment_fill.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem (tr ("Segment Fill mode places several\n"
                                "points all along the line segments\n"
                                "of a curve. Step 1 - Click on the\n"
                                "Segment Fill button."),
                            QPoint (300, 40));
  m_text1 = createTextItem (tr ("Step 2 - Select the curve the new\n"
                                "points will belong to."),
                            QPoint (300, 140));
  m_text2 = createTextItem (tr ("Step 3 - Move the cursor over a line\n"
                                "segment in the desired curve. If a\n"
                                "green line appears, click on it once\n"
                                "to generate many points."),
                            QPoint (300, 220));

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

void TutorialStateSegmentFill::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::end ()";

  // It is not safe to remove and deallocate items here since an active TutorialButton
  // may be on the stack. So we clear the scene as the first step in the next begin()
}

void TutorialStateSegmentFill::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::slotNext";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CHECKLIST_WIZARD_LINES);
}

void TutorialStateSegmentFill::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}
