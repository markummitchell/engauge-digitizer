#include "BackgroundStateContext.h"
#include "BackgroundStateCurve.h"
#include "BackgroundStateNone.h"
#include "BackgroundStateOriginal.h"
#include "BackgroundStateUnloaded.h"
#include "DocumentModelColorFilter.h"
#include "EngaugeAssert.h"
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

QGraphicsPixmapItem &BackgroundStateContext::image ()
{
  return m_states [m_currentState]->image();
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

void BackgroundStateContext::setPixmapForAllStates (const QPixmap &pixmap)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::setPixmapForAllStates";

  for (int backgroundState = 0; backgroundState < NUM_BACKGROUND_STATES; backgroundState++) {

    m_states [backgroundState]->setPixmap (pixmap);
  }
}

void BackgroundStateContext::updateColorFilter (const DocumentModelColorFilter &colorFilter)
{
  LOG4CPP_INFO_S ((*mainCat)) << "BackgroundStateContext::updateColorFilter";

  m_states [m_currentState]->updateColorFilter (colorFilter);
}
