#ifndef TUTORIAL_STATE_ABSTRACT_BASE_H
#define TUTORIAL_STATE_ABSTRACT_BASE_H

#include <QObject>

enum TutorialState {
  TUTORIAL_STATE_AXIS_POINTS,
  TUTORIAL_STATE_CURVE_TYPE,
  TUTORIAL_STATE_INTRODUCTION,
  TUTORIAL_STATE_POINT_MATCH,
  TUTORIAL_STATE_SEGMENT_FILL,
  NUM_TUTORIAL_STATES
};

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

 private:
  TutorialStateAbstractBase();

  TutorialStateContext &m_context;
};

#endif // TUTORIAL_STATE_ABSTRACT_BASE_H
