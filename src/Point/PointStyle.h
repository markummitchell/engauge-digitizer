#ifndef POINT_STYLE_H
#define POINT_STYLE_H

#include "ColorPalette.h"
#include "PointShape.h"
#include <QColor>
#include <QPolygonF>

class QXmlStreamReader;
class QXmlStreamWriter;

/// Details for a specific Point.
class PointStyle
{
public:
  /// Default constructor only for use when this class is being stored by a container that requires the default constructor.
  PointStyle ();

  /// Normal constructor. The style type and radius are determined by the currently selected Curve
  PointStyle(PointShape pointShape,
             unsigned int radius,
             double lineWidth,
             ColorPalette paletteColor);

  /// Copy constructor.
  PointStyle (const PointStyle &other);

  /// Assignment constructor.
  PointStyle &operator=(const PointStyle &other);

  /// Initial default for axes curve.
  static PointStyle defaultAxesCurve ();

  /// Initial default for index'th graph curve.
  static PointStyle defaultGraphCurve (int index);

  /// Return true if point is a circle, otherwise it is a polygon. For a circle, the radius is important and no polygon is needed from this class
  bool isCircle () const;

  /// Get method for line width.
  double lineWidth () const;

  /// Load model from serialized xml. Returns the curve name
  QString loadXml(QXmlStreamReader &reader);

  /// Get method for point color.
  ColorPalette paletteColor () const;

  /// Return the polygon for creating a QGraphicsPolygonItem. The size is determined by the radius
  QPolygonF polygon () const;

  /// Radius of point. For a circle this is all that is needed to draw a circle. For a polygon, the radius determines the size of the polygon
  int radius () const;

  /// Serialize to stream
  void saveXml(QXmlStreamWriter &writer,
               const QString &curveName) const;

  /// Set method for line width.
  void setLineWidth (double width);

  /// Set method for point color.
  void setPaletteColor (ColorPalette paletteColor);

  /// Set method for point radius.
  void setRadius (int radius);

  /// Set method for point shape.
  void setShape (PointShape shape);

  /// Get method for point shape.
  PointShape shape () const;

private:

  PointShape m_shape;
  unsigned int m_radius;
  double m_lineWidth;
  ColorPalette m_paletteColor;
};

#endif // POINT_STYLE_H
