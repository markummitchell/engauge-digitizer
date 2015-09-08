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

  context().setWindowTitle ("Introduction");

  m_background = new QGraphicsPixmapItem (QPixmap (":/engauge/img/SpreadsheetsForDoc.png"));
  m_background->setPos (0, 0);
  context().tutorialDlg().scene().addItem (m_background);

  m_text0 = new QGraphicsTextItem ("Engauge Digitizer starts with\n"
                                   "images of graphs and maps");
  m_text0->setPos (200, 40);
  context().tutorialDlg().scene().addItem (m_text0);

  m_text1 = new QGraphicsTextItem ("You create (or digitize) points along\n"
                                   "the graph and map curves");
  m_text1->setPos (240, 180);
  context().tutorialDlg().scene().addItem (m_text1);

  m_text2 = new QGraphicsTextItem ("The digitized curve points can be\n"
                                   "exported, as numbers, to other software tools");
  m_text2->setPos (210, 330);
  context().tutorialDlg().scene().addItem (m_text2);

  m_next = new TutorialButton ("Next",
                               context().tutorialDlg().scene());
  QSize backgroundSize = context().tutorialDlg().backgroundSize();
  m_next->setGeometry (QPoint (backgroundSize.width () - buttonMargin () - m_next->size ().width (),
                               backgroundSize.height () - buttonMargin () - m_next->size ().height ()));
  connect (m_next, SIGNAL (signalTriggered ()), this, SLOT (slotNext ()));
}

void TutorialStateIntroduction::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateIntroduction::end ()";

  context().tutorialDlg().scene().removeItem (m_background);
  context().tutorialDlg().scene().removeItem (m_text0);
  context().tutorialDlg().scene().removeItem (m_text1);
  context().tutorialDlg().scene().removeItem (m_text2);
  // TutorialButton removes itself from the scene

  delete m_background;
  delete m_text0;
  delete m_text1;
  delete m_text2;
  delete m_next;

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
