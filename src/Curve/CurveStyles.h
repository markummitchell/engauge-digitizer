#ifndef CURVE_STYLES_H
#define CURVE_STYLES_H

#include "ColorPalette.h"
#include "CurveStyle.h"
#include <QHash>
#include <QString>

class Document;
class QXmlStreamReader;
class QXmlStreamWriter;

typedef QHash<QString, CurveStyle> CurveStylesInternal;

/// Model for DlgSettingsCurveProperties and CmdSettingsCurveProperties.
class CurveStyles
{
public:
  /// Default constructor.
  CurveStyles();

  /// Initial constructor from Document.
  CurveStyles(const Document &document);

  /// Copy constructor.
  CurveStyles (const CurveStyles &other);

  /// Assignment constructor.
  CurveStyles &operator=(const CurveStyles &other);

  /// List of all curve names
  QStringList curveNames () const;

  /// CurveStyle in specified curve.
  CurveStyle curveStyle (const QString &curveName) const;

  /// Get method for line color in specified curve.
  ColorPalette lineColor (const QString &curveName) const;

  /// Get method for connect as method for lines in specified curve.
  CurveConnectAs lineConnectAs (const QString &curveName) const;

  /// Get method for copying one line style in one step.
  const LineStyle lineStyle (const QString &curveName) const;

  /// Get method for line width in specified curve.
  int lineWidth (const QString &curveName) const;

  /// Load from serialized xml
  void loadXml (QXmlStreamReader &reader);

  /// Get method for curve point color in specified curve.
  ColorPalette pointColor (const QString &curveName) const;

  /// Get method for curve point is circle in specified curve.
  bool pointIsCircle (const QString &curveName) const;

  /// Get method for curve point line width.
  int pointLineWidth (const QString &curveName) const;

  /// Get method for curve point polygon in specified curve.
  QPolygonF pointPolygon (const QString &curveName) const;

  /// Get method for curve point radius.
  int pointRadius (const QString &curveName) const;

  /// Get method for curve point shape.
  PointShape pointShape(const QString &curveName) const;

  /// Get method for copying one point style. Cannot return just a reference or else there is a warning about returning reference to temporary
  const PointStyle pointStyle (const QString &curveName) const;

  /// Serialize to xml
  void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for curve style
  void setCurveStyle (const QString &curveName,
                      const CurveStyle &curveStyle);

  /// Set method for line color in specified curve.
  void setLineColor (const QString &curveName,
                     ColorPalette lineColor);

  /// Set method for connect as method for lines in specified curve.
  void setLineConnectAs (const QString &curveName,
                         CurveConnectAs curveConnectAs);

  /// Set method for line width in specified curve.
  void setLineWidth (const QString &curveName,
                     int width);

  /// Set method curve point color in specified curve.
  void setPointColor (const QString &curveName,
                      ColorPalette curveColor);

  /// Set method for curve point is circle in specified curve.
  void setPointIsCircle (const QString &curveName,
                         bool pointIsCircle);

  /// Set method for curve point perimeter line width.
  void setPointLineWidth (const QString &curveName,
                          int width);

  /// Set method for curve point radius.
  void setPointRadius (const QString &curveName,
                       int radius);

  /// Set method for curve point shape in specified curve.
  void setPointShape (const QString &curveName,
                      PointShape shape);

private:

  CurveStylesInternal m_curveStyles;

};

#endif // CURVE_STYLES_H
