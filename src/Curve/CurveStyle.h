#ifndef CURVE_STYLE_H
#define CURVE_STYLE_H

#include "LineStyle.h"
#include "PointStyle.h"

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

  /// Serialize to xml
  void saveXml(QXmlStreamWriter &writer,
               const QString &curveName) const;

  /// Set method for LineStyle
  void setLineStyle (const LineStyle &lineStyle);

  /// Set method for PointStyle
  void setPointStyle (const PointStyle &pointStyle);

private:

  PointStyle m_pointStyle;
  LineStyle m_lineStyle;
};

#endif // CURVE_STYLE_H
