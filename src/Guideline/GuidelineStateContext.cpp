/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CmdMediator.h"
#include "EngaugeAssert.h"
#include "GuidelineAbstract.h"
#include "Guidelines.h"
#include "GuidelineStateAbstractBase.h"
#include "GuidelineStateContext.h"
#include "GuidelineStateDeployedConstantRSelectEdit.h"
#include "GuidelineStateDeployedConstantRSelectEditAppearing.h"
#include "GuidelineStateDeployedConstantRSelectEditHover.h"
#include "GuidelineStateDeployedConstantRSelectHide.h"
#include "GuidelineStateDeployedConstantRSelectLock.h"
#include "GuidelineStateDeployedConstantRUnselectEdit.h"
#include "GuidelineStateDeployedConstantRUnselectHide.h"
#include "GuidelineStateDeployedConstantRUnselectLock.h"
#include "GuidelineStateDeployedConstantTSelectEdit.h"
#include "GuidelineStateDeployedConstantTSelectEditAppearing.h"
#include "GuidelineStateDeployedConstantTSelectEditHover.h"
#include "GuidelineStateDeployedConstantTSelectHide.h"
#include "GuidelineStateDeployedConstantTSelectLock.h"
#include "GuidelineStateDeployedConstantTUnselectEdit.h"
#include "GuidelineStateDeployedConstantTUnselectHide.h"
#include "GuidelineStateDeployedConstantTUnselectLock.h"
#include "GuidelineStateDeployedConstantXSelectEdit.h"
#include "GuidelineStateDeployedConstantXSelectEditAppearing.h"
#include "GuidelineStateDeployedConstantXSelectEditHover.h"
#include "GuidelineStateDeployedConstantXSelectHide.h"
#include "GuidelineStateDeployedConstantXSelectLock.h"
#include "GuidelineStateDeployedConstantXUnselectEdit.h"
#include "GuidelineStateDeployedConstantXUnselectHide.h"
#include "GuidelineStateDeployedConstantXUnselectLock.h"
#include "GuidelineStateDeployedConstantYSelectEdit.h"
#include "GuidelineStateDeployedConstantYSelectEditAppearing.h"
#include "GuidelineStateDeployedConstantYSelectEditHover.h"
#include "GuidelineStateDeployedConstantYSelectHide.h"
#include "GuidelineStateDeployedConstantYSelectLock.h"
#include "GuidelineStateDeployedConstantYUnselectEdit.h"
#include "GuidelineStateDeployedConstantYUnselectHide.h"
#include "GuidelineStateDeployedConstantYUnselectLock.h"
#include "GuidelineStateDiscarded.h"
#include "GuidelineStateHandleR.h"
#include "GuidelineStateHandleT.h"
#include "GuidelineStateHandleX.h"
#include "GuidelineStateHandleY.h"
#include "MainWindow.h"
#include <QGraphicsScene>
#include "Transformation.h"

