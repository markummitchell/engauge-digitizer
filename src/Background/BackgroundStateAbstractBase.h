#ifndef BACKGROUND_STATE_ABSTRACT_BASE_H
#define BACKGROUND_STATE_ABSTRACT_BASE_H

/// Set of possible states of background image.
enum BackgroundState {
  BACKGROUND_STATE_ORIGINAL,
  BACKGROUND_STATE_CURVE,
  BACKGROUND_STATE_NONE,
  NUM_BACKGROUND_STATES
};

class BackgroundStateContext;

/// Background image state machine state base class
class BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateAbstractBase(BackgroundStateContext &context);
  ~BackgroundStateAbstractBase();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state.
  virtual void begin() = 0;

  /// Reference to the BackgroundStateContext that contains all the BackgroundStateAbstractBase subclasses, without const.
  BackgroundStateContext &context();

  /// Reference to the BackgroundStateContext that contains all the BackgroundStateAbstractBase subclasses, without const.
  const BackgroundStateContext &context() const;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end() = 0;

private:
  BackgroundStateAbstractBase();

  BackgroundStateContext &m_context;
};

#endif // BACKGROUND_STATE_ABSTRACT_BASE_H
