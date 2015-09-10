#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateColorFilter.h"
#include "TutorialStateContext.h"

TutorialStateColorFilter::TutorialStateColorFilter (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context)
{
}

void TutorialStateColorFilter::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::begin ()";

  m_title = createTitle ("Color Filter");
  m_background = createPixmapItem (":/engauge/img/panel_color_filter.png",
                                   QPoint (0, 30));
  m_text0 = createTextItem ("Each curve has Color Filter settings that\n"
                            "are applied in Segment Fill mode. For\n"
                            "black lines the defaults work well, but for\n"
                            "colored lines the settings can be improved",
                            QPoint (260, 30));
  m_text1 = createTextItem ("Step 1 - Select the Settings / Color\n"
                            "Filter menu option",
                            QPoint (285, 115));
  m_text2 = createTextItem ("Step 2 - Select the curve that will\n"
                            "be given the new settings",
                            QPoint (285, 155));
  m_text3 = createTextItem ("Step 3 - Select the mode. Intensity is\n"
                            "suggested for uncolored lines, and Hue\n"
                            "is suggested for colored lines",
                            QPoint (285, 200));
  m_text4 = createTextItem ("Step 4 - Adjust the included range by\n"
                            "dragging the green handles. The graph\n"
                            "shows a histogram distribution of the\n"
                            "values underneath, until the curve is\n"
                            "clear in the preview window below. Click\n"
                            "Ok when finished\n\n"
                            "This ends the tutorial. Good luck!",
                            QPoint (285, 280));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton ("Previous",
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));
}

void TutorialStateColorFilter::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::end ()";

  context().tutorialDlg().scene().removeItem (m_title);
  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  context().tutorialDlg().scene().removeItem (m_text3);
  context().tutorialDlg().scene().removeItem (m_text4);
  // TutorialButton removes itself from the scene

  delete m_title;
  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_text3;
  delete m_text4;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_text3 = 0;
  m_text4 = 0;
  m_previous = 0;
}

void TutorialStateColorFilter::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateColorFilter::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_SEGMENT_FILL);
}
