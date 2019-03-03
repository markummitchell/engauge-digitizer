/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

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
class DocumentModelGridRemoval;
class GraphicsScene;
class GraphicsView;
class Transformation;

/// Background image state machine state base class
class BackgroundStateAbstractBase
{
 public:
  /// Single constructor
  BackgroundStateAbstractBase(BackgroundStateContext &context,
                              GraphicsScene &scene);
  virtual ~BackgroundStateAbstractBase();

  /// Method that is called at the exact moment a state is entered. Typically called just after end for the previous state.
  virtual void begin() = 0;

  /// Reference to the BackgroundStateContext that contains all the BackgroundStateAbstractBase subclasses, without const.
  BackgroundStateContext &context();

  /// Reference to the BackgroundStateContext that contains all the BackgroundStateAbstractBase subclasses, without const.
  const BackgroundStateContext &context() const;

  /// Method that is called at the exact moment a state is exited. Typically called just before begin for the next state
  virtual void end() = 0;

  /// Zoom so background fills the window
  virtual void fitInView (GraphicsView &view) = 0;

  /// Image for the current state
  QImage image () const;

  /// Graphics image item for the current state
  QGraphicsPixmapItem &imageItem () const;

  /// Reference to the GraphicsScene, without const.
  GraphicsScene &scene();

  /// Reference to the GraphicsScene, without const.
  const GraphicsScene &scene() const;

  /// Update the currently selected curve name
  virtual void setCurveSelected (bool isGnuplot,
                                 const Transformation &transformation,
                                 const DocumentModelGridRemoval &modelGridRemoval,
                                 const DocumentModelColorFilter &colorFilter,
                                 const QString &curveSelected) = 0;

  /// Update the image for this state, after the leaf class processes it appropriately
  virtual void setPixmap (bool isGnuplot,
                          const Transformation &transformation,
                          const DocumentModelGridRemoval &modelGridRemoval,
                          const DocumentModelColorFilter &modelColorFilter,
                          const QPixmap &pixmap,
                          const QString &curveSelected) = 0;

  /// State name for debugging
  virtual QString state() const = 0;

  /// Apply color filter settings
  virtual void updateColorFilter (bool isGnuplot,
                                  const Transformation &transformation,
                                  const DocumentModelGridRemoval &modelGridRemoval,
                                  const DocumentModelColorFilter &modelColorFilter,
                                  const QString &curveSelected) = 0;

 protected:

  /// Show/hide background image
  void setImageVisible (bool visible);

  /// Save the image for this state after it has been processed by the leaf class
  void setProcessedPixmap (const QPixmap &pixmap);

 private:
  BackgroundStateAbstractBase();

  BackgroundStateContext &m_context;
  GraphicsScene &m_scene;

  // Each state has its own image, although only one is shown at a time. This is null if an image has not been defined yet,
  // so we can eliminate a dependency on the ordering of the state transitions and the update of the image by setPixmap
  QGraphicsPixmapItem *m_imageItem;

  QImage m_image; // Original image. This is stored in addition to m_imageItem since m_imageItem cannot be used when invisible
};

#endif // BACKGROUND_STATE_ABSTRACT_BASE_H
