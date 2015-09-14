#ifndef TUTORIAL_STATE_CURVE_SELECTION_H
#define TUTORIAL_STATE_CURVE_SELECTION_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Curve selection panel discusses how to select a curve, and perform setup on the selected curve
class TutorialStateCurveSelection : public TutorialStateAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateCurveSelection (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called when settings button is triggered
  void slotColorFilter();

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
  QGraphicsTextItem *m_text3;
  TutorialButton *m_previous;
  TutorialButton *m_colorFilter;  
  TutorialButton *m_next;
};

#endif // TUTORIAL_STATE_CURVE_SELECTION_H
