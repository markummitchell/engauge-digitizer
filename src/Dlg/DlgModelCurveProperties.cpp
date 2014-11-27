#include "CmdMediator.h"
#include "DlgModelCurveProperties.h"

DlgModelCurveProperties::DlgModelCurveProperties()
{
}

DlgModelCurveProperties::DlgModelCurveProperties (const CmdMediator &cmdMediator)
{
  const Curve &curveAxes = cmdMediator.document().curveAxes();
  m_lineStyles [AXIS_CURVE_NAME] = curveAxes.lineStyle ();
  m_pointStyles [AXIS_CURVE_NAME] = curveAxes.pointStyle ();

  QStringList graphCurveNames = cmdMediator.document().curvesGraphsNames();
  QStringList::const_iterator itr;
  for (itr = graphCurveNames.begin (); itr != graphCurveNames.end (); itr++) {

    const QString &graphCurveName = *itr;
    const Curve *graphCurve = cmdMediator.document ().curveForCurveName(graphCurveName);
    m_lineStyles [graphCurveName] = graphCurve->lineStyle ();
    m_pointStyles [graphCurveName] = graphCurve->pointStyle ();
  }
}

DlgModelCurveProperties::DlgModelCurveProperties (const DlgModelCurveProperties &other) :
  m_lineStyles (other.lineStyles ()),
  m_pointStyles (other.pointStyles ())
{
}

DlgModelCurveProperties &DlgModelCurveProperties::operator=(const DlgModelCurveProperties &other)
{
  m_lineStyles = other.lineStyles ();
  m_pointStyles = other.pointStyles ();

  return *this;
}

LineStyle DlgModelCurveProperties::lineStyleForCurveName (const QString &curveName) const
{
  Q_ASSERT (m_lineStyles.contains (curveName));
  return m_lineStyles [curveName];
}

LineStyles DlgModelCurveProperties::lineStyles () const
{
  return m_lineStyles;
}

PointStyle DlgModelCurveProperties::pointStyleForCurveName (const QString &curveName) const
{
  Q_ASSERT (m_pointStyles.contains (curveName));
  return m_pointStyles [curveName];
}

PointStyles DlgModelCurveProperties::pointStyles () const
{
  return m_pointStyles;
}

void DlgModelCurveProperties::setLineStyleForCurveName(const QString &curveName,
                                                       const LineStyle &lineStyle)
{
  m_lineStyles [curveName] = lineStyle;
}

void DlgModelCurveProperties::setPointStyleForCurveName(const QString &curveName,
                                                        const PointStyle &pointStyle)
{
  m_pointStyles [curveName] = pointStyle;
}
