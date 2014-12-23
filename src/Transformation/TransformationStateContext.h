#ifndef TRANSFORMATION_STATE_CONTEXT_H
#define TRANSFORMATION_STATE_CONTEXT_H

#include <QVector>
#include "TransformationStateAbstractBase.h"

class CmdMediator;
class Transformation;

/// Context class for transformation state machine. This removes some tricky state processing from MainWindow.
/// Unlike typical state machines, the transitions are driven directly from the outside rather than indirectly
/// by events that are processed by the states (this has triggerStateTransition rather than requestStateTransition)
class TransformationStateContext
{
public:
  /// Single constructor.
  TransformationStateContext();
  virtual ~TransformationStateContext();

  /// Trigger a state transition to be performed immediately.
  void triggerStateTransition (TransformationState transformationState,
                               CmdMediator &cmdMediator,
                               const Transformation &transformation);

private:

  QVector<TransformationStateAbstractBase*> m_states;
  TransformationState m_currentState;
};

#endif // TRANSFORMATION_STATE_CONTEXT_H
