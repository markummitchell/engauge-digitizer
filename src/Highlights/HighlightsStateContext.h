#ifndef HIGHLIGHTS_STATE_CONTEXT_H
#define HIGHLIGHTS_STATE_CONTEXT_H

#include "HighlightsStateAbstractBase.h"
#include <QVector>

/// Context class for highlights state machine. This removes some tricky state processing from MainWindow
class HighlightsStateContext
{
public:
  /// Single constructor.
  HighlightsStateContext();
  virtual ~HighlightsStateContext();

  /// Initiate state transition to be performed later, when HighlightsState is off the stack
  void requestDelayedStateTransition (HighlightsState highlightsState);

private:

  QVector<HighlightsStateAbstractBase*> m_states;
  HighlightsState m_currentState;
  HighlightsState m_requestedState; // Same as m_currentState until requestStateTransition is called
};

#endif // HIGHLIGHTS_STATE_CONTEXT_H