GuidelineStateContext::GuidelineStateContext (GuidelineAbstract &guideline,
                                              MainWindow &mainWindow,
                                              Guidelines &guidelines,
                                              GuidelineState guidelineStateInitial) :
  m_guideline (guideline),
  m_guidelines (guidelines),
  m_mainWindow (mainWindow)
{
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT          , new GuidelineStateDeployedConstantRSelectEdit          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT_APPEARING, new GuidelineStateDeployedConstantRSelectEditAppearing (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_EDIT_HOVER    , new GuidelineStateDeployedConstantRSelectEditHover     (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_HIDE          , new GuidelineStateDeployedConstantRSelectHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_SELECT_LOCK          , new GuidelineStateDeployedConstantRSelectLock          (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_EDIT        , new GuidelineStateDeployedConstantRUnselectEdit        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_HIDE        , new GuidelineStateDeployedConstantRUnselectHide        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_R_UNSELECT_LOCK        , new GuidelineStateDeployedConstantRUnselectLock        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT          , new GuidelineStateDeployedConstantTSelectEdit          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT_APPEARING, new GuidelineStateDeployedConstantTSelectEditAppearing (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_EDIT_HOVER    , new GuidelineStateDeployedConstantTSelectEditHover     (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_HIDE          , new GuidelineStateDeployedConstantTSelectHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_SELECT_LOCK          , new GuidelineStateDeployedConstantTSelectLock          (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_EDIT        , new GuidelineStateDeployedConstantTUnselectEdit        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_HIDE        , new GuidelineStateDeployedConstantTUnselectHide        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_T_UNSELECT_LOCK        , new GuidelineStateDeployedConstantTUnselectLock        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT          , new GuidelineStateDeployedConstantXSelectEdit          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_APPEARING, new GuidelineStateDeployedConstantXSelectEditAppearing (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_EDIT_HOVER    , new GuidelineStateDeployedConstantXSelectEditHover     (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_HIDE          , new GuidelineStateDeployedConstantXSelectHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_SELECT_LOCK          , new GuidelineStateDeployedConstantXSelectLock          (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_EDIT        , new GuidelineStateDeployedConstantXUnselectEdit        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_HIDE        , new GuidelineStateDeployedConstantXUnselectHide        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_X_UNSELECT_LOCK        , new GuidelineStateDeployedConstantXUnselectLock        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT          , new GuidelineStateDeployedConstantYSelectEdit          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_APPEARING, new GuidelineStateDeployedConstantYSelectEditAppearing (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_EDIT_HOVER    , new GuidelineStateDeployedConstantYSelectEditHover     (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_HIDE          , new GuidelineStateDeployedConstantYSelectHide          (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_SELECT_LOCK          , new GuidelineStateDeployedConstantYSelectLock          (*this));  
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_EDIT        , new GuidelineStateDeployedConstantYUnselectEdit        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_HIDE        , new GuidelineStateDeployedConstantYUnselectHide        (*this));
  m_states.insert (GUIDELINE_STATE_DEPLOYED_CONSTANT_Y_UNSELECT_LOCK        , new GuidelineStateDeployedConstantYUnselectLock        (*this));  
  m_states.insert (GUIDELINE_STATE_DISCARDED                                , new GuidelineStateDiscarded                       (*this));
  m_states.insert (GUIDELINE_STATE_HANDLE_R                                 , new GuidelineStateHandleR                         (*this));
  m_states.insert (GUIDELINE_STATE_HANDLE_T                                 , new GuidelineStateHandleT                         (*this));
  m_states.insert (GUIDELINE_STATE_HANDLE_X                                 , new GuidelineStateHandleX                         (*this));
  m_states.insert (GUIDELINE_STATE_HANDLE_Y                                 , new GuidelineStateHandleY                         (*this));
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

QPointF GuidelineStateContext::convertGraphCoordinateToScreenPoint (double valueGraph) const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->convertGraphCoordinateToScreenPoint (valueGraph);
}

double GuidelineStateContext::convertScreenPointToGraphCoordinate (const QPointF &posScreen) const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->convertScreenPointToGraphCoordinate (posScreen);
}

GuidelineAbstract *GuidelineStateContext::createGuideline (const QString &identifier,
                                                           GuidelineState stateInitial) const
{
  return m_guidelines.createGuideline (identifier,
                                       stateInitial);
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

void GuidelineStateContext::handleActiveChange (bool active)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleActiveChange (active);
  transitionIfRequested ();
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

void GuidelineStateContext::handleGuidelineMode (bool visible,
                                                 bool locked)
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleGuidelineMode (visible,
                                                 locked);
  transitionIfRequested ();
}

DocumentModelGuideline GuidelineStateContext::modelGuideline () const
{
  return m_mainWindow.cmdMediator ()->document ().modelGuideline ();
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

void GuidelineStateContext::slotTimeout ()
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  m_states[m_currentState]->handleTimeout ();
  transitionIfRequested ();
}

QString GuidelineStateContext::stateDump () const
{
  return m_guidelines.stateDump ();
}

QString GuidelineStateContext::stateName () const
{
  ENGAUGE_ASSERT (m_currentState != NUM_GUIDELINE_STATES);

  return m_states[m_currentState]->stateName();
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
  transitionIfRequested ();
}
