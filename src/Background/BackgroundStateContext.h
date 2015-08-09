#ifndef BACKGROUND_STATE_CONTEXT_H
#define BACKGROUND_STATE_CONTEXT_H

#include "BackgroundStateAbstractBase.h"
#include <QVector>

/// Context class that manages the background image state machine.
/// Overall strategy is that changing the currently selected curve should not affect the background
/// image if the original image is being shown, or no image is being shown. However, if the
/// curve-specific color filter image is being shown, then it should be replaced by the filtered
/// image specific to the new curve
class BackgroundStateContext
{
 public:
  /// Single constructor
  BackgroundStateContext();

  /// Initiate state transition to be performed later, when BackgroundState is off the stack
  void requestStateTransition (BackgroundState backgroundState);

private:

  void completeRequestedStateTransitionIfExists ();

  QVector<BackgroundStateAbstractBase*> m_states;
  BackgroundState m_currentState;
  BackgroundState m_requestedState; // Same as m_currentState until requestStateTransition is called
};

#endif // BACKGROUND_STATE_CONTEXT_H
