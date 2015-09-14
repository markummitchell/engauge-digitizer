#ifndef TUTORIAL_STATE_SEGMENT_FILL_H
#define TUTORIAL_STATE_SEGMENT_FILL_H

#include "TutorialStateAbstractBase.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialButton;
class TutorialStateContext;

/// Segment fill panel discusses the digitization of points along curve lines
class TutorialStateSegmentFill : public TutorialStateAbstractBase
{
  Q_OBJECT;

 public:
  /// Single constructor
  TutorialStateSegmentFill (TutorialStateContext &context);

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

#endif // TUTORIAL_STATE_SEGMENT_FILL_H
