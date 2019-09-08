/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontal.h"
#include "GuidelineStateDeployedVertical.h"
#include "GuidelineStateTemplateHorizontal.h"
#include "GuidelineStateTemplateVertical.h"

GuidelineStateContext::GuidelineStateContext(GuidelineState guidelineStateInitial)
{
  m_states.insert (GUIDELINE_STATE_DEPLOYED_HORIZONTAL  , new GuidelineStateDeployedHorizontal (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_VERTICAL    , new GuidelineStateDeployedVertical   (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL  , new GuidelineStateTemplateHorizontal (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL    , new GuidelineStateTemplateVertical   (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_GUIDELINE_STATES);

  m_currentState = NUM_GUIDELINE_STATES; // Value that forces a transition right away
  m_nextState = guidelineStateInitial;
}

GuidelineStateContext::~GuidelineStateContext ()
{
}

void GuidelineStateContext::requestStateTransition (GuidelineState guidelineState)
{
  m_nextState = guidelineState;
}

void GuidelineStateContext::transitionIfRequested ()
{
  if (m_currentState != m_nextState) {
    
    // End the current state if there is one
    if (m_currentState != NUM_GUIDELINE_STATES) {
      m_states[m_currentState]->end ();
    }
    
    m_currentState = m_nextState;

    // Start the requested state
    m_states[m_currentState]->begin();
  }
}
