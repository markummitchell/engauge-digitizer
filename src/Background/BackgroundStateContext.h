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
/// Overall strategy is that changing the currently selected curve should not
/// affect the background
/// image if the original image is being shown, or no image is being shown.
/// However, if the
/// curve-specific color filter image is being shown, then it should be replaced
/// by the filtered
/// image specific to the new curve.
///
/// Other considerations are that the processing should be robust in terms of
/// ordering of the
/// following incoming events:
/// -# State transitions
/// -# Setting of the background image
/// -# Setting of the currently selected curve name
class BackgroundStateContext {
public:
  /// Single constructor
  BackgroundStateContext(MainWindow &mainWindow);

  /// Open Document is being closed so remove the background
  void close();

  /// Zoom so background fills the window
  void fitInView(GraphicsView &view);

  /// Image for the Curve state, even if the current state is different
  QImage imageForCurveState() const;

  /// Initiate state transition to be performed later, when BackgroundState is
  /// off the stack
  void requestStateTransition(BackgroundState backgroundState);

  /// Transition to the specified state. This method is used by classes outside
  /// of the state machine to trigger transitions
  void setBackgroundImage(BackgroundImage backgroundImage);

  /// Update the selected curve. Although this probably affects only the
  /// BACKGROUND_STATE_CURVE state, we will forward it
  /// to all states (consistent with setPixmap)
  void setCurveSelected(const Transformation &transformation,
                        const DocumentModelGridRemoval &modelGridRemoval,
                        const DocumentModelColorFilter &modelColorFilter,
                        const QString &curveSelected);

  /// Update the images of all states, rather than just the current state
  void setPixmap(const Transformation &transformation,
                 const DocumentModelGridRemoval &modelGridRemoval,
                 const DocumentModelColorFilter &modelColorFilter,
                 const QPixmap &pixmapOriginal);

  /// Apply color filter settings
  void updateColorFilter(const Transformation &transformation,
                         const DocumentModelGridRemoval &modelGridRemoval,
                         const DocumentModelColorFilter &colorFilter);

private:
  BackgroundStateContext();

  void completeRequestedStateTransitionIfExists();

  const MainWindow &m_mainWindow;

  QVector<BackgroundStateAbstractBase *> m_states;
  BackgroundState m_currentState;
  BackgroundState m_requestedState; // Same as m_currentState until
                                    // requestStateTransition is called
};

#endif // BACKGROUND_STATE_CONTEXT_H
