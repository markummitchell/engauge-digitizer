#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "BackgroundStateNone.h"
#include "BackgroundStateOriginal.h"
#include "EngaugeAssert.h"
#include "Logger.h"

BackgroundStateContext::BackgroundStateContext()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::BackgroundStateContext";

  // These states follow the same order as the BackgroundState enumeration
  m_states.insert (BACKGROUND_STATE_ORIGINAL, new BackgroundStateOriginal (*this));
  m_states.insert (BACKGROUND_STATE_CURVE   , new BackgroundStateCurve    (*this));
  m_states.insert (BACKGROUND_STATE_NONE    , new BackgroundStateNone     (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_BACKGROUND_STATES);

  m_currentState = NUM_BACKGROUND_STATES; // Value that forces a transition right away
  requestStateTransition (BACKGROUND_STATE_ORIGINAL);
}

void BackgroundStateContext::completeRequestedStateTransitionIfExists()
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::completeRequestedStateTransitionIfExists";

  if (m_currentState != m_requestedState) {

    // A transition is waiting so perform it

    if (m_currentState != NUM_BACKGROUND_STATES) {

      // This is not the first state so close the previous state
      m_states [m_currentState]->end ();
    }

    // Start the new state
    m_currentState = m_requestedState;
    m_states [m_requestedState]->begin ();
  }
}

void BackgroundStateContext::requestStateTransition (BackgroundState backgroundState)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::requestStateTransition";

  m_requestedState = backgroundState;
}
