#ifndef CURVE_STYLE_H
#define CURVE_STYLE_H

#include "CurveConnectAs.h"
#include "LineStyle.h"
#include "PointStyle.h"

/// Style for one curve.
class CurveStyle
{
 public:
  /// Single constructor.
  CurveStyle(const PointStyle &pointStyle,
             const LineStyle &lineStyle,
             CurveConnectAs curveConnectAs);

  /// Get method for connection method.
  CurveConnectAs curveConnectAs () const;

  /// Get method for line style.
  LineStyle lineStyle () const;

  /// Get method for point style.
  PointStyle pointStyle () const;

 private:
  CurveStyle();

  PointStyle m_pointStyle;
  LineStyle m_lineStyle;
  CurveConnectAs m_curveConnectAs;
};

#endif // CURVE_STYLE_H
