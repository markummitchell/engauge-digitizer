#include "CallbackGatherXThetaValuesRelations.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetaValuesRelations::CallbackGatherXThetaValuesRelations(const DocumentModelExport &modelExport,
                                                                         const QStringList &curvesIncluded,
                                                                         const Transformation &transformation) :
  m_modelExport (modelExport),
  m_transformation (transformation)
{
  bool firstCurveForGatherXTheta = (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE);

  // Included just the first curve, or all curves depending on DocumentModelExport
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

CallbackSearchReturn CallbackGatherXThetaValuesRelations::callback (const QString &curveName,
                                                                    const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackGatherXThetaValuesRelations::callback"
                               << " curveName=" << curveName.toLatin1().data()
                               << " point=" << point.identifier().toLatin1().data();

  if (m_curveNamesIncluded.contains (curveName)) {

    QPointF posGraph;
    m_transformation.transformScreenToRawGraph (point.posScreen(),
                                                posGraph);

    m_values [posGraph.x ()] = true;
  }

  return CALLBACK_SEARCH_RETURN_CONTINUE;
}

int CallbackGatherXThetaValuesRelations::xThetaValueCount () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesRelations::xThetaValueCount";

  return 0;
}

void CallbackGatherXThetaValuesRelations::xThetaValueSteps (double &xThetaMin,
                                                            double &xThetaStep)
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesRelations::xThetaValueSteps";

  xThetaMin = 0.0;
  xThetaStep = 0.0;
}
