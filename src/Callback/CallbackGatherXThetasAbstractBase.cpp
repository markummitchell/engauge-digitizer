/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetasAbstractBase.h"
#include "DocumentModelExportFormat.h"
#include "EngaugeAssert.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetasAbstractBase::CallbackGatherXThetasAbstractBase(bool firstCurveOnly,
                                                                     bool extrapolateOutsideEndpoints,
                                                                     const QStringList &curvesIncluded,
                                                                     const Transformation &transformation) :
  m_extrapolateOutsideEndpoints (extrapolateOutsideEndpoints),
  m_curvesIncluded (curvesIncluded),
  m_transformation (transformation)
{
  // Include just the first curve, or all curves depending on DocumentModelExportFormat
  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;
    m_curvesIncludedHash [curveIncluded] = true;

    if (firstCurveOnly) {

      // We only want points belonging to the first included curve so exit this loop
      break;

    }
  }
}

CallbackGatherXThetasAbstractBase::~CallbackGatherXThetasAbstractBase()
{
}

void CallbackGatherXThetasAbstractBase::addGraphX (double xGraph)
{
  m_xThetaValues [xGraph] = true;
}

CurveLimits CallbackGatherXThetasAbstractBase::curveLimitsMax () const
{
  return m_curveLimitsMax;
}

CurveLimits CallbackGatherXThetasAbstractBase::curveLimitsMin () const
{
  return m_curveLimitsMin;
}

QStringList CallbackGatherXThetasAbstractBase::curvesIncluded () const
{
  return m_curvesIncluded;
}

CurvesIncludedHash CallbackGatherXThetasAbstractBase::curvesIncludedHash () const
{
  return m_curvesIncludedHash;
}

const Transformation &CallbackGatherXThetasAbstractBase::transformation () const
{
  return m_transformation;
}

void CallbackGatherXThetasAbstractBase::updateMinMax (const QString &curveName,
                                                      const Point &point)
{
  // Skip unless the endpoints are to be collected. We update the min/max values
  // even if the curve is not curvesIncludedHash since endpoints are sometimes
  // required for curves other than the first when collecting just xTheta values from
  // the first curve
  if (!m_extrapolateOutsideEndpoints) {

    QPointF posGraph;
    transformation ().transformScreenToRawGraph (point.posScreen(),
                                                 posGraph);

    if (!m_curveLimitsMin.contains (curveName) ||
        posGraph.x() < m_curveLimitsMin [curveName]) {

      m_curveLimitsMin [curveName] = posGraph.x ();
    }

    if (!m_curveLimitsMax.contains (curveName) ||
        posGraph.x() > m_curveLimitsMax [curveName]) {

      m_curveLimitsMax [curveName] = posGraph.x ();
    }
  }
}

ValuesVectorXOrY CallbackGatherXThetasAbstractBase::xThetaValuesRaw () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetasAbstractBase::xThetaValuesRaw";

  return m_xThetaValues;
}
