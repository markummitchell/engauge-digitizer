#ifndef POINT_STYLE_H
#define POINT_STYLE_H

#include "ColorPalette.h"
#include "PointShape.h"
#include <QColor>
#include <QPolygonF>

/// Details for a specific Point.
class PointStyle
{
public:
  /// Default constructor only for use when this class is being stored by a container that requires the default constructor.
  PointStyle ();

  /// Normal constructor. The style type and radius are determined by the currently selected Curve
  PointStyle(PointShape pointShape,
             unsigned int radius,
             ColorPalette paletteColor);

  /// Copy constructor.
  PointStyle (const PointStyle &other);

  /// Assignment constructor.
  PointStyle &operator=(const PointStyle &other);

  /// Return the color to be applied to the QGraphicsItem.
  QColor color () const;

  /// Return true if point is a circle, otherwise it is a polygon. For a circle, the radius is important and no polygon is needed from this class
  bool isCircle () const;

  /// Get method for point color.
  ColorPalette paletteColor () const;

  /// Get method for point shape.
  PointShape pointShape () const;

  /// Return the polygon for creating a QGraphicsPolygonItem. The size is determined by the radius
  QPolygonF polygon () const;

  /// Radius of point. For a circle this is all that is needed to draw a circle. For a polygon, the radius determines the size of the polygon
  int radius () const;

private:

  PointShape m_pointShape;
  unsigned int m_radius;
  ColorPalette m_paletteColor;
};

#endif // POINT_STYLE_H
