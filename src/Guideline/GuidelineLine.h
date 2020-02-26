/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_LINE_H
#define GUIDELINE_LINE_H

#include "GuidelineAbstract.h"
#include <QColor>
#include <QGraphicsLineItem>

class QMouseEvent;
class QPainter;
class QGraphicsScene;
class QStyleOptionGraphicsItem;
class QWidget;

/// Line version of GuidelineAbstract
class GuidelineLine : public GuidelineAbstract, public QGraphicsLineItem
{
public:
  /// Single constructor.
  GuidelineLine(QGraphicsScene &scene,
                Guidelines &guidelines,
                GuidelineState guidelineStateInitial,
                const QString &identifier);
  ~GuidelineLine();

  virtual bool getGraphicsItemAcceptHover () const;

  virtual bool getGraphicsItemSelected () const;

  virtual QGraphicsItem::GraphicsItemFlags graphicsItemFlags () const;

  /// User toggled guideline visibility
  void handleVisibilityChange (bool visible);

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
  GuidelineLine();

  // Forces use of setPenColor instead of QGraphicsLineItem::setPen
  using QGraphicsLineItem::setPen;

};

#endif // GUIDELINE_LINE_H
