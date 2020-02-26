/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_ELLIPSE_H
#define GUIDELINE_ELLIPSE_H

#include "GuidelineAbstract.h"
#include <QColor>
#include <QGraphicsEllipseItem>

class QMouseEvent;
class QPainter;
class QGraphicsScene;
class QStyleOptionGraphicsItem;
class QWidget;

/// Ellipse version of GuidelineAbstract
class GuidelineEllipse : public GuidelineAbstract, public QGraphicsEllipseItem
{
public:
  /// Single constructor.
  GuidelineEllipse(QGraphicsScene &scene,
                   Guidelines &guidelines,
                   GuidelineState guidelineStateInitial,
                   const QString &identifier);
  ~GuidelineEllipse();

  /// Override normal QGraphicsEllipseItem collision detection that covers ellipse boundary
  /// and entire interior region, to exclude the interior region
  virtual bool collidesWithPath (const QPainterPath &path,
                                 Qt::ItemSelectionMode mode = Qt::IntersectsItemShape) const;

  virtual bool getGraphicsItemSelected () const;

  virtual bool getGraphicsItemAcceptHover () const;

  virtual QGraphicsItem::GraphicsItemFlags graphicsItemFlags () const;

  /// Highlight this Guideline upon hover enter
  virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

  /// Unset highlighting triggered by hover enter
  virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

  virtual QString identifier () const;

  /// Forward movements to visible Guideline
  virtual void mouseMoveEvent (QGraphicsSceneMouseEvent *event);

  /// Forward press event to state machine
  virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

  /// Cleanup after being dragged
  virtual void mouseReleaseEvent (QGraphicsSceneMouseEvent *event);

  /// Override painting so this disappears when selected. Selected Guidelines are never visible
  virtual void paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget = Q_NULLPTR);

  virtual void removeFromScene (QGraphicsScene *scene);
  virtual void setGraphicsItemAcceptHoverEvents (bool accept);
  virtual void setGraphicsItemFlags (QGraphicsItem::GraphicsItemFlags flags);
  virtual void setGraphicsItemLine (const QLineF &line);
  virtual void setGraphicsItemPen (const QColor &color,
                                   double lineWidth);
  virtual void setGraphicsItemVisible (bool visible);
  virtual void setGraphicsItemZValue (double z);
  virtual void updateColor ();
  virtual void updateGeometry (double valueGraph);
  virtual void updateGeometry (const QPointF &posScreen);
  
private:
  GuidelineEllipse();

  // Forces use of setPenColor instead of QGraphicsLineItem::setPen
  using QGraphicsEllipseItem::setPen;

};

#endif // GUIDELINE_ELLIPSE_H
