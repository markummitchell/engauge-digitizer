#include "CmdMediator.h"
#include "TransformationStateAbstractBase.h"
#include "TransformationStateContext.h"
#include "TransformationStateDefined.h"
#include "TransformationStateUndefined.h"

TransformationStateContext::TransformationStateContext()
{
  m_states.insert (TRANSFORMATION_STATE_DEFINED  , new TransformationStateDefined   (*this));
  m_states.insert (TRANSFORMATION_STATE_UNDEFINED, new TransformationStateUndefined (*this));
  Q_ASSERT (m_states.size () == NUM_TRANSFORMATION_STATES);

  m_currentState = NUM_TRANSFORMATION_STATES; // Value that forces a transition right away
}

TransformationStateContext::~TransformationStateContext()
{
}

void TransformationStateContext::triggerStateTransition (TransformationState transformationState,
                                                         CmdMediator &cmdMediator,
                                                         const Transformation &transformation)
{
  // Transition if we are not already at the requested state
  if (transformationState != m_currentState) {

    // End the current state if there is one
    if (m_currentState != NUM_TRANSFORMATION_STATES) {
      m_states[m_currentState]->end(cmdMediator,
                                    transformation);
    }

    m_currentState = transformationState;

    // Start the requested state
    m_states[m_currentState]->begin(cmdMediator,
                                    transformation);
  }
}
