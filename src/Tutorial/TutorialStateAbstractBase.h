#ifndef TUTORIAL_STATE_ABSTRACT_BASE_H
#define TUTORIAL_STATE_ABSTRACT_BASE_H

enum TutorialState {
  TUTORIAL_STATE_INTRODUCTION,
  NUM_TUTORIAL_STATES
};

class TutorialStateContext;

/// One state manages one panel of the tutorial
class TutorialStateAbstractBase
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
  /// Context class for the tutorial state machine
  TutorialStateContext &context ();

 private:
  TutorialStateAbstractBase();

  TutorialStateContext &m_context;
};

#endif // TUTORIAL_STATE_ABSTRACT_BASE_H
