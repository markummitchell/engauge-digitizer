#include "CurveSettingsInt.h"

CurveSettingsInt::CurveSettingsInt (const CurveFilter &curveFilter,
                                    const PointStyle &pointStyle,
                                    const LineStyle &lineStyle,
                                    CurveConnectAs curveConnectAs) :
  m_curveFilter (curveFilter),
  m_pointStyle (pointStyle),
  m_lineStyle (lineStyle),
  m_curveConnectAs (curveConnectAs)
{
}

CurveConnectAs CurveSettingsInt::curveConnectAs () const
{
  return m_curveConnectAs;
}

CurveFilter CurveSettingsInt::curveFilter () const
{
  return m_curveFilter;
}

LineStyle CurveSettingsInt::lineStyle () const
{
  return m_lineStyle;
}

PointStyle CurveSettingsInt::pointStyle () const
{
  return m_pointStyle;
}
