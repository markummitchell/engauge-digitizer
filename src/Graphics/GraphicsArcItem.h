/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ARCITEM_H
#define GRAPHICS_ARCITEM_H

#include <QGraphicsEllipseItem>

/// Draw an arc as an ellipse but without lines from the center to the start and end points
class GraphicsArcItem : public QGraphicsEllipseItem
{
public:
  /// Constructor with individual coordinates
  GraphicsArcItem(double x,
                  double y,
                  double width,
                  double height,
                  QGraphicsItem *parent = 0);

  /// Constructor with coordinates specified as rectangle
  GraphicsArcItem(const QRectF &rect,
                  QGraphicsItem *parent = 0);

  /// QGraphicsEllipseItem ignored transformation when computing bounding rectangle, although it should
  /// so we must make boundingRect smarter
  virtual QRectF boundingRect() const;

  /// Paint without interior fill
  virtual void paint (QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget);

private:
  GraphicsArcItem();

};

#endif // GRAPHICS_ARCITEM_H
