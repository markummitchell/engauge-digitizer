/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ARC_ITEM_H
#define GRAPHICS_ARC_ITEM_H

#include <QGraphicsEllipseItem>

/// Draw an arc as an ellipse but without lines from the center to the start and end points
///
/// Use within GraphicsArcItemRelay when there is a possibility that geometry updates
/// would be done while an event handler is executing
///
/// This class probably requires the circumscribed rectangle used to construct the ellipse
/// to be normalized to prevent QTBUG-80937
class GraphicsArcItem : public QGraphicsEllipseItem
{
public:
  /// Default constructor. This needs, at a minimum, a later call to setRect
  GraphicsArcItem();

  /// Constructor with individual coordinates. Also sets transform origin point
  GraphicsArcItem(double x,
                  double y,
                  double width,
                  double height,
                  QGraphicsItem *parent = 0);

  /// Constructor with coordinates specified as rectangle
  GraphicsArcItem(const QRectF &rect,
                  QGraphicsItem *parent = 0);

  /// Paint without interior fill
  virtual void paint (QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget);

  /// Set bounding rectangle. Updates transform origin point
  virtual void setRect (const QRectF &rect);

  /// Set bounding rectangle. Updates transform origin point
  virtual void setRect (double x,
                        double y,
                        double width,
                        double height);

};

#endif // GRAPHICS_ARCITEM_H
