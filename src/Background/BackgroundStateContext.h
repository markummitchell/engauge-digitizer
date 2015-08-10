#ifndef BACKGROUND_STATE_CONTEXT_H
#define BACKGROUND_STATE_CONTEXT_H

#include "BackgroundImage.h"
#include "BackgroundStateAbstractBase.h"
#include <QVector>

class DocumentModelColorFilter;
class MainWindow;
class QGraphicsPixmapItem;

/// Context class that manages the background image state machine.
/// Overall strategy is that changing the currently selected curve should not affect the background
/// image if the original image is being shown, or no image is being shown. However, if the
/// curve-specific color filter image is being shown, then it should be replaced by the filtered
/// image specific to the new curve
class BackgroundStateContext
{
 public:
  /// Single constructor
  BackgroundStateContext(MainWindow &mainWindow);

  /// Image for the current state
  QGraphicsPixmapItem &image ();

  /// Initiate state transition to be performed later, when BackgroundState is off the stack
  void requestStateTransition (BackgroundState backgroundState);

  /// Transition to the specified state. This method is used by classes outside of the state machine to trigger transitions
  void selectBackgroundImage (BackgroundImage backgroundImage);

  ///  Update the images of all states, rather than just the current state
  void setPixmapForAllStates (const QPixmap &pixmap);

  /// Apply color filter settings
  void updateColorFilter (const DocumentModelColorFilter &colorFilter);

 private:
  BackgroundStateContext();

  void completeRequestedStateTransitionIfExists ();

  const MainWindow &m_mainWindow;

  QVector<BackgroundStateAbstractBase*> m_states;
  BackgroundState m_currentState;
  BackgroundState m_requestedState; // Same as m_currentState until requestStateTransition is called
};

#endif // BACKGROUND_STATE_CONTEXT_H
