#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "BackgroundStateNone.h"
#include "BackgroundStateOriginal.h"
#include "BackgroundStateUnloaded.h"
#include "DocumentModelColorFilter.h"
#include "EngaugeAssert.h"
#include "GraphicsView.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGraphicsPixmapItem>

BackgroundStateContext::BackgroundStateContext(MainWindow &mainWindow) :
  m_mainWindow (mainWindow)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::BackgroundStateContext";

  // These states follow the same order as the BackgroundState enumeration
  m_states.insert (BACKGROUND_STATE_CURVE   , new BackgroundStateCurve    (*this, mainWindow.scene()));
  m_states.insert (BACKGROUND_STATE_NONE    , new BackgroundStateNone     (*this, mainWindow.scene()));
  m_states.insert (BACKGROUND_STATE_ORIGINAL, new BackgroundStateOriginal (*this, mainWindow.scene()));
  m_states.insert (BACKGROUND_STATE_UNLOADED, new BackgroundStateUnloaded (*this, mainWindow.scene()));
  ENGAUGE_ASSERT (m_states.size () == NUM_BACKGROUND_STATES);

  m_currentState = NUM_BACKGROUND_STATES; // Value that forces a transition right away
  requestStateTransition (BACKGROUND_STATE_UNLOADED);
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

void BackgroundStateContext::fitInView (GraphicsView &view)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::fitInView";

  if (m_currentState != NUM_BACKGROUND_STATES) {

    view.fitInView (&m_states [m_currentState]->imageItem ());

  }
}

QImage BackgroundStateContext::imageForCurveState () const
{
  return m_states [BACKGROUND_STATE_CURVE]->image();
}

void BackgroundStateContext::requestStateTransition (BackgroundState backgroundState)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::requestStateTransition";

  m_requestedState = backgroundState;
}

void BackgroundStateContext::selectBackgroundImage (BackgroundImage backgroundImage)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::selectBackgroundImage"
                              << " background=" << backgroundImageToString (backgroundImage).toLatin1().data();

  BackgroundState backgroundState;
  switch (backgroundImage) {
    case BACKGROUND_IMAGE_FILTERED:
      backgroundState = BACKGROUND_STATE_CURVE;
      break;

    case BACKGROUND_IMAGE_NONE:
      backgroundState = BACKGROUND_STATE_NONE;
      break;

     case BACKGROUND_IMAGE_ORIGINAL:
      backgroundState = BACKGROUND_STATE_ORIGINAL;
      break;

    default:
      LOG4CPP_ERROR_S ((*mainCat)) << "BackgroundStateContext::selectBackgroundImage";
      exit (-1);
  }

  // It is safe to transition to the new state immediately since no BackgroundState classes are on the stack
  requestStateTransition (backgroundState);
  completeRequestedStateTransitionIfExists ();
}

void BackgroundStateContext::setColorFilter (const DocumentModelColorFilter &modelColorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::setColorFilter";

  for (int backgroundState = 0; backgroundState < NUM_BACKGROUND_STATES; backgroundState++) {

    m_states [backgroundState]->setColorFilter (modelColorFilter);
  }
}

void BackgroundStateContext::setCurveSelected (const QString &curveSelected)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::setCurveSelected"
                              << " curve=" << curveSelected.toLatin1().data();

  for (int backgroundState = 0; backgroundState < NUM_BACKGROUND_STATES; backgroundState++) {

    m_states [backgroundState]->setCurveSelected (curveSelected);
  }
}

void BackgroundStateContext::setPixmap (const QPixmap &pixmapOriginal)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::setPixmap";

  for (int backgroundState = 0; backgroundState < NUM_BACKGROUND_STATES; backgroundState++) {

    m_states [backgroundState]->setPixmap (pixmapOriginal);
  }
}
