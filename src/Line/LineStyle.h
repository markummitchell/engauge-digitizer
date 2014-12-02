#ifndef LINE_STYLE_H
#define LINE_STYLE_H

#include "ColorPalette.h"
#include "CurveConnectAs.h"
#include <QColor>

class QXmlStreamWriter;

/// Details for a specific Line.
class LineStyle
{
public:
  /// Default constructor only for use when this class is being stored by a container that requires the default constructor.
  LineStyle ();

  /// Single constructor.
  LineStyle (unsigned int width,
             ColorPalette paletteColor,
             CurveConnectAs curveConnectAs);

  /// Copy constructor.
  LineStyle (const LineStyle &other);

  /// Assignment operator.
  LineStyle &operator= (const LineStyle &other);

  /// Return the line color.
  QColor color () const;

  /// Get method for connect type.
  CurveConnectAs curveConnectAs () const;

  /// Initial default for axes curve.
  static LineStyle defaultAxesCurve ();

  /// Initial default for index'th graph curve.
  static LineStyle defaultGraphCurve (int index);

  /// Line color.
  ColorPalette paletteColor() const;

  /// Save style to stream.
  void saveStyle(QXmlStreamWriter &stream,
                 const QString &curveName) const;

  /// Set connect as.
  void setCurveConnectAs (CurveConnectAs curveConnectAs);

  /// Set method for line color.
  void setPaletteColor (ColorPalette paletteColor);

  /// Set width of line.
  void setWidth (int width);

  /// Width of line.
  unsigned int width () const;

private:

  unsigned int m_width;
  ColorPalette m_paletteColor;
  CurveConnectAs m_curveConnectAs;
};

#endif // LINE_STYLE_H
