#include "CurveSettingsInt.h"

CurveSettingsInt::CurveSettingsInt (const ColorFilterSettings &colorFilterSettings,
                                    const PointStyle &pointStyle,
                                    const LineStyle &lineStyle,
                                    CurveConnectAs curveConnectAs) :
  m_colorFilterSettings (colorFilterSettings),
  m_pointStyle (pointStyle),
  m_lineStyle (lineStyle),
  m_curveConnectAs (curveConnectAs)
{
}

ColorFilterSettings CurveSettingsInt::colorFilterSettings () const
{
  return m_colorFilterSettings;
}

CurveConnectAs CurveSettingsInt::curveConnectAs () const
{
  return m_curveConnectAs;
}

LineStyle CurveSettingsInt::lineStyle () const
{
  return m_lineStyle;
}

PointStyle CurveSettingsInt::pointStyle () const
{
  return m_pointStyle;
}
