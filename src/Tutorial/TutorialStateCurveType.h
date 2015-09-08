#ifndef TUTORIAL_STATE_CURVE_TYPE_H
#define TUTORIAL_STATE_CURVE_TYPE_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Curve type state/panel lets user select the curve type (lines or points)
class TutorialStateCurveType : public TutorialStateAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateCurveType (TutorialStateContext &context);

  virtual void begin ();
  virtual void end ();

 public slots:
  /// Slot called when next button for curves is triggered
  void slotNextCurves();

  /// Slot called when next button for lines is triggered
  void slotNextLines();

  /// Slot called to return to previous panel
  void slotPrevious ();

 private:

  QGraphicsPixmapItem *m_background;
  QGraphicsTextItem *m_text0;
  QGraphicsTextItem *m_text1;
  TutorialButton *m_previous;
  TutorialButton *m_nextCurves;
  TutorialButton *m_nextLines;
};

#endif // TUTORIAL_STATE_CURVE_TYPE_H
