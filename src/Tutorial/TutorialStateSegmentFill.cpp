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
  TutorialStateAbstractBase (context)
{
}

void TutorialStateSegmentFill::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::begin ()";

  m_title = createTitle ("Segment Fill");
  m_background = createPixmapItem (":/engauge/img/panel_segment_fill.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem ("Segment Fill mode places several\n"
                            "points all along the line segments\n"
                            "of a curve. Step 1 - Click on the\n"
                            "Segment Fill button.",
                            QPoint (300, 40));
  m_text1 = createTextItem ("Step 2 - Select the curve the new\n"
                            "points will belong to.",
                            QPoint (300, 140));
  m_text2 = createTextItem ("Step 3 - Move the cursor over a line\n"
                            "segment in the desired curve. If a\n"
                            "green line appears, click on it once\n"
                            "to generate many points.\n\n"
                            "This ends the tutorial. Good luck!",
                            QPoint (300, 220));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton ("Previous",
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));
}

void TutorialStateSegmentFill::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::end ()";

  context().tutorialDlg().scene().removeItem (m_title);
  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  // TutorialButton removes itself from the scene

  delete m_title;
  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_previous = 0;
}

void TutorialStateSegmentFill::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateSegmentFill::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}
