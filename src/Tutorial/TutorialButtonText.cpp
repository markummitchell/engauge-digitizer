#include "Logger.h"
#include "TutorialButton.h"
#include "TutorialButtonRect.h"
#include "TutorialButtonText.h"

TutorialButtonText::TutorialButtonText (TutorialButton &tutorialButton,
                                        const QString &text,
                                        TutorialButtonRect *rect) :
  QGraphicsTextItem (text,
                     rect),
  m_tutorialButton (tutorialButton)
{
  setAcceptHoverEvents(true);
  setFlag (QGraphicsItem::ItemIsSelectable);
}

void TutorialButtonText::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialButtonText::mouseReleaseEvent";

  QGraphicsTextItem::mouseReleaseEvent (event);

  m_tutorialButton.handleTriggered ();
}
