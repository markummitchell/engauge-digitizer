#ifndef CURVE_STYLE_H
#define CURVE_STYLE_H

#include "LineStyle.h"
#include "PointStyle.h"

class QTextStream;
class QXmlStreamReader;
class QXmlStreamWriter;

/// Container for LineStyle and PointStyle for one Curve
class CurveStyle
{
public:
  /// Default constructor
  CurveStyle();

  /// Constructor with styles
  CurveStyle (const LineStyle &lineStyle,
              const PointStyle &pointStyle);

  /// Get method for LineStyle
  LineStyle lineStyle() const;

  /// Load from serialized xml. Returns the curve name
  QString loadXml (QXmlStreamReader &reader);

  /// Get method for PointStyle
  PointStyle pointStyle() const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  /// Serialize to xml
  void saveXml(QXmlStreamWriter &writer,
               const QString &curveName) const;

  /// Set method for line color in specified curve.
  void setLineColor (ColorPalette lineColor);

  /// Set method for connect as method for lines in specified curve.
  void setLineConnectAs (CurveConnectAs curveConnectAs);

  /// Set method for LineStyle
  void setLineStyle (const LineStyle &lineStyle);

  /// Set method for line width in specified curve.
  void setLineWidth (int width);

  /// Set method curve point color in specified curve.
  void setPointColor (ColorPalette curveColor);

  /// Set method for curve point perimeter line width.
  void setPointLineWidth (int width);

  /// Set method for curve point radius.
  void setPointRadius (int radius);

  /// Set method for curve point shape in specified curve.
  void setPointShape (PointShape shape);

  /// Set method for PointStyle
  void setPointStyle (const PointStyle &pointStyle);

private:

  PointStyle m_pointStyle;
  LineStyle m_lineStyle;
};

#endif // CURVE_STYLE_H
