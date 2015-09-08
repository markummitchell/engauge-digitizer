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

  context().setWindowTitle ("Curve Type");

  m_background = new QGraphicsPixmapItem (QPixmap (":/engauge/img/panel_lines_points.png"));
  m_background->setPos (0, 0);
  context().tutorialDlg().scene().addItem (m_background);

  m_text0 = new QGraphicsTextItem ("The next steps depend on how the curves\n"
                                   "are drawn, in terms of lines and points");
  m_text0->setPos (240, 20);
  context().tutorialDlg().scene().addItem (m_text0);

  m_text1 = new QGraphicsTextItem ("If the curves are drawn\n"
                                   "with lines then click on\n"
                                   "Next (Lines)");
  m_text1->setPos (265, 120);
  context().tutorialDlg().scene().addItem (m_text1);

  m_text2 = new QGraphicsTextItem ("If the curves are drawn\n"
                                   "without lines and only\n"
                                   "with points, then click on\n"
                                   "Next (Points)");
  m_text2->setPos (265, 270);
  context().tutorialDlg().scene().addItem (m_text2);

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton ("Previous",
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height () - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_nextCurves = new TutorialButton ("Next (Lines)",
                                     context().tutorialDlg().scene());
  m_nextCurves->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_nextCurves->size ().width (),
                                     backgroundSize.height () / 3.0 - m_nextCurves->size ().height () / 2.0));
  connect (m_nextCurves, SIGNAL (signalTriggered ()), this, SLOT (slotNextCurves ()));

  m_nextLines = new TutorialButton ("Next (Points)",
                                    context().tutorialDlg().scene());
  m_nextLines->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_nextLines->size ().width (),
                                    backgroundSize.height () * 2.0 / 3.0 - m_nextLines->size ().height () / 2.0));
  connect (m_nextLines, SIGNAL (signalTriggered ()), this, SLOT (slotNextLines ()));
}

void TutorialStateCurveType::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateCurveType::end ()";

  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  // TutorialButton removes itself from the scene

  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_nextCurves;
  delete m_nextLines;
  delete m_previous;

  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_nextCurves = 0;
  m_nextLines = 0;
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

  context().requestDelayedStateTransition (TUTORIAL_STATE_AXIS_POINTS);
}
