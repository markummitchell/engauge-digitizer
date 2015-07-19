#include "CallbackGatherXThetaValues.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetaValues::CallbackGatherXThetaValues(const DocumentModelExport &modelExport,
                                                       const QStringList &curvesIncluded,
                                                       const Transformation &transformation) :
  m_modelExport (modelExport),
  m_transformation (transformation)
{
  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;
    m_curveNamesIncluded [curveIncluded] = true;
  }
}

CallbackSearchReturn CallbackGatherXThetaValues::callback (const QString &curveName,
                                                           const Point &point)
{
  LOG4CPP_DEBUG_S ((*mainCat)) << "CallbackGatherXThetaValues::callback"
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

ExportValues CallbackGatherXThetaValues::xThetaValues () const
{
  if (m_modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC) {

    // Convert the gathered values into a periodic sequence
    double xThetaMin = m_values.firstKey();
    double xThetaMax = m_values.lastKey();

    ValuesContainer values;
    double xTheta = xThetaMin;
    while (xTheta <= xThetaMax) {
      values [xTheta] = true;
      xTheta += m_modelExport.pointsInterval();
    }

    // Unless the last xTheta value exactly equals xThetaMax, we add one more point so last little piece
    // is included

    return values.keys();

  } else {

    // Return the gathered values
    return m_values.keys();

  }
}

