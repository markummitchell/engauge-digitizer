#include "Logger.h"
#include <qdebug.h>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "TutorialButton.h"
#include "TutorialDlg.h"
#include "TutorialStateContext.h"
#include "TutorialStateIntroduction.h"

TutorialStateIntroduction::TutorialStateIntroduction (TutorialStateContext &context) : 
  TutorialStateAbstractBase (context)
{
}

void TutorialStateIntroduction::begin ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateIntroduction::begin ()";

  m_title = createTitle ("Introduction");
  m_background = createPixmapItem (":/engauge/img/SpreadsheetsForDoc.png",
                                   QPoint (0, 0));
  m_text0 = createTextItem ("Engauge Digitizer starts with\n"
                            "images of graphs and maps.",
                            QPoint (200, 40));
  m_text1 = createTextItem ("You create (or digitize) points along\n"
                            "the graph and map curves.",
                            QPoint (240, 180));
  m_text2 = createTextItem ("The digitized curve points can be\n"
                            "exported, as numbers, to other software tools.",
                            QPoint (210, 330));

  QSize backgroundSize = context().tutorialDlg().backgroundSize();

  m_next = new TutorialButton ("Next",
                               context().tutorialDlg().scene());
  m_next->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_next->size ().width (),
                               backgroundSize.height () - buttonMargin () - m_next->size ().height ()));
  connect (m_next, SIGNAL (signalTriggered ()), this, SLOT (slotNext ()));
}

void TutorialStateIntroduction::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateIntroduction::end ()";

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
  delete m_next;

  m_title = 0;
  m_background = 0;
  m_text0 = 0;
  m_text1 = 0;
  m_text2 = 0;
  m_next = 0;
}

void TutorialStateIntroduction::slotNext ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateIntroduction::slotNext";

  context().requestDelayedStateTransition (TUTORIAL_STATE_AXIS_POINTS);
}
