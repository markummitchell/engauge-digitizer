#ifndef CHECKER_STATE_CONTEXT_H
#define CHECKER_STATE_CONTEXT_H

#include "CheckerStateAbstractBase.h"
#include <QVector>

/// Context class for checker state machine. This removes some tricky state processing from MainWindow
class CheckerStateContext
{
public:
  /// Single constructor.
  CheckerStateContext();
  virtual ~CheckerStateContext();

  /// Initiate state transition to be performed later, when CheckerState is off the stack
  void requestDelayedStateTransition (CheckerState checkerState);

private:

  QVector<CheckerStateAbstractBase*> m_states;
  CheckerState m_currentState;
  CheckerState m_requestedState; // Same as m_currentState until requestStateTransition is called
};

#endif // CHECKER_STATE_CONTEXT_H
