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

  m_title = createTitle ("Point Match");
  m_background = createPixmapItem (":/engauge/img/SpreadsheetsForDoc.png",
                                   QPoint (0, 0));
  m_text0 = createTextItem ("Engauge Digitizer starts with\n"
                            "images of graphs and maps",
                            QPoint (200, 40));
  m_text1 = createTextItem ("You create (or digitize) points along\n"
                            "the graph and map curves",
                            QPoint (240, 180));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_previous = new TutorialButton ("Previous",
                                   context().tutorialDlg().scene());
  m_previous->setGeometry (QPoint (buttonMargin (),
                                   backgroundSize.height() - buttonMargin() - m_previous->size().height()));
  connect (m_previous, SIGNAL (signalTriggered ()), this, SLOT (slotPrevious ()));

  m_next = new TutorialButton ("Next",
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
  // TutorialButton removes itself from the scene

  delete m_title;
  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_next;
  delete m_previous;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_next = 0;
  m_previous = 0;
}

void TutorialStatePointMatch::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStatePointMatch::slotNextCurves";

//  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}

void TutorialStatePointMatch::slotPrevious ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStatePointMatch::slotPrevious";

  context().requestDelayedStateTransition (TUTORIAL_STATE_CURVE_TYPE);
}
