#include "CmdMediator.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QGraphicsScene>
#include <QImage>
#include "TransformationStateAbstractBase.h"
#include "TransformationStateContext.h"
#include "TransformationStateDefined.h"
#include "TransformationStateUndefined.h"

TransformationStateContext::TransformationStateContext(QGraphicsScene &scene,
                                                       bool isGnuplot) :
  m_isGnuplot (isGnuplot)
{
  m_states.insert (TRANSFORMATION_STATE_DEFINED  , new TransformationStateDefined   (*this, scene));
  m_states.insert (TRANSFORMATION_STATE_UNDEFINED, new TransformationStateUndefined (*this, scene));
  ENGAUGE_ASSERT (m_states.size () == NUM_TRANSFORMATION_STATES);

  m_currentState = NUM_TRANSFORMATION_STATES; // Value that forces a transition right away
}

TransformationStateContext::~TransformationStateContext()
{
}

bool TransformationStateContext::isGnuplot() const
{
  return m_isGnuplot;
}

void TransformationStateContext::resetOnLoad ()
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateContext::resetOnLoad";

  m_currentState = NUM_TRANSFORMATION_STATES;
}

void TransformationStateContext::triggerStateTransition (TransformationState transformationState,
                                                         CmdMediator &cmdMediator,
                                                         const Transformation &transformation,
                                                         const QString &selectedGraphCurve)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateContext::triggerStateTransition";

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
                                    transformation,
                                    selectedGraphCurve);
  }
}

void TransformationStateContext::updateAxesChecker (CmdMediator &cmdMediator,
                                                    const Transformation &transformation)
{
  LOG4CPP_INFO_S ((*mainCat)) << "TransformationStateContext::updateAxesChecker";

  // Skip if there is no image so the state has not yet been set yet
  if (m_currentState < NUM_TRANSFORMATION_STATES) {

    m_states[m_currentState]->updateAxesChecker (cmdMediator,
                                                 transformation);

  }
}
