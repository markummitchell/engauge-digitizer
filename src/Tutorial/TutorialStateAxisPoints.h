/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TUTORIAL_STATE_AXIS_POINTS_H
#define TUTORIAL_STATE_AXIS_POINTS_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Axis points panel discusses axis point digitization
class TutorialStateAxisPoints : public TutorialStateAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateAxisPoints (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called when next button is triggered
  void slotNext();

  /// Slot called to return to previous panel
  void slotPrevious();

 private:

  QGraphicsTextItem *m_title;
  QGraphicsPixmapItem *m_background;
  QGraphicsTextItem *m_text0;
  QGraphicsTextItem *m_text1;
  QGraphicsTextItem *m_text2;
  TutorialButton *m_previous;
  TutorialButton *m_next;
};

#endif // TUTORIAL_STATE_AXIS_POINTS_H
