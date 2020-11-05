/******************************************************************************************************
 * (C) 2020 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRAPHICS_ARC_AS_PATH_ITEM_H
#define GRAPHICS_ARC_AS_PATH_ITEM_H

#include <QGraphicsPathItem>

/// Draw an arc as an ellipse but without lines from the center to the start and end points
///
/// This version, as compared to GraphicsArcAsPathItem, does not use QGraphicsEllipseItem since that
/// gives obvious artifacts when drawing with any span angle less than 360 degrees, as the line
/// get moved around. See QTDEBUG-80937. This version sacrifices cleanly drawn lines for artifact-free drawing.
class GraphicsArcAsPathItem : public QGraphicsPathItem
{
public:
  /// Constructor with individual coordinates
  GraphicsArcAsPathItem(double x,
                        double y,
                        double width,
                        double height,
                        QGraphicsItem *parent = 0);

  /// Constructor with coordinates specified as rectangle
  GraphicsArcAsPathItem(const QRectF &rect,
                  QGraphicsItem *parent = 0);

  /// Emulate QGraphicsEllipseItem::setSpanAngle
  void setSpanAngle (int spanAngle);

  /// Emulate QGraphicsEllipseItem::setStartAngle
  void setStartAngle (int startAngle);

private:
  GraphicsArcAsPathItem();

  void updateGeometry ();

  double m_x;
  double m_y;
  double m_width;
  double m_height;
  int m_startAngle; // In tics
  int m_spanAngle; // In tics
};

#endif // GRAPHICS_ARC_AS_PATH_ITEM_H
