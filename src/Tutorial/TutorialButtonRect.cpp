#include "Logger.h"
#include "TutorialButton.h"
#include "TutorialButtonRect.h"

TutorialButtonRect::TutorialButtonRect (TutorialButton &tutorialButton) :
  m_tutorialButton (tutorialButton)
{
  setAcceptHoverEvents(true);
  setFlag (QGraphicsItem::ItemIsSelectable);
}

void TutorialButtonRect::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialButtonRect::mouseReleaseEvent";

  QGraphicsRectItem::mouseReleaseEvent (event);

  m_tutorialButton.handleTriggered ();
}
