#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateContext.h"
#include "TutorialStateCurveType.h"

TutorialStateCurveType::TutorialStateCurveType (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context)
{
}

void TutorialStateCurveType::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::begin ()";

  m_title = createTitle ("Curve Type");
  m_background = createPixmapItem (":/engauge/img/panel_lines_points.png",
                                   QPoint (0, 0));
  m_text0 = createTextItem ("The next steps depend on how the curves\n"
                            "are drawn, in terms of lines and points.",
                            QPoint (240, 40));
  m_text1 = createTextItem ("If the curves are drawn\n"
                            "with lines (with or without\n"
                            "points) then click on\n"
                            "Next (Lines).",
                            QPoint (265, 110));
  m_text2 = createTextItem ("If the curves are drawn\n"
                            "without lines and only\n"
                            "with points, then click on\n"
                            "Next (Points).",
                            QPoint (265, 270));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton ("Previous",
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height () - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_nextLines = new TutorialButton ("Next (Lines)",
                                     context().tutorialDlg().scene());
  m_nextLines->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_nextLines->size ().width (),
                                     backgroundSize.height () / 3.0 - m_nextLines->size ().height () / 2.0));
  connect (m_nextLines, SIGNAL (signalTriggered ()), this, SLOT (slotNextCurves ()));

  m_nextPoints = new TutorialButton ("Next (Points)",
                                    context().tutorialDlg().scene());
  m_nextPoints->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_nextPoints->size ().width (),
                                    backgroundSize.height () * 2.0 / 3.0 - m_nextPoints->size ().height () / 2.0));
  connect (m_nextPoints, SIGNAL (signalTriggered ()), this, SLOT (slotNextLines ()));
}

void TutorialStateCurveType::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::end ()";

  context().tutorialDlg().scene().removeItem (m_title);
  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  // TutorialButtons removes themselves from the scene

  delete m_title;
  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_nextLines;
  delete m_nextPoints;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_nextLines = 0;
  m_nextPoints = 0;
  m_previous = 0;
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
