/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontal.h"
#include "GuidelineStateDeployedVertical.h"
#include "GuidelineStateHandle.h"
#include "GuidelineStateNull.h"
#include "GuidelineStateTemplateHorizontalBottom.h"
#include "GuidelineStateTemplateHorizontalTop.h"
#include "GuidelineStateTemplateVerticalLeft.h"
#include "GuidelineStateTemplateVerticalRight.h"

GuidelineStateContext::GuidelineStateContext (Guideline &guideline,
                                              GuidelineState guidelineStateInitial) :
  m_guideline (guideline)
{
  m_states.insert (GUIDELINE_STATE_DEPLOYED_HORIZONTAL       , new GuidelineStateDeployedHorizontal       (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_VERTICAL         , new GuidelineStateDeployedVertical         (*this));
  m_states.insert (GUIDELINE_STATE_HANDLE                    , new GuidelineStateHandle                   (*this));  
  m_states.insert (GUIDELINE_STATE_NULL                      , new GuidelineStateNull                     (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM, new GuidelineStateTemplateHorizontalBottom (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP   , new GuidelineStateTemplateHorizontalTop    (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT    , new GuidelineStateTemplateVerticalLeft     (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT   , new GuidelineStateTemplateVerticalRight    (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_GUIDELINE_STATES);

  m_currentState = NUM_GUIDELINE_STATES; // Value that forces a transition right away
  m_nextState = guidelineStateInitial;

  transitionIfRequested ();
}

GuidelineStateContext::~GuidelineStateContext ()
{
}

bool GuidelineStateContext::alwaysVisible () const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->alwaysVisible ();
}

QColor GuidelineStateContext::colorForStateAndHover (bool hover) const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->colorForStateAndHover (hover);
}

Guideline &GuidelineStateContext::guideline ()
{
  return m_guideline;
}

void GuidelineStateContext::handleMousePress ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleMousePress ();
  transitionIfRequested ();  
}

void GuidelineStateContext::handleMouseRelease ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleMouseRelease ();
  transitionIfRequested ();
}

bool GuidelineStateContext::initialHoverEventsEnable () const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->initialHoverEventsEnable();
}

void GuidelineStateContext::requestStateTransition (GuidelineState guidelineState)
{
  ENGAUGE_ASSERT (guidelineState != NUM_GUIDELINE_STATES);

  m_nextState = guidelineState;
}

void GuidelineStateContext::setStateReplacement (GuidelineState stateReplacement)
{
  m_stateReplacement = stateReplacement;
}

GuidelineState GuidelineStateContext::stateReplacement () const
{
  return m_stateReplacement;
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
