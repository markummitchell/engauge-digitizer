#ifndef CURVE_SETTINGS_INT_H
#define CURVE_SETTINGS_INT_H

#include "ColorFilterSettings.h"
#include "CurveConnectAs.h"
#include "LineStyle.h"
#include "PointStyle.h"

/// Internal settings for one curve, such as LineStyle, PointStyle and CurveFilter. These settings are used only
/// internally by Curve, and are not related to the DlgSettings classes at all
class CurveSettingsInt
{
 public:
  /// Single constructor.
  CurveSettingsInt(const ColorFilterSettings &colorFilterSettings,
                   const PointStyle &pointStyle,
                   const LineStyle &lineStyle,
                   CurveConnectAs curveConnectAs);

  /// Get method for connection method.
  CurveConnectAs curveConnectAs () const;

  /// Get method for color filter.
  ColorFilterSettings colorFilterSettings () const;

  /// Get method for line style.
  LineStyle lineStyle () const;

  /// Get method for point style.
  PointStyle pointStyle () const;

 private:
  CurveSettingsInt();

  ColorFilterSettings m_colorFilterSettings;
  PointStyle m_pointStyle;
  LineStyle m_lineStyle;
  CurveConnectAs m_curveConnectAs;
};

#endif // CURVE_SETTINGS_INT_H
