#include "CallbackGatherXThetaValues.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"

CallbackGatherXThetaValues::CallbackGatherXThetaValues(const DocumentModelExport &modelExport,
                                                       const QStringList &curvesGraphsNames,
                                                       const Transformation &transformation) :
  m_modelExport (modelExport),
  m_transformation (transformation)
{
  // Build a list of curves to include by subtracting the excluded curves from the the complete list.
  // Special case is to use only first included curve if appropriate flag is set
  QStringList::const_iterator itr;
  for (itr = curvesGraphsNames.begin(); itr != curvesGraphsNames.end(); itr++) {

    QString curvesGraphName = *itr;

    if (!modelExport.curveNamesNotExported().contains (curvesGraphName)) {

      // Not excluded which means it gets included
      m_curveNamesIncluded [curvesGraphName] = true;

      if (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE) {
        // Quick exit since once curve is all we want
        break;
      }
    }
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

Values CallbackGatherXThetaValues::xThetaValues () const
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

