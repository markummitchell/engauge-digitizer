/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef POINT_STYLE_H
#define POINT_STYLE_H

#include "ColorPalette.h"
#include "PointShape.h"
#include <QColor>
#include <QPolygonF>

class QTextStream;
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
             int lineWidth,
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
  int lineWidth () const;

  /// Load model from serialized xml. Returns the curve name
  void loadXml(QXmlStreamReader &reader);

  /// Get method for point color.
  ColorPalette paletteColor () const;

  /// Return the polygon for creating a QGraphicsPolygonItem. The size is determined by the radius
  QPolygonF polygon () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Radius of point. For a circle this is all that is needed to draw a circle. For a polygon, the radius determines the size of the polygon
  unsigned int radius () const;

  /// Serialize to stream
  void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for line width.
  void setLineWidth (int width);

  /// Set method for point color.
  void setPaletteColor (ColorPalette paletteColor);

  /// Set method for point radius.
  void setRadius (unsigned int radius);

  /// Set method for point shape.
  void setShape (PointShape shape);

  /// Get method for point shape.
  PointShape shape () const;

private:

  PointShape m_shape;
  unsigned int m_radius;
  int m_lineWidth;
  ColorPalette m_paletteColor;
};

#endif // POINT_STYLE_H
