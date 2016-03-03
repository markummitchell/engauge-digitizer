/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TUTORIAL_BUTTON_RECT_H
#define TUTORIAL_BUTTON_RECT_H

#include <QGraphicsRectItem>

class TutorialButton;

/// This class customizes QGraphicsRectItem so it performs a callback after a mouse event
class TutorialButtonRect : public QGraphicsRectItem
{
 public:
  /// Single constructor
  TutorialButtonRect (TutorialButton &tutorialButton);

  /// Forward mouse event to TutorialButton
  virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

 private:
  TutorialButtonRect ();

  TutorialButton &m_tutorialButton;
};

#endif // TUTORIAL_BUTTON_RECT_H
