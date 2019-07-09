/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TUTORIAL_STATE_INTRODUCTION_H
#define TUTORIAL_STATE_INTRODUCTION_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Introduction state/panel is the first panel the user sees
class TutorialStateIntroduction : public TutorialStateAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateIntroduction (TutorialStateContext &context);
  
  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called when next button is triggered
  void slotNext();

 private:

  QGraphicsTextItem *m_title;
  QGraphicsPixmapItem *m_background;
  QGraphicsTextItem *m_text0;
  QGraphicsTextItem *m_text1;
  QGraphicsTextItem *m_text2;
  TutorialButton *m_next;
};

#endif // TUTORIAL_STATE_INTRODUCTION_H
