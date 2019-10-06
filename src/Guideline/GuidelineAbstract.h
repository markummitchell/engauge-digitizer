/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_ABSTRACT_H
#define GUIDELINE_ABSTRACT_H

#include "GuidelineStateContext.h"
#include <QColor>
#include <QGraphicsItem>
#include <QObject>

class QGraphicsScene;
class QMouseEvent;
class QPainter;
class QPointF;
class QStyleOptionGraphicsItem;
class QWidget;

/// This class is a special case of the standard QGraphicsLineItem for guidelines,
/// and serves as the base class for the guideline state classes. This class has
/// a state machine to handle state-specific behavior for hovering, dragging, and
/// formatting.
///
/// General strategy:
/// 1) Four template Guidelines lie around the four scene borders
/// 2) A deployed Guideline is created by dragging a template Guideline from its original position
/// 3) When a (template or deployed) Guideline is dragged, the following process occurs
///    3a) The dragged Guideline becomes invisible, and its state changes to Handle
///    3b) A new deployed Guideline is generated where the dragged Guideline was located
///    3c) Dragging the Handle causes the same movements in the new deployed Guideline
///    3d) The new deployed Guideline is continually resized to just fit the scene, and in the
///        case of polar coordinates resized to go between origin and scene edge (theta) or
///        curved elliptically (range)
///    3e) At the end of the drag, the Handle is no longer needed so it transitions to Discarded state
///    3f) At the end of the drag, if it started with a template Guideline then a replacement
///        is put back on the scene edge
///
/// This strategy works with the following constraints
/// 1) Since it is not the dragged object that we modify in 3d above, we can resize and adjust
///    the curvature of the visible new deployed Guideline as necessary
///
/// A simple way to describe this approach: Clicking and dragging involves the clicked Guideline
/// dying and a new Guideline being born in its place
///
/// State names are defined as:
/// # horizontal = Follows constant-y isocontour
/// # vertical = Follows constant-x isocontour
/// # template = One of the guidelines along every scene border that can be dragged
/// # deployed = One of the guidelines created by the user dragging a template guideline
/// # hide = Used when all Guidelines have been turned off
/// # hover = Applies when cursor is hovering over the Guideline, to add some highlighting
/// # normal = After a deployed Guideline has been created and lost the hover
/// # discarded = A noop state. The Guideline is no longer useful and has been removed
/// # handle = This Guideline is invisible, being dragged, and moving a bound deployed
///            Guideline along the same drag trajectory
/// # lurking = Template Guideline state for when active but not seen, and waiting for hover
///
/// There are two derived classes:
/// # one for drawing lines (cartesian and polar angle) with QGraphicsLineItem
/// # one for drawing ellipses (range angle) with QGraphicsEllipseItem
/// An attempt to draw lines with just QGraphicsEllipseItem, for simplicity, failed with
/// the result having sinusoidally changing line width.
class GuidelineAbstract : public QObject
{
  Q_OBJECT;

public:
  /// Single constructor.
  GuidelineAbstract(QGraphicsScene &scene);
  ~GuidelineAbstract();

  /// Bind a newly-created visible Guideline to this Guideline, and make this one invisible
  void bindGuidelineVisible (GuidelineAbstract *guidelineVisible);
  
  /// Detach visible Guideline after click and drag
  void detachVisibleGuideline (const QPointF &posScene);

  /// Guideline has been dragged off screen so remove it
  void draggedOffScreen ();

  /// Return true if accepting hover events
  virtual bool getGraphicsItemAcceptHover () const = 0;

  /// Wrapper for QGraphicsItem::isSelected
  virtual bool getGraphicsItemSelected () const = 0;

  /// Wraps QGraphicsItem::flags
  virtual QGraphicsItem::GraphicsItemFlags graphicsItemFlags () const = 0;
  
  /// DigitizeState change so active status may (or may not) be toggled
  void handleActiveChange (bool active);

  /// Highlight this Guideline upon hover enter
  void handleHoverEnterEvent();

  /// Unset highlighting triggered by hover enter
  void handleHoverLeaveEvent();

  /// Forwad movements to visible Guideline
  void handleMouseMoveEvent (const QPointF &posScene);

  /// Forward press event to state machine
  void handleMousePressEvent(const QPointF &posScene);

  /// Cleanup after being dragged
  void handleMouseReleaseEvent (const QPointF &posScene);

  /// User toggled Guideline visibility
  void handleVisibleChange (bool visible);

  /// Make graphics item remove itself from the scene
  virtual void removeFromScene (QGraphicsScene *scene) = 0;
  
  /// GraphicsScene that owns this class
  QGraphicsScene &scene ();

  /// Wrapper for QGraphicsItem::setAcceptHoverEvents
  virtual void setGraphicsItemAcceptHoverEvents (bool accept) = 0;
  
  /// Wrapper for QGraphicsItem::setFlags
  virtual void setGraphicsItemFlags (QGraphicsItem::GraphicsItemFlags flags) = 0;

  /// Wrapper for QGraphicsLineItem::setLine
  virtual void setGraphicsItemLine (const QLineF &line) = 0;
  
  /// Wrapper for QGraphicsItem::setPen
  virtual void setGraphicsItemPen (const QColor &color,
                                   double lineWidth) = 0;

  /// Wrapper for QGraphicsItem::setVisible
  virtual void setGraphicsItemVisible (bool visible) = 0;
  
  /// Wrapper for QGraphicsItem::setZValue
  virtual void setGraphicsItemZValue (double z) = 0;

  /// State as a string for debugging only
  QString state () const;

  /// Update active versus inactive state. Inactive state applies when DigitizeState is not DigitizeStateSelect, since
  /// the Guidelines can help with moving points around. This method is called on DigitizeState transitions.
  /// Active is not the same as visibility. When inactive, guidelines ignore hover and click events
  void updateActive (bool active);

  /// Force a color update
  virtual void updateColor () = 0;

  /// Update the geometry so it passes through the specified point
  virtual void updateGeometry (const QPointF &pos) = 0;

  /// Update given Transformation in GuidelineStateContext. This is called after a command has been executed
  void updateWithLatestTransformation ();

signals:

  /// Signal for cloned deployed Guideline from handle Guideline
  void signalHandleMoved (QPointF);

public slots:

  /// Slot for signal from cloned deployed Guideline from handle Guideline
  void slotHandleMoved (QPointF posScreen);

protected:
  /// State machine context owned by this class
  GuidelineStateContext *context();

  /// State machine context owned by this class as a const
  const GuidelineStateContext *context () const;

  /// Create state machine after virtual methods of child classes have been defined
  void setContext (GuidelineStateContext *context);

private:
  GuidelineAbstract();

  QGraphicsScene &m_scene;

  // Context is allocated as a final step in the constructor, at which point
  // this class has registered with the QGraphicsScene
  GuidelineStateContext *m_context;

  // After binding to visible Guideline
  GuidelineAbstract *m_guidelineVisible;

};

#endif // GUIDELINE_ABSTRACT_H
