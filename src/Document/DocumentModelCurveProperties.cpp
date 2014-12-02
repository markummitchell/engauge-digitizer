#include "CmdMediator.h"
#include "DocumentModelCurveProperties.h"
#include "Logger.h"
#include <QDebug>
#include <QXmlStreamWriter>

DocumentModelCurveProperties::DocumentModelCurveProperties()
{
}

DocumentModelCurveProperties::DocumentModelCurveProperties (const CmdMediator &cmdMediator)
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

DocumentModelCurveProperties::DocumentModelCurveProperties (const DocumentModelCurveProperties &other)
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

DocumentModelCurveProperties &DocumentModelCurveProperties::operator=(const DocumentModelCurveProperties &other)
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

ColorPalette DocumentModelCurveProperties::lineColor (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
    qDebug() << "shit4 "<<curveName<<" "<< m_lineStyles[curveName].paletteColor();
  return m_lineStyles [curveName].paletteColor();
}

CurveConnectAs DocumentModelCurveProperties::lineConnectAs (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].curveConnectAs();
}

const LineStyles &DocumentModelCurveProperties::lineStyles () const
{
  return m_lineStyles;
}

int DocumentModelCurveProperties::lineWidth (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName].width();
}

ColorPalette DocumentModelCurveProperties::pointColor (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].paletteColor();
}

bool DocumentModelCurveProperties::pointIsCircle (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].isCircle();
}

QPolygonF DocumentModelCurveProperties::pointPolygon (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].polygon();
}

int DocumentModelCurveProperties::pointRadius (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].radius();
}

PointShape DocumentModelCurveProperties::pointShape (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].shape ();
}

const PointStyles &DocumentModelCurveProperties::pointStyles() const
{
  return m_pointStyles;
}

void DocumentModelCurveProperties::saveModel(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCurveProperties::saveModel";

  stream.writeStartElement("DocumentModelCurveProperties");

  LineStyles::const_iterator itrL;
  for (itrL = m_lineStyles.constBegin(); itrL != m_lineStyles.constEnd(); itrL++) {
    QString curveName = itrL.key();
    const LineStyle &lineStyle = itrL.value();
    lineStyle.saveStyle(stream,
                        curveName);
  }

  PointStyles::const_iterator itrP;
  for (itrP = m_pointStyles.constBegin(); itrP != m_pointStyles.constEnd(); itrP++) {
    QString curveName = itrP.key();
    const PointStyle &pointStyle = itrP.value();
    pointStyle.saveStyle(stream,
                         curveName);
  }

  stream.writeEndElement();
}

void DocumentModelCurveProperties::setLineColor (const QString &curveName,
                                            ColorPalette lineColor)
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setPaletteColor(lineColor);
    qDebug() << "shit6 "<< curveName<<" "<<lineColor<< "->"<< m_lineStyles[curveName].paletteColor();
}

void DocumentModelCurveProperties::setLineConnectAs (const QString &curveName,
                                                CurveConnectAs curveConnectAs)
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setCurveConnectAs(curveConnectAs);
}

void DocumentModelCurveProperties::setLineWidth (const QString &curveName,
                                            int width)
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  m_lineStyles [curveName].setWidth(width);
}

void DocumentModelCurveProperties::setPointColor (const QString &curveName,
                                             ColorPalette curveColor)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setPaletteColor(curveColor);
}

void DocumentModelCurveProperties::setPointRadius (const QString &curveName,
                                              int radius)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setRadius (radius);
}

void DocumentModelCurveProperties::setPointShape (const QString &curveName,
                                             PointShape shape)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setShape (shape);
}

