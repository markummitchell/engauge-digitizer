#ifndef TUTORIAL_STATE_ABSTRACT_BASE_H
#define TUTORIAL_STATE_ABSTRACT_BASE_H

#include <QObject>

enum TutorialState {
  TUTORIAL_STATE_AXIS_POINTS,
  TUTORIAL_STATE_CHECKLIST_WIZARD_LINES,
  TUTORIAL_STATE_CHECKLIST_WIZARD_POINTS,
  TUTORIAL_STATE_COLOR_FILTER,
  TUTORIAL_STATE_CURVE_SELECTION,
  TUTORIAL_STATE_CURVE_TYPE,
  TUTORIAL_STATE_INTRODUCTION,
  TUTORIAL_STATE_POINT_MATCH,
  TUTORIAL_STATE_SEGMENT_FILL,
  NUM_TUTORIAL_STATES
};

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class TutorialStateContext;

/// One state manages one panel of the tutorial
class TutorialStateAbstractBase : public QObject
{
 public:
  /// Single constructor
  TutorialStateAbstractBase(TutorialStateContext &context);
  virtual ~TutorialStateAbstractBase();

  /// Transition into this state
  virtual void begin () = 0;

  /// Transition out of this state
  virtual void end () = 0;

 protected:

  /// Buttons are placed up against bottom side, and left or right side, separated by this margin
  int buttonMargin () const;

  /// Context class for the tutorial state machine
  TutorialStateContext &context ();

  /// Factory method for pixmap items
  QGraphicsPixmapItem *createPixmapItem (const QString &resource,
                                         const QPoint &pos);

  /// Factory method for text items
  QGraphicsTextItem *createTextItem (const QString &text,
                                     const QPoint &pos);

  /// Factory method for title items
  QGraphicsTextItem *createTitle (const QString &text);

 private:
  TutorialStateAbstractBase();

  TutorialStateContext &m_context;
};

#endif // TUTORIAL_STATE_ABSTRACT_BASE_H
