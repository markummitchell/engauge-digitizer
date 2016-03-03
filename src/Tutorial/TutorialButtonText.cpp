/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
