/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetasInCurves.h"
#include "DocumentModelExportFormat.h"
#include "EngaugeAssert.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetasInCurves::CallbackGatherXThetasInCurves(const DocumentModelExportFormat &modelExport,
                                                             const QStringList &curvesIncluded,
                                                             const Transformation &transformation) :
  CallbackGatherXThetasAbstractBase ((modelExport.pointsSelectionFunctions() ==
                                      EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE),
                                     modelExport.extrapolateOutsideEndpoints (),
                                     curvesIncluded,
                                     transformation)
{
}

CallbackSearchReturn CallbackGatherXThetasInCurves::callback (const QString &curveName,
                                                              const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackGatherXThetasInCurves::callback"
                               << " curveName=" << curveName.toLatin1().data()
                               << " point=" << point.identifier().toLatin1().data();

  updateMinMax (curveName,
                point);

  if (curvesIncludedHash ().contains (curveName)) {

    QPointF posGraph;
    transformation ().transformScreenToRawGraph (point.posScreen(),
                                                 posGraph);
    addGraphX (posGraph.x ());
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}
