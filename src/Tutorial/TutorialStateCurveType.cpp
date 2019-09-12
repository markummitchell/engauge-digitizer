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
#include <qmath.h>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateContext.h"
#include "TutorialStateCurveType.h"

TutorialStateCurveType::TutorialStateCurveType (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context),
  m_title (nullptr),
  m_background (nullptr),
  m_text0 (nullptr),
  m_text1 (nullptr),
  m_text2 (nullptr),
  m_previous (nullptr),
  m_nextLines (nullptr),
  m_nextPoints (nullptr)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::TutorialStateCurveType";
}

void TutorialStateCurveType::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::begin ()";

  context().tutorialDlg().scene().clear ();

  m_title = createTitle (tr ("Curve Type"));
  m_background = createPixmapItem (":/engauge/img/panel_lines_points.png",
                                   QPoint (0, 0));
  m_text0 = createTextItem (tr ("The next steps depend on how the curves\n"
                                "are drawn, in terms of lines and points."),
                            QPoint (240, 40));
  m_text1 = createTextItem (tr ("If the curves are drawn\n"
                                "with lines (with or without\n"
                                "points) then click on\n"
                                "Next (Lines)."),
                            QPoint (265, 110));
  m_text2 = createTextItem (tr ("If the curves are drawn\n"
                                "without lines and only\n"
                                "with points, then click on\n"
                                "Next (Points)."),
                            QPoint (265, 270));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton (tr ("Previous"),
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height () - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_nextLines = new TutorialButton (tr ("Next (Lines)"),
                                    context().tutorialDlg().scene());
  m_nextLines->setGeometry (QPoint (qFloor (backgroundSize.width () - buttonMargin () - m_nextLines->size ().width ()),
                                    qFloor (backgroundSize.height () / 3.0 - m_nextLines->size ().height () / 2.0)));
  connect (m_nextLines, SIGNAL (signalTriggered ()), this, SLOT (slotNextCurves ()));

  m_nextPoints = new TutorialButton (tr ("Next (Points)"),
                                     context().tutorialDlg().scene());
  m_nextPoints->setGeometry (QPoint (qFloor (backgroundSize.width () - buttonMargin () - m_nextPoints->size ().width ()),
                                     qFloor (backgroundSize.height () * 2.0 / 3.0 - m_nextPoints->size ().height () / 2.0)));
  connect (m_nextPoints, SIGNAL (signalTriggered ()), this, SLOT (slotNextLines ()));
}

void TutorialStateCurveType::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::end ()";

  // It is not safe to remove and deallocate items here since an active TutorialButton
  // may be on the stack. So we clear the scene as the first step in the next begin()
}

void TutorialStateCurveType::slotNextCurves ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::slotNextCurves";

  context().requestDelayedStateTransition (TUTORIAL_STATE_SEGMENT_FILL);
}

void TutorialStateCurveType::slotNextLines ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::slotNextLines";

  context().requestDelayedStateTransition (TUTORIAL_STATE_POINT_MATCH);
}

void TutorialStateCurveType::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::slotNextCurves";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_SELECTION);
}
