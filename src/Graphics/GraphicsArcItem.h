/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ARCITEM_H
#define GRAPHICS_ARCITEM_H

#include <QGraphicsEllipseItem>

/// Draw an arc as an ellipse but without lines from the center to the start and end points
///
/// Note that QGraphicsEllipseItem needs help when drawing with any span angle less than 360 degrees.
/// Without help, there are artifacts left on the screen as the start and/or span angle get changed,
/// the start and stop angles drawn are unrelated to the requested start and stop angles, and some pixels
/// do not get drawn. See QTDEBUG-80937
///
/// Originally this class overrode QGraphicsEllipseItem::boundingRect and called QGraphicsScene::boundingRect.
/// However, that led to an infinite loop since QGraphicsScene::boundingRect looped back around to
/// QGraphicsEllipseItem::boundingRect
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

  /// Paint without interior fill
  virtual void paint (QPainter *painter,
                      const QStyleOptionGraphicsItem *option,
                      QWidget *widget);

private:
  GraphicsArcItem();

};

#endif // GRAPHICS_ARCITEM_H
