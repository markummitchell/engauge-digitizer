#include "CallbackGatherXThetaValuesFunctions.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
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

void CallbackGatherXThetaValuesFunctions::firstSimplestNumberLinear (double &xThetaFirstSimplestNumber,
                                                                     double &xThetaMin,
                                                                     double &xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::firstSimplestNumberLinear";

  // X/theta range
  xThetaMin = m_xThetaValues.firstKey();
  xThetaMax = m_xThetaValues.lastKey();

  // Compute offset that gives the simplest numbers
  ExportAlignLinear alignLinear (xThetaMin,
                                 xThetaMax);

  xThetaFirstSimplestNumber = alignLinear.firstSimplestNumber();
}

void CallbackGatherXThetaValuesFunctions::firstSimplestNumberLog (double &xThetaFirstSimplestNumber,
                                                                  double &xThetaMin,
                                                                  double &xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::firstSimplestNumberLog";

  // X/theta range
  xThetaMin = m_xThetaValues.firstKey();
  xThetaMax = m_xThetaValues.lastKey();

  // Compute offset that gives the simplest numbers
  ExportAlignLog alignLog (xThetaMin,
                           xThetaMax);

  xThetaFirstSimplestNumber = alignLog.firstSimplestNumber();
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValues () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValues";

  if (m_modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC) {

    if (m_transformation.modelCoords().coordScaleXTheta() == COORD_SCALE_LINEAR) {
      return xThetaValuesInterpolatePeriodicLinear ();
    } else {
      return xThetaValuesInterpolatePeriodicLog ();
    }

  } else {

    // Return the gathered values
    return m_xThetaValues.keys();

  }
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLinear() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLinear";

  double xThetaFirstSimplestNumber, xThetaMin, xThetaMax;
  firstSimplestNumberLinear (xThetaFirstSimplestNumber,
                             xThetaMin,
                             xThetaMax);

    // Assuming user picks an appropriate interval increment, numbering starting at xThetaFirstSimplestNumber will give nice x/theta numbers
  if (m_modelExport.pointsIntervalUnitsFunctions() == EXPORT_POINTS_INTERVAL_UNITS_GRAPH) {
    return xThetaValuesInterpolatePeriodicLinearGraph(xThetaFirstSimplestNumber,
                                                      xThetaMin,
                                                      xThetaMax);
  } else {
    return xThetaValuesInterpolatePeriodicLinearScreen(xThetaFirstSimplestNumber,
                                                       xThetaMin,
                                                       xThetaMax);
  }
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLinearGraph(double xThetaFirstSimplestNumber,
                                                                                                 double xThetaMin,
                                                                                                 double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLinearGraph";

  // Convert the gathered values into a periodic sequence
  ValuesVectorXOrY values;
  double xTheta = xThetaFirstSimplestNumber;
  while (xTheta > xThetaMin) {
    xTheta -= m_modelExport.pointsIntervalFunctions(); // Go backwards until reaching or passing minimum
  }
  if (xTheta < xThetaMin) {
    values [xThetaMin] = true; // We passed minimum so insert point right at xThetaMin
  }

  xTheta += m_modelExport.pointsIntervalFunctions();
  while (xTheta <= xThetaMax) {
    values [xTheta] = true;
    xTheta += m_modelExport.pointsIntervalFunctions(); // Insert point at a simple number
  }

  if (xTheta > xThetaMax) {
    values [xThetaMax] = xThetaMax; // We passed maximum so insert point right at xThetaMax
  }

  return values.keys();
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLinearScreen (double xThetaFirstSimplestNumber,
                                                                                                   double xThetaMin,
                                                                                                   double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLinearScreen";

  // Convert the gathered values into a periodic sequence
  ValuesVectorXOrY values;
  double xTheta = xThetaFirstSimplestNumber;
  while (xTheta > xThetaMin) {
    xTheta -= m_modelExport.pointsIntervalFunctions(); // Go backwards until reaching or passing minimum
  }
  if (xTheta < xThetaMin) {
    values [xThetaMin] = true; // We passed minimum so insert point right at xThetaMin
  }

  xTheta += m_modelExport.pointsIntervalFunctions();
  while (xTheta <= xThetaMax) {
    values [xTheta] = true;
    xTheta += m_modelExport.pointsIntervalFunctions(); // Insert point at a simple number
  }

  if (xTheta > xThetaMax) {
    values [xThetaMax] = xThetaMax; // We passed maximum so insert point right at xThetaMax
  }

  return values.keys();
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLog() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLog";

  double xThetaFirstSimplestNumber, xThetaMin, xThetaMax;
  firstSimplestNumberLog (xThetaFirstSimplestNumber,
                          xThetaMin,
                          xThetaMax);

  // Assuming user picks an appropriate interval increment, numbering starting at xThetaFirstSimplestNumber will give nice x/theta numbers
  if (m_modelExport.pointsIntervalUnitsFunctions() == EXPORT_POINTS_INTERVAL_UNITS_GRAPH) {
    return xThetaValuesInterpolatePeriodicLogGraph(xThetaFirstSimplestNumber,
                                                   xThetaMin,
                                                   xThetaMax);
  } else {
    return xThetaValuesInterpolatePeriodicLogScreen(xThetaFirstSimplestNumber,
                                                    xThetaMin,
                                                    xThetaMax);
  }
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLogGraph (double xThetaFirstSimplestNumber,
                                                                                               double xThetaMin,
                                                                                               double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLogGraph";

  // Convert the gathered values into a periodic sequence
  ValuesVectorXOrY values;
  double xTheta = xThetaFirstSimplestNumber;
  while (xTheta > xThetaMin) {
    xTheta /= m_modelExport.pointsIntervalFunctions(); // Go backwards until reaching or passing minimum
  }
  if (xTheta < xThetaMin) {
    values [xThetaMin] = true; // We passed minimum so insert point right at xThetaMin
  }

  xTheta *= m_modelExport.pointsIntervalFunctions();
  while (xTheta <= xThetaMax) {
    values [xTheta] = true;
    xTheta *= m_modelExport.pointsIntervalFunctions(); // Insert point at a simple number
  }

  if (xTheta > xThetaMax) {
    values [xThetaMax] = xThetaMax; // We passed maximum so insert point right at xThetaMax
  }

  return values.keys();
}

ExportValuesXOrY CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLogScreen (double xThetaFirstSimplestNumber,
                                                                                                double xThetaMin,
                                                                                                double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "CallbackGatherXThetaValuesFunctions::xThetaValuesInterpolatePeriodicLogScreen";

  // Convert the gathered values into a periodic sequence
  ValuesVectorXOrY values;
  double xTheta = xThetaFirstSimplestNumber;
  while (xTheta > xThetaMin) {
    xTheta /= m_modelExport.pointsIntervalFunctions(); // Go backwards until reaching or passing minimum
  }
  if (xTheta < xThetaMin) {
    values [xThetaMin] = true; // We passed minimum so insert point right at xThetaMin
  }

  xTheta *= m_modelExport.pointsIntervalFunctions();
  while (xTheta <= xThetaMax) {
    values [xTheta] = true;
    xTheta *= m_modelExport.pointsIntervalFunctions(); // Insert point at a simple number
  }

  if (xTheta > xThetaMax) {
    values [xThetaMax] = xThetaMax; // We passed maximum so insert point right at xThetaMax
  }

  return values.keys();
}
