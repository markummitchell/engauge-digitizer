/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetasInCurves.h"
#include "DocumentModelExportFormat.h"
#include "EngaugeAssert.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetasInCurves::CallbackGatherXThetasInCurves(const DocumentModelExportFormat &modelExport,
                                                             const QStringList &curvesIncluded,
                                                             const Transformation &transformation) :
  m_transformation (transformation)
{
  bool firstCurveForGatherXTheta = (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);

  // Include just the first curve, or all curves depending on DocumentModelExportFormat
  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;
    m_curveNamesIncluded [curveIncluded] = true;

    if (firstCurveForGatherXTheta) {

      // We only want points belonging to the first included curve so exit this loop
      break;

    }
  }
}

CallbackSearchReturn CallbackGatherXThetasInCurves::callback (const QString &curveName,
                                                              const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackGatherXThetasInCurves::callback"
                               << " curveName=" << curveName.toLatin1().data()
                               << " point=" << point.identifier().toLatin1().data();

  if (m_curveNamesIncluded.contains (curveName)) {

    QPointF posGraph;
    m_transformation.transformScreenToRawGraph (point.posScreen(),
                                                posGraph);

    m_xThetaValues [posGraph.x ()] = true;
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

ValuesVectorXOrY CallbackGatherXThetasInCurves::xThetaValuesRaw () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetasInCurves::xThetaValuesRaw";

  return m_xThetaValues;
}
