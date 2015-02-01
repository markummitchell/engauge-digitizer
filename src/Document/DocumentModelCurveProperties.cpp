#include "CmdMediator.h"
#include "DocumentModelCurveProperties.h"
#include "Logger.h"
#include <QDebug>
#include <QXmlStreamWriter>

DocumentModelCurveProperties::DocumentModelCurveProperties()
{
}

DocumentModelCurveProperties::DocumentModelCurveProperties (const Document &document)
{
  // Axis curve
  const Curve &curveAxes = document.curveAxes();
  m_lineStyles [AXIS_CURVE_NAME] = curveAxes.lineStyle();
  m_pointStyles [AXIS_CURVE_NAME] = curveAxes.pointStyle ();

  // Graph curves
  QStringList graphCurveNames = document.curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = document.curveForCurveName(graphCurveName);
    m_lineStyles [graphCurveName] = graphCurve->lineStyle();
    m_pointStyles [graphCurveName] = graphCurve->pointStyle ();
  }
}

DocumentModelCurveProperties::DocumentModelCurveProperties (const DocumentModelCurveProperties &other)
{
  // Line styles
  LineStyles::const_iterator itrL;
  for (itrL = other.lineStyles().constBegin (); itrL != other.lineStyles().constEnd(); itrL++) {
    QString curveName = itrL.key();
    LineStyle lineStyle = itrL.value();
    m_lineStyles [curveName] = lineStyle;
  }

  // Point styles
  PointStyles::const_iterator itrP;
  for (itrP = other.pointStyles().constBegin(); itrP != other.pointStyles().constEnd(); itrP++) {
    QString curveName = itrP.key();
    PointStyle pointStyle = itrP.value();   
    m_pointStyles [curveName] = pointStyle;
  }
}

DocumentModelCurveProperties &DocumentModelCurveProperties::operator=(const DocumentModelCurveProperties &other)
{
  // Line styles
  LineStyles::const_iterator itrL;
  for (itrL = other.lineStyles().constBegin (); itrL != other.lineStyles().constEnd(); itrL++) {
    QString curveName = itrL.key();
    LineStyle lineStyle = itrL.value();
    m_lineStyles [curveName] = lineStyle;
  }

  // Point styles
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

double DocumentModelCurveProperties::lineWidth (const QString &curveName) const
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

double DocumentModelCurveProperties::pointLineWidth (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName].lineWidth();
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

  // Line styles
  LineStyles::const_iterator itrL;
  for (itrL = m_lineStyles.constBegin(); itrL != m_lineStyles.constEnd(); itrL++) {
    QString curveName = itrL.key();
    const LineStyle &lineStyle = itrL.value();
    lineStyle.saveStyle(stream,
                        curveName);
  }

  // Point styles
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

void DocumentModelCurveProperties::setPointLineWidth (const QString &curveName,
                                                      double width)
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  m_pointStyles [curveName].setLineWidth (width);
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

