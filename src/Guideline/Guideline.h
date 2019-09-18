/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_H
#define GUIDELINE_H

#include "GuidelineStateContext.h"
#include <QColor>
#include <QGraphicsLineItem>

class QMouseEvent;
class QPainter;
class QGraphicsScene;
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
///    3e) At the end of the drag, the Handle is no longer needed so it transitions to Null state
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
/// # null = A noop state. The Guideline is no longer useful and has been retired
/// # handle = This Guideline is invisible, being dragged, and moving a bound deployed
///            Guideline along the same drag trajectory
/// # lurking = Template Guideline state for when active but not seen, and waiting for hover
class Guideline : public QObject, public QGraphicsLineItem
{
  Q_OBJECT;

public:
  /// Single constructor.
  Guideline(QGraphicsScene &scene,
            Guidelines &guidelines,
            GuidelineState guidelineStateInitial);
  ~Guideline();

  /// Bind a newly-created visible Guideline to this Guideline, and make this one invisible
  void bindGuidelineVisible (Guideline *guidelineVisible);

  /// Show/hide the Guideline objects
  void handleShowHide (bool show);

  /// Highlight this Guideline upon hover enter
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /// Unset highlighting triggered by hover enter
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  /// Forwad movements to visible Guideline
  virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

  /// Forward press event to state machine
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /// Cleanup after being dragged
  virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

  /// Override painting so this disappears when selected. Selected Guidelines are never visible
  virtual void paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget = Q_NULLPTR);

  /// Set pen color and line width
  void setPenColor (const QColor &color,
                    double lineWidth);

  /// Update the geometry so it passes through the specified point
  void updateGeometry (const QPointF &pos);

signals:

  /// Signal for cloned deployed Guideline from handle Guideline
  void signalHandleMoved (QPointF);

public slots:

  /// Slot for signal from cloned deployed Guideline from handle Guideline
  void slotHandleMoved (QPointF posScreen);

private:
  Guideline();

  // Forces use of setPenColor instead of QGraphicsLineItem::setPen
  using QGraphicsLineItem::setPen;

  // Context is allocated as a final step in the constructor, at which point
  // this class has registered with the QGraphicsScene
  GuidelineStateContext *m_context;

  // After binding to visible Guideline
  Guideline *m_guidelineVisible;

};

#endif // GUIDELINE_H
