#ifndef BACKGROUND_STATE_ABSTRACT_BASE_H
#define BACKGROUND_STATE_ABSTRACT_BASE_H

#include <QGraphicsPixmapItem>
#include <QImage>

/// Set of possible states of background image.
enum BackgroundState {
  BACKGROUND_STATE_CURVE,
  BACKGROUND_STATE_NONE,
  BACKGROUND_STATE_ORIGINAL,
  BACKGROUND_STATE_UNLOADED,
  NUM_BACKGROUND_STATES
};

class BackgroundStateContext;
class DocumentModelColorFilter;
class GraphicsScene;

/// Background image state machine state base class
class BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateAbstractBase(BackgroundStateContext &context,
                              GraphicsScene &scene);
  ~BackgroundStateAbstractBase();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state.
  virtual void begin() = 0;

  /// Reference to the BackgroundStateContext that contains all the BackgroundStateAbstractBase subclasses, without const.
  BackgroundStateContext &context();

  /// Reference to the BackgroundStateContext that contains all the BackgroundStateAbstractBase subclasses, without const.
  const BackgroundStateContext &context() const;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end() = 0;

  /// Image for the current state
  QGraphicsPixmapItem &image ();

  /// Reference to the GraphicsScene, without const.
  GraphicsScene &scene();

  /// Reference to the GraphicsScene, without const.
  const GraphicsScene &scene() const;

  ///  Update the image for this state
  virtual void setPixmap (const QPixmap &pixmap) = 0;

  /// Apply color filter settings
  virtual void updateColorFilter (const DocumentModelColorFilter &colorFilter) = 0;

private:
  BackgroundStateAbstractBase();

  BackgroundStateContext &m_context;
  GraphicsScene &m_scene;

  // Each state has its own image, although only one is shown at a time
  QGraphicsPixmapItem m_image;
};

#endif // BACKGROUND_STATE_ABSTRACT_BASE_H
