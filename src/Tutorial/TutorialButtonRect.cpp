#include "Logging.h"
#include "TutorialButton.h"
#include "TutorialButtonRect.h"

TutorialButtonRect::TutorialButtonRect (TutorialButton &tutorialbutton) :
  m_tutorialButton (tutorialButton)
{
}

void TutorialButtonRect::mouseReleaseEvent (QGraphicsSceneMouseEvent *event)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TutorialButtonRect::mouseReleaseEvent";

  m_tutorialButton->handleTriggered ();
}


