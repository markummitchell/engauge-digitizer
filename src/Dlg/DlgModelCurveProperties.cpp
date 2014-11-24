#include "CmdMediator.h"
#include "DlgModelCurveProperties.h"

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

LineStyles DlgModelCurveProperties::lineStyles () const
{
  return m_lineStyles;
}

PointStyles DlgModelCurveProperties::pointStyles () const
{
  return m_pointStyles;
}
