/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Guideline.h"
#include "Guidelines.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedHorizontalHide.h"
#include "GuidelineStateDeployedHorizontalShow.h"
#include "GuidelineStateDeployedVerticalHide.h"
#include "GuidelineStateDeployedVerticalShow.h"
#include "GuidelineStateHandle.h"
#include "GuidelineStateNull.h"
#include "GuidelineStateTemplateHorizontalBottomHide.h"
#include "GuidelineStateTemplateHorizontalBottomShow.h"
#include "GuidelineStateTemplateHorizontalTopHide.h"
#include "GuidelineStateTemplateHorizontalTopShow.h"
#include "GuidelineStateTemplateVerticalLeftHide.h"
#include "GuidelineStateTemplateVerticalLeftShow.h"
#include "GuidelineStateTemplateVerticalRightHide.h"
#include "GuidelineStateTemplateVerticalRightShow.h"
#include <QGraphicsScene>

GuidelineStateContext::GuidelineStateContext (Guideline &guideline,
                                              Guidelines &guidelines,
                                              GuidelineState guidelineStateInitial) :
  m_guideline (guideline),
  m_guidelines (guidelines)
{
  m_states.insert (GUIDELINE_STATE_DEPLOYED_HORIZONTAL_HIDE       , new GuidelineStateDeployedHorizontalHide       (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_HORIZONTAL_SHOW       , new GuidelineStateDeployedHorizontalShow       (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_VERTICAL_HIDE         , new GuidelineStateDeployedVerticalHide         (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_VERTICAL_SHOW         , new GuidelineStateDeployedVerticalShow         (*this));  
  m_states.insert (GUIDELINE_STATE_HANDLE                         , new GuidelineStateHandle                       (*this));  
  m_states.insert (GUIDELINE_STATE_NULL                           , new GuidelineStateNull                         (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE, new GuidelineStateTemplateHorizontalBottomHide (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_SHOW, new GuidelineStateTemplateHorizontalBottomShow (*this));  
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE   , new GuidelineStateTemplateHorizontalTopHide    (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_SHOW   , new GuidelineStateTemplateHorizontalTopShow    (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE    , new GuidelineStateTemplateVerticalLeftHide    (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_SHOW    , new GuidelineStateTemplateVerticalLeftShow     (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE   , new GuidelineStateTemplateVerticalRightHide    (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_SHOW   , new GuidelineStateTemplateVerticalRightShow    (*this));  
  ENGAUGE_ASSERT (m_states.size () == NUM_GUIDELINE_STATES);

  m_currentState = NUM_GUIDELINE_STATES; // Value that forces a transition right away
  m_nextState = guidelineStateInitial;

  transitionIfRequested ();
}

GuidelineStateContext::~GuidelineStateContext ()
{
}

Guideline *GuidelineStateContext::createGuideline (GuidelineState stateInitial) const
{
  return m_guidelines.createGuideline (stateInitial);
}

bool GuidelineStateContext::doPaint () const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->doPaint ();
}

Guideline &GuidelineStateContext::guideline ()
{
  return m_guideline;
}

void GuidelineStateContext::handleHoverEnterEvent ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleHoverEnterEvent ();
  transitionIfRequested ();
}

void GuidelineStateContext::handleHoverLeaveEvent ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleHoverLeaveEvent ();
  transitionIfRequested ();
}

void GuidelineStateContext::handleMousePress (const QPointF &posScene)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleMousePress (posScene);
  transitionIfRequested ();  
}

void GuidelineStateContext::handleMouseRelease ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleMouseRelease ();
  transitionIfRequested ();
}

void GuidelineStateContext::handleShowHide (bool show)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleShowHide (show);
  transitionIfRequested ();
}

QLineF GuidelineStateContext::lineFromPoint (const QPointF &point) const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->lineFromPoint (point);
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

QString GuidelineStateContext::state () const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->state();
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
