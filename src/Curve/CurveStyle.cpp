#include "CurveStyle.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

CurveStyle::CurveStyle()
{
}

CurveStyle::CurveStyle (const LineStyle &lineStyle,
                        const PointStyle &pointStyle) :
  m_pointStyle (pointStyle),
  m_lineStyle (lineStyle)
{
}

LineStyle CurveStyle::lineStyle() const
{
  return m_lineStyle;
}

QString CurveStyle::loadXml(QXmlStreamReader &reader)
{

}

PointStyle CurveStyle::pointStyle() const
{
  return m_pointStyle;
}

void CurveStyle::saveXml(QXmlStreamWriter &writer,
                         const QString &curveName) const
{

}

void CurveStyle::setLineStyle(const LineStyle &lineStyle)
{
  m_lineStyle = lineStyle;
}

void CurveStyle::setPointStyle(const PointStyle &pointStyle)
{
  m_pointStyle = pointStyle;
}
