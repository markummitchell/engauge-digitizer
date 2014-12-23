#include "CheckerStateContext.h"
#include "CheckerStateTransformDefined.h"
#include "CheckerStateTransformUndefined.h"

CheckerStateContext::CheckerStateContext()
{
  m_states.insert (CHECKER_STATE_TRANSFORM_DEFINED  , new CheckerStateTransformDefined   (*this));
  m_states.insert (CHECKER_STATE_TRANSFORM_UNDEFINED, new CheckerStateTransformUndefined (*this));
  Q_ASSERT (m_states.size () == NUM_CHECKER_STATES);

  m_currentState = NUM_CHECKER_STATES; // Value that forces a transition right away
}

CheckerStateContext::~CheckerStateContext()
{
}

void CheckerStateContext::requestDelayedStateTransition (CheckerState checkerState)
{
  m_requestedState = checkerState;
}
