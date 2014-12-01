#include "CmdMediator.h"
#include "DlgModelCurveProperties.h"
#include "Logger.h"
#include <QDebug>
#include <QXmlStreamWriter>

DlgModelCurveProperties::DlgModelCurveProperties()
{
}

DlgModelCurveProperties::DlgModelCurveProperties (const CmdMediator &cmdMediator)
{
  const Curve &curveAxes = cmdMediator.document().curveAxes();
  m_lineStyles [AXIS_CURVE_NAME].setCurveConnectAs (curveAxes.lineStyle().curveConnectAs());
  m_lineStyles [AXIS_CURVE_NAME].setPaletteColor(curveAxes.lineStyle().paletteColor());
  m_lineStyles [AXIS_CURVE_NAME].setWidth(curveAxes.lineStyle().width());
  m_pointStyles [AXIS_CURVE_NAME].setPaletteColor(curveAxes.pointStyle ().paletteColor());
  m_pointStyles [AXIS_CURVE_NAME].setRadius(curveAxes.pointStyle().radius());
  m_pointStyles [AXIS_CURVE_NAME].setShape(curveAxes.pointStyle().shape());

  QStringList graphCurveNames = cmdMediator.document().curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = cmdMediator.document ().curveForCurveName(graphCurveName);
    m_lineStyles [graphCurveName].setCurveConnectAs (graphCurve->lineStyle().curveConnectAs());
    qDebug() << "shit1 "<< graphCurveName << " " << graphCurve->lineStyle().paletteColor();
    m_lineStyles [graphCurveName].setPaletteColor(graphCurve->lineStyle().paletteColor());
    m_lineStyles [graphCurveName].setWidth(graphCurve->lineStyle().width());
    m_pointStyles [graphCurveName].setPaletteColor(graphCurve->pointStyle ().paletteColor());
    m_pointStyles [graphCurveName].setRadius(graphCurve->pointStyle().radius());
    m_pointStyles [graphCurveName].setShape(graphCurve->pointStyle().shape());
  }
}

DlgModelCurveProperties::DlgModelCurveProperties (const DlgModelCurveProperties &other)
{
  LineStyles::const_iterator itrL;
  for (itrL = other.lineStyles().constBegin (); itrL != other.lineStyles().constEnd(); itrL++) {
    QString curveName = itrL.key();
    LineStyle lineStyle = itrL.value();
    qDebug() << "shit2 "<<curveName<< " " << itrL.value().paletteColor() << "->" << lineStyle.paletteColor();
    m_lineStyles [curveName] = lineStyle;
  }

  PointStyles::const_iterator itrP;
  for (itrP = other.pointStyles().constBegin(); itrP != other.pointStyles().constEnd(); itrP++) {
    QString curveName = itrP.key();
    PointStyle pointStyle = itrP.value();   
    m_pointStyles [curveName] = pointStyle;
  }
}

DlgModelCurveProperties &DlgModelCurveProperties::operator=(const DlgModelCurveProperties &other)
{
  LineStyles::const_iterator itrL;
  for (itrL = other.lineStyles().constBegin (); itrL != other.lineStyles().constEnd(); itrL++) {
    QString curveName = itrL.key();
    LineStyle lineStyle = itrL.value();
    qDebug() << "shit3 "<<curveName<<" "<< itrL.value().paletteColor() << "->" << lineStyle.paletteColor();
    m_lineStyles [curveName] = lineStyle;
  }

  PointStyles::const_iterator itrP;
  for (itrP = other.pointStyles().constBegin(); itrP != other.pointStyles().constEnd(); itrP++) {
    QString curveName = itrP.key();
    PointStyle pointStyle = itrP.value();
    m_pointStyles [curveName] = pointStyle;
  }

  return *this;
}

ColorPalette DlgModelCurveProperties::lineColor (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
    qDebug() << "shit4 "<<curveName<<" "<< m_lineStyles[curveName].paletteColor();
  return m_lineStyles [curveName].paletteColor();
}

CurveConnectAs DlgModelCurveProperties::lineConnectAs (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].curveConnectAs();
}

const LineStyles &DlgModelCurveProperties::lineStyles () const
{
  return m_lineStyles;
}

int DlgModelCurveProperties::lineWidth (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].width();
}

ColorPalette DlgModelCurveProperties::pointColor (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].paletteColor();
}

bool DlgModelCurveProperties::pointIsCircle (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].isCircle();
}

QPolygonF DlgModelCurveProperties::pointPolygon (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].polygon();
}

int DlgModelCurveProperties::pointRadius (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].radius();
}

PointShape DlgModelCurveProperties::pointShape (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].shape ();
}

const PointStyles &DlgModelCurveProperties::pointStyles() const
{
  return m_pointStyles;
}

void DlgModelCurveProperties::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgModelCurveProperties::saveModel";

  stream.writeStartElement("DlgModelCurveProperties");

  LineStyles::const_iterator itrL;
  for (itrL = m_lineStyles.constBegin(); itrL != m_lineStyles.constEnd(); itrL++) {
    const LineStyle &lineStyle = *itrL;
    lineStyle.saveStyle(stream);
  }

  PointStyles::const_iterator itrP;
  for (itrP = m_pointStyles.constBegin(); itrP != m_pointStyles.constEnd(); itrP++) {
    const PointStyle &pointStyle = *itrP;
    pointStyle.saveStyle(stream);
  }

  stream.writeEndElement();
}

void DlgModelCurveProperties::setLineColor (const QString &curveName,
                                            ColorPalette lineColor)
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setPaletteColor(lineColor);
    qDebug() << "shit6 "<< curveName<<" "<<lineColor<< "->"<< m_lineStyles[curveName].paletteColor();
}

void DlgModelCurveProperties::setLineConnectAs (const QString &curveName,
                                                CurveConnectAs curveConnectAs)
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setCurveConnectAs(curveConnectAs);
}

void DlgModelCurveProperties::setLineWidth (const QString &curveName,
                                            int width)
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setWidth(width);
}

void DlgModelCurveProperties::setPointColor (const QString &curveName,
                                             ColorPalette curveColor)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setPaletteColor(curveColor);
}

void DlgModelCurveProperties::setPointRadius (const QString &curveName,
                                              int radius)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setRadius (radius);
}

void DlgModelCurveProperties::setPointShape (const QString &curveName,
                                             PointShape shape)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setShape (shape);
}

