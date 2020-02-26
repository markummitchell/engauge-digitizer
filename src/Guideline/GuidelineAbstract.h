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
/// When a deployed Guideline is dragged, the following process occurs
///  1) The dragged Guideline becomes invisible, and its state changes to Handle
///  2) A new deployed Guideline is generated where the dragged Guideline was located
///  3) Dragging the Handle causes the same movements in the new deployed Guideline
///  4) The new deployed Guideline is continually resized to just fit the scene, and in the
///     case of polar coordinates resized to go between origin and scene edge (theta) or
///     curved elliptically (range)
///  5) At the end of the drag, the Handle and Visible Guidelines are sacrificed (=discarded)
///     and a new Deployed Guideline is created. Since the new Deployed Guideline is off the
///     stack, the new CmdGuidelineMove can work on it safely
/// State transitions are diagrammed in the GuidelineStateContext class
///
/// This strategy works with the following constraints
/// 1) Since it is not the dragged object that we modify in 3d above, we can resize and adjust
///    the curvature of the visible new deployed Guideline as necessary
/// 2) When a Guideline is clicked on, that is the one that is active during the cursor drag.
///    It is not possible to move the focus to another QGraphicsItem
/// 3) At the end of the drag, a new CmdGuidelineMove is created and its redo method is run
///    before the Handle Guideline is off the stack. This would corrupt the movement if that
///    CmdGuidelineMove tried to move the (on the stack) Handle, so we do not transition the
///    Handle state back to the Deployed state. Instead, a third Guideline is created as the
///    target of the new CmdGuidelineMove. The Handle and Visible Guidelines are sacrificed
///    (=moved to Discard state or deleted).j
///
/// State names are defined as:
/// # horizontal = Follows constant-y isocontour
/// # vertical = Follows constant-x isocontour
/// # deployed = One of the guidelines created by button press or dragging an existing Guideline
/// # hide = Used when all Guidelines have been turned off
/// # hover = Applies when cursor is hovering over the Guideline, to add some highlighting
/// # normal = After a deployed Guideline has been created and lost the hover
/// # discarded = A noop state. The Guideline is no longer useful and has been removed
/// # handle = This Guideline is invisible, being dragged, and moving a bound deployed
///            Guideline along the same drag trajectory
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
  void bindGuidelineVisibleToInvisible (GuidelineAbstract *guidelineVisible);

  /// Return true if accepting hover events
  virtual bool getGraphicsItemAcceptHover () const = 0;

  /// Wrapper for QGraphicsItem::isSelected
  virtual bool getGraphicsItemSelected () const = 0;

  /// Wraps QGraphicsItem::flags
  virtual QGraphicsItem::GraphicsItemFlags graphicsItemFlags () const = 0;

  /// DigitizeState change so active status may (or may not) be toggled
  void handleActiveChange (bool active);

  /// User toggled Guideline visibility and/or locked mode
  void handleGuidelineMode (bool visible,
                            bool locked);

  /// Highlight this Guideline upon hover enter
  void handleHoverEnterEvent();

  /// Unset highlighting triggered by hover enter
  void handleHoverLeaveEvent();

  /// Forward movements to visible Guideline
  void handleMouseMoveEvent (const QPointF &posScene);

  /// Forward press event to state machine
  void handleMousePressEvent(const QPointF &posScene);

  /// Cleanup after being dragged
  void handleMouseReleaseEvent (const QPointF &posScene);

  /// Unique identifier from QGraphicsItem
  virtual QString identifier () const = 0;

  /// Get position in graph coordinates
  QPointF posCursorGraph () const;

  /// Make graphics item remove itself from the scene
  virtual void removeFromScene (QGraphicsScene *scene) = 0;
  
  /// Replace visible and handle Guidelines after click and drag
  void sacrificeHandleAndVisibleGuidelines (const QPointF &posScene,
                                            GuidelineState guidelineStateForReplacement);
  
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

  /// Dump of state as a string for debugging only. Context like the QGraphicsItem flags is included
  QString stateDump () const;

  /// Current state name for debugging and unit test only
  QString stateName () const;

  /// Update active versus inactive state. Inactive state applies when DigitizeState is not DigitizeStateSelect, since
  /// the Guidelines can help with moving points around. This method is called on DigitizeState transitions.
  /// Active is not the same as visibility. When inactive, guidelines ignore hover and click events
  void updateActive (bool active);

  /// Force a color update
  virtual void updateColor () = 0;

  /// Update the geometry so it passes through the specified coordinate value in graph coordinates
  virtual void updateGeometry (double valueGraph) = 0;

  /// Update the geometry so it passes through the specified point in screen coordinates
  virtual void updateGeometry (const QPointF &posScreen) = 0;

  /// Update given Transformation in GuidelineStateContext. This is called after a command has been executed
  void updateWithLatestTransformation ();

signals:

  /// Signal indicating end of Guideline drag
  void signalGuidelineDragged (QString,
                               double,
                               bool,
                               GuidelineState);

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
