#include "CallbackGatherXThetaValuesFunctions.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetaValuesFunctions::CallbackGatherXThetaValuesFunctions(const DocumentModelExport &modelExport,
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

CallbackSearchReturn CallbackGatherXThetaValuesFunctions::callback (const QString &curveName,
                                                                    const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::callback"
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

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValues () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValues";

  if (m_modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC) {

    // Convert the gathered values into a periodic sequence
    double xThetaMin = m_xThetaValues.firstKey();
    double xThetaMax = m_xThetaValues.lastKey();

    ValuesVectorXOrY values;
    double xTheta = xThetaMin;
    while (xTheta <= xThetaMax) {
      values [xTheta] = true;
      xTheta += m_modelExport.pointsIntervalFunctions();
    }

    // Unless the last xTheta value exactly equals xThetaMax, we add one more point so last little piece
    // is included

    return values.keys();

  } else {

    // Return the gathered values
    return m_xThetaValues.keys();

  }
}

