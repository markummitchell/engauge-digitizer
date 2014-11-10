#include "CurveStyle.h"

CurveStyle::CurveStyle (const PointStyle &pointStyle,
                        const LineStyle &lineStyle,
                        CurveConnectAs curveConnectAs) :
  m_pointStyle (pointStyle),
  m_lineStyle (lineStyle),
  m_curveConnectAs (curveConnectAs)
{
}

CurveConnectAs CurveStyle::curveConnectAs () const
{
  return m_curveConnectAs;
}

LineStyle CurveStyle::lineStyle () const
{
  return m_lineStyle;
}

PointStyle CurveStyle::pointStyle () const
{
  return m_pointStyle;
}
