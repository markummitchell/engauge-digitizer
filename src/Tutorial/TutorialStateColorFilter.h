/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TUTORIAL_STATE_COLOR_FILTER_H
#define TUTORIAL_STATE_COLOR_FILTER_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Color filter panel discusses the curve-specific color filtering
class TutorialStateColorFilter : public TutorialStateAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateColorFilter (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called to return to previous panel
  void slotBack();

 private:

  QGraphicsTextItem *m_title;
  QGraphicsPixmapItem *m_background;
  QGraphicsTextItem *m_text0;
  QGraphicsTextItem *m_text1;
  QGraphicsTextItem *m_text2;
  QGraphicsTextItem *m_text3;
  QGraphicsTextItem *m_text4;
  TutorialButton *m_back;
};

#endif // TUTORIAL_STATE_COLOR_FILTER_H
