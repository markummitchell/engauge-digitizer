/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineViewStateAbstractBase.h"
#include "GuidelineViewStateContext.h"
#include "GuidelineViewStateEdit.h"
#include "GuidelineViewStateHide.h"
#include "GuidelineViewStateLock.h"

GuidelineViewStateContext::GuidelineViewStateContext ()
{
  m_states.insert (GUIDELINE_VIEW_STATE_EDIT, new GuidelineViewStateEdit  (*this));
  m_states.insert (GUIDELINE_VIEW_STATE_HIDE, new GuidelineViewStateHide  (*this));
  m_states.insert (GUIDELINE_VIEW_STATE_LOCK, new GuidelineViewStateLock  (*this));  
  ENGAUGE_ASSERT (m_states.size () == NUM_GUIDELINE_VIEW_STATES);

  m_currentState = NUM_GUIDELINE_VIEW_STATES; // Value that forces a transition right away
  m_nextState = GUIDELINE_VIEW_STATE_HIDE;

  transitionIfRequested ();
}

GuidelineViewStateContext::~GuidelineViewStateContext ()
{
}

GuidelineViewState GuidelineViewStateContext::guidelineViewState () const
{
  return m_currentState;
}

void GuidelineViewStateContext::handleStateChange (GuidelineViewState state)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_VIEW_STATES);

  m_states[m_currentState]->handleStateChange (state);
  transitionIfRequested ();
}

void GuidelineViewStateContext::requestStateTransition (GuidelineViewState state)
{
  ENGAUGE_ASSERT (state != NUM_GUIDELINE_VIEW_STATES);

  m_nextState = state;
}

GuidelineViewState GuidelineViewStateContext::state() const
{
  return m_currentState;
}

void GuidelineViewStateContext::transitionIfRequested ()
{
  if (m_currentState != m_nextState) {

    // End the current state if there is one
    if (m_currentState != NUM_GUIDELINE_VIEW_STATES) {
      m_states[m_currentState]->end ();
    }

    m_currentState = m_nextState;

    // Start the requested state
    m_states[m_currentState]->begin();
  }
}
