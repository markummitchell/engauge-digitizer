/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef BACKGROUND_STATE_CONTEXT_H
#define BACKGROUND_STATE_CONTEXT_H

#include "BackgroundImage.h"
#include "BackgroundStateAbstractBase.h"
#include <QVector>

class DocumentModelColorFilter;
class DocumentModelGridRemoval;
class GraphicsView;
class MainWindow;
class QGraphicsPixmapItem;
class Transformation;

/// Context class that manages the background image state machine.
/// Overall strategy is that changing the currently selected curve should not affect the background
/// image if the original image is being shown, or no image is being shown. However, if the
/// curve-specific color filter image is being shown, then it should be replaced by the filtered
/// image specific to the new curve.
///
/// Other considerations are that the processing should be robust in terms of ordering of the
/// following incoming events:
/// -# State transitions
/// -# Setting of the background image
/// -# Setting of the currently selected curve name
class BackgroundStateContext
{
 public:
  /// Single constructor
  BackgroundStateContext(MainWindow &mainWindow);

  /// Destructor deallocates memory
  ~BackgroundStateContext();
  
  /// Open Document is being closed so remove the background
  void close();

  /// Zoom so background fills the window
  void fitInView (GraphicsView &view);

  /// Image for the Curve state, even if the current state is different
  QImage imageForCurveState () const;

  /// Initiate state transition to be performed later, when BackgroundState is off the stack
  void requestStateTransition (BackgroundState backgroundState);

  /// Transition to the specified state. This method is used by classes outside of the state machine to trigger transitions
  void setBackgroundImage (BackgroundImage backgroundImage);

  /// Update the selected curve. Although this probably affects only the BACKGROUND_STATE_CURVE state, we will forward it
  /// to all states (consistent with setPixmap)
  void setCurveSelected (bool isGnuplot,
                         const Transformation &transformation,
                         const DocumentModelGridRemoval &modelGridRemoval,
                         const DocumentModelColorFilter &modelColorFilter,
                         const QString &curveSelected);

  /// Update the images of all states, rather than just the current state
  void setPixmap (bool isGnuplot,
                  const Transformation &transformation,
                  const DocumentModelGridRemoval &modelGridRemoval,
                  const DocumentModelColorFilter &modelColorFilter,
                  const QPixmap &pixmapOriginal,
                  const QString &curveSelected);

  /// Apply color filter settings
  void updateColorFilter (bool isGnuplot,
                          const Transformation &transformation,
                          const DocumentModelGridRemoval &modelGridRemoval,
                          const DocumentModelColorFilter &colorFilter,
                          const QString &curveSelected);

 private:
  BackgroundStateContext();

  void completeRequestedStateTransitionIfExists ();

  const MainWindow &m_mainWindow;

  QVector<BackgroundStateAbstractBase*> m_states;
  BackgroundState m_currentState;
  BackgroundState m_requestedState; // Same as m_currentState until requestStateTransition is called
};

#endif // BACKGROUND_STATE_CONTEXT_H
