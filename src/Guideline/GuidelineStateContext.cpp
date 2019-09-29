/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "Guidelines.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRActive.h"
#include "GuidelineStateDeployedConstantRHide.h"
#include "GuidelineStateDeployedConstantRHover.h"
#include "GuidelineStateDeployedConstantRLocked.h"
#include "GuidelineStateDeployedConstantTActive.h"
#include "GuidelineStateDeployedConstantTHide.h"
#include "GuidelineStateDeployedConstantTHover.h"
#include "GuidelineStateDeployedConstantTLocked.h"
#include "GuidelineStateDeployedConstantXActive.h"
#include "GuidelineStateDeployedConstantXHide.h"
#include "GuidelineStateDeployedConstantXHover.h"
#include "GuidelineStateDeployedConstantXLocked.h"
#include "GuidelineStateDeployedConstantYActive.h"
#include "GuidelineStateDeployedConstantYHide.h"
#include "GuidelineStateDeployedConstantYHover.h"
#include "GuidelineStateDeployedConstantYLocked.h"
#include "GuidelineStateDiscarded.h"
#include "GuidelineStateHandle.h"
#include "GuidelineStateTemplateHorizontalBottomHide.h"
#include "GuidelineStateTemplateHorizontalBottomHover.h"
#include "GuidelineStateTemplateHorizontalBottomLurking.h"
#include "GuidelineStateTemplateHorizontalTopHide.h"
#include "GuidelineStateTemplateHorizontalTopHover.h"
#include "GuidelineStateTemplateHorizontalTopLurking.h"
#include "GuidelineStateTemplateVerticalLeftHide.h"
#include "GuidelineStateTemplateVerticalLeftHover.h"
#include "GuidelineStateTemplateVerticalLeftLurking.h"
#include "GuidelineStateTemplateVerticalRightHide.h"
#include "GuidelineStateTemplateVerticalRightHover.h"
#include "GuidelineStateTemplateVerticalRightLurking.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateContext::GuidelineStateContext (GuidelineAbstract &guideline,
                                              Guidelines &guidelines,
                                              GuidelineState guidelineStateInitial) :
  m_guideline (guideline),
  m_guidelines (guidelines)
{
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_ACTIVE        , new GuidelineStateDeployedConstantRActive        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HIDE          , new GuidelineStateDeployedConstantRHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_HOVER         , new GuidelineStateDeployedConstantRHover         (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_LOCKED        , new GuidelineStateDeployedConstantRLocked        (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_ACTIVE        , new GuidelineStateDeployedConstantTActive        (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HIDE          , new GuidelineStateDeployedConstantTHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_HOVER         , new GuidelineStateDeployedConstantTHover         (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_LOCKED        , new GuidelineStateDeployedConstantTLocked        (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_ACTIVE        , new GuidelineStateDeployedConstantXActive        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HIDE          , new GuidelineStateDeployedConstantXHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_HOVER         , new GuidelineStateDeployedConstantXHover         (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_LOCKED        , new GuidelineStateDeployedConstantXLocked        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_ACTIVE        , new GuidelineStateDeployedConstantYActive        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HIDE          , new GuidelineStateDeployedConstantYHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_HOVER         , new GuidelineStateDeployedConstantYHover         (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_LOCKED        , new GuidelineStateDeployedConstantYLocked        (*this));   
  m_states.insert (GUIDELINE_STATE_DISCARDED                         , new GuidelineStateDiscarded                      (*this));
  m_states.insert (GUIDELINE_STATE_HANDLE                            , new GuidelineStateHandle                         (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HIDE   , new GuidelineStateTemplateHorizontalBottomHide   (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_HOVER  , new GuidelineStateTemplateHorizontalBottomHover  (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_BOTTOM_LURKING, new GuidelineStateTemplateHorizontalBottomLurking(*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HIDE      , new GuidelineStateTemplateHorizontalTopHide      (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_HOVER     , new GuidelineStateTemplateHorizontalTopHover     (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_HORIZONTAL_TOP_LURKING   , new GuidelineStateTemplateHorizontalTopLurking   (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HIDE       , new GuidelineStateTemplateVerticalLeftHide       (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_HOVER      , new GuidelineStateTemplateVerticalLeftHover      (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_LEFT_LURKING    , new GuidelineStateTemplateVerticalLeftLurking    (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HIDE      , new GuidelineStateTemplateVerticalRightHide      (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_HOVER     , new GuidelineStateTemplateVerticalRightHover     (*this));
  m_states.insert (GUIDELINE_STATE_TEMPLATE_VERTICAL_RIGHT_LURKING   , new GuidelineStateTemplateVerticalRightLurking   (*this));
  ENGAUGE_ASSERT (m_states.size () == NUM_GUIDELINE_STATES);

  m_currentState = NUM_GUIDELINE_STATES; // Value that forces a transition right away
  m_nextState = guidelineStateInitial;

  transitionIfRequested ();
}

GuidelineStateContext::~GuidelineStateContext ()
{
}

bool GuidelineStateContext::cartesian() const
{
  return m_guidelines.coordsType () == COORDS_TYPE_CARTESIAN;
}

ColorPalette GuidelineStateContext::color () const
{
  return m_guidelines.color ();
}

GuidelineAbstract *GuidelineStateContext::createGuideline (GuidelineState stateInitial) const
{
  return m_guidelines.createGuideline (stateInitial);
}

bool GuidelineStateContext::doPaint () const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->doPaint ();
}

void GuidelineStateContext::draggedOffScreen ()
{
  requestStateTransition (GUIDELINE_STATE_DISCARDED);
  transitionIfRequested ();
}

GuidelineAbstract &GuidelineStateContext::guideline ()
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

void GuidelineStateContext::handleMouseRelease (const QPointF &posScene)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleMouseRelease (posScene);
  transitionIfRequested ();
}

void GuidelineStateContext::handleShowHide (bool show)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleShowHide (show);
  transitionIfRequested ();
}

EllipseParameters GuidelineStateContext::pointToEllipse (const QPointF &posScreen) const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->pointToEllipse (posScreen);
}

QLineF GuidelineStateContext::pointToLine (const QPointF &posScreen) const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->pointToLine (posScreen);
}

QPointF GuidelineStateContext::posCursorGraph () const
{
  return m_posCursorGraph;
}

void GuidelineStateContext::requestStateTransition (GuidelineState guidelineState)
{
  ENGAUGE_ASSERT (guidelineState != NUM_GUIDELINE_STATES);

  m_nextState = guidelineState;
}

void GuidelineStateContext::setPosCursorGraph (const QPointF &posGraph)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_posCursorGraph = posGraph;
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

QString GuidelineStateContext::stateDump () const
{
  return m_guidelines.stateDump ();
}

GuidelineState GuidelineStateContext::stateReplacement () const
{
  return m_stateReplacement;
}

Transformation GuidelineStateContext::transformation() const
{
  return m_guidelines.transformation ();
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

void GuidelineStateContext::updateWithLatestTransformation()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->updateWithLatestTransformation();
}
