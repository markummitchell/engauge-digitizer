#include "Logger.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
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

  m_background = new QGraphicsPixmapItem (QPixmap (":/engauge/img/SpreadsheetsForDoc.png"));
  m_background->setPos (0, 0);
  context().tutorialDlg().scene().addItem (m_background);
}

void TutorialStateIntroduction::end ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialStateIntroduction::end ()";

  context().tutorialDlg().scene().removeItem (m_background);
}
