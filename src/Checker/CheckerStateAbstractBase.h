#ifndef CHECKER_STATE_ABSTRACT_BASE_H
#define CHECKER_STATE_ABSTRACT_BASE_H

class CheckerStateContext;

/// Set of possible states of axes checker.
enum CheckerState {
  CHECKER_STATE_TRANSFORM_DEFINED,
  CHECKER_STATE_TRANSFORM_UNDEFINED,
  NUM_CHECKER_STATES
};

/// Base class for all checker states. This serves as an interface to CheckerStateContext
class CheckerStateAbstractBase
{
public:
  /// Single constructor.
  CheckerStateAbstractBase(CheckerStateContext &context);
  virtual ~CheckerStateAbstractBase();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state
  virtual void begin() = 0;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end() = 0;

protected:
  /// Reference to the CheckerStateContext that contains all the CheckerStateAbstractBase subclasses, without const.
  CheckerStateContext &context ();

private:
  CheckerStateAbstractBase();

  CheckerStateContext &m_context;
};

#endif // CHECKER_STATE_ABSTRACT_BASE_H
