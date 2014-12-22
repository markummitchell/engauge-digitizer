#include "HighlightsStateContext.h"
#include "HighlightsStateTransformDefined.h"
#include "HighlightsStateTransformUndefined.h"

HighlightsStateContext::HighlightsStateContext()
{
  m_states.insert (HIGHLIGHTS_STATE_TRANSFORM_DEFINED  , new HighlightsStateTransformDefined   (*this));
  m_states.insert (HIGHLIGHTS_STATE_TRANSFORM_UNDEFINED, new HighlightsStateTransformUndefined (*this));
  Q_ASSERT (m_states.size () == NUM_HIGHLIGHTS_STATES);

  m_currentState = NUM_HIGHLIGHTS_STATES; // Value that forces a transition right away
}

HighlightsStateContext::~HighlightsStateContext()
{
}

void HighlightsStateContext::requestDelayedStateTransition (HighlightsState highlightsState)
{
  m_requestedState = highlightsState;
}
