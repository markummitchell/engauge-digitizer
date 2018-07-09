/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "ExportXThetaValuesMergedFunctions.h"
#include "Logger.h"
#include "Point.h"
#include <qmath.h>
#include "Transformation.h"

using namespace std;

ExportXThetaValuesMergedFunctions::ExportXThetaValuesMergedFunctions(const DocumentModelExportFormat &modelExport,
                                                                     const ValuesVectorXOrY &xThetaValuesRaw,
                                                                     const Transformation &transformation) :
  m_modelExport (modelExport),
  m_xThetaValuesRaw (xThetaValuesRaw),
  m_transformation (transformation)
{
}

void ExportXThetaValuesMergedFunctions::firstSimplestNumberLinear (double &xThetaFirstSimplestNumber,
                                                                   double &xThetaMin,
                                                                   double &xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::firstSimplestNumberLinear";

  // X/theta range
  xThetaMin = m_xThetaValuesRaw.firstKey();
  xThetaMax = m_xThetaValuesRaw.lastKey();

  // Compute offset that gives the simplest numbers
  ExportAlignLinear alignLinear (xThetaMin,
                                 xThetaMax);

  xThetaFirstSimplestNumber = alignLinear.firstSimplestNumber ();
}

void ExportXThetaValuesMergedFunctions::firstSimplestNumberLog (double &xThetaFirstSimplestNumber,
                                                                double &xThetaMin,
                                                                double &xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::firstSimplestNumberLog";

  // X/theta range
  xThetaMin = m_xThetaValuesRaw.firstKey();
  xThetaMax = m_xThetaValuesRaw.lastKey();

  // Compute offset that gives the simplest numbers
  ExportAlignLog alignLog (xThetaMin,
                           xThetaMax);

  xThetaFirstSimplestNumber = alignLog.firstSimplestNumber();
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::periodicLinear() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::periodicLinear";

  if (m_xThetaValuesRaw.count () > 0) {

    double xThetaFirstSimplestNumber, xThetaMin, xThetaMax;
    firstSimplestNumberLinear (xThetaFirstSimplestNumber,
                               xThetaMin,
                               xThetaMax);

    // Assuming user picks an appropriate interval increment, numbering starting at xThetaFirstSimplestNumber
    // will give nice x/theta numbers
    if (m_modelExport.pointsIntervalUnitsFunctions() == EXPORT_POINTS_INTERVAL_UNITS_GRAPH) {
      return periodicLinearGraph(xThetaFirstSimplestNumber,
                                 xThetaMin,
                                 xThetaMax);
    } else {
      return periodicLinearScreen(xThetaMin,
                                  xThetaMax);
    }
  } else {

    ExportValuesXOrY emptyList;
    return emptyList;
  }
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::periodicLinearGraph(double xThetaFirstSimplestNumber,
                                                                        double xThetaMin,
                                                                        double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::periodicLinearGraph";

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
    values [xThetaMax] = true; // We passed maximum so insert point right at xThetaMax
  }

  return values.keys();
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::periodicLinearScreen (double xThetaMin,
                                                                          double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::periodicLinearScreen";

  const double ARBITRARY_Y = 0.0;

  // Screen coordinates of endpoints
  QPointF posScreenFirst, posScreenLast;
  m_transformation.transformRawGraphToScreen(QPointF (xThetaMin,
                                                      ARBITRARY_Y),
                                             posScreenFirst);
  m_transformation.transformRawGraphToScreen(QPointF (xThetaMax,
                                                      ARBITRARY_Y),
                                             posScreenLast);
  double deltaScreenX = posScreenLast.x() - posScreenFirst.x();
  double deltaScreenY = posScreenLast.y() - posScreenFirst.y();
  double deltaScreen = qSqrt (deltaScreenX * deltaScreenX + deltaScreenY * deltaScreenY);

  // Need calculations to find the scaling to be applied to successive points
  double s = 1.0;
  double interval = m_modelExport.pointsIntervalFunctions();
  if ((interval > 0) &&
      (interval < deltaScreen)) {
    s = interval / deltaScreen;
  }

  // Example: xThetaMin=0.1 and xThetaMax=100 (points are 0.1, 1, 10, 100) with s=1/3 so scale should be 10
  // which multiples 0.1 to get 1. This uses s=(log(xNext)-log(xMin))/(log(xMax)-log(xMin))
  double xNext = xThetaMin + s * (xThetaMax - xThetaMin);
  double delta = xNext - xThetaMin;

  ValuesVectorXOrY values;

  double xTheta = xThetaMin;
  while (xTheta <= xThetaMax) {

    values [xTheta] = true;

    xTheta += delta;
  }

  return values.keys();
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::periodicLog() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::periodicLog";

  double xThetaFirstSimplestNumber, xThetaMin, xThetaMax;
  firstSimplestNumberLog (xThetaFirstSimplestNumber,
                          xThetaMin,
                          xThetaMax);

  // Assuming user picks an appropriate interval increment, numbering starting at xThetaFirstSimplestNumber
  // will give nice x/theta numbers
  if (m_modelExport.pointsIntervalUnitsFunctions() == EXPORT_POINTS_INTERVAL_UNITS_GRAPH) {
    return periodicLogGraph(xThetaFirstSimplestNumber,
                            xThetaMin,
                            xThetaMax);
  } else {
    return periodicLogScreen(xThetaMin,
                             xThetaMax);
  }
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::periodicLogGraph (double xThetaFirstSimplestNumber,
                                                                      double xThetaMin,
                                                                      double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::periodicLogGraph";

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
    values [xThetaMax] = true; // We passed maximum so insert point right at xThetaMax
  }

  return values.keys();
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::periodicLogScreen (double xThetaMin,
                                                                       double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::periodicLogScreen";

  const double ARBITRARY_Y = 0.0;

  // Screen coordinates of endpoints
  QPointF posScreenFirst, posScreenLast;
  m_transformation.transformRawGraphToScreen(QPointF (xThetaMin,
                                                      ARBITRARY_Y),
                                             posScreenFirst);
  m_transformation.transformRawGraphToScreen(QPointF (xThetaMax,
                                                      ARBITRARY_Y),
                                             posScreenLast);
  double deltaScreenX = posScreenLast.x() - posScreenFirst.x();
  double deltaScreenY = posScreenLast.y() - posScreenFirst.y();
  double deltaScreen = qSqrt (deltaScreenX * deltaScreenX + deltaScreenY * deltaScreenY);

  // Need calculations to find the scaling to be applied to successive points
  double s = 1.0;
  double interval = m_modelExport.pointsIntervalFunctions();
  if ((interval > 0) &&
      (interval < deltaScreen)) {
    s = interval / deltaScreen;
  }

  // Example: xThetaMin=0.1 and xThetaMax=100 (points are 0.1, 1, 10, 100) with s=1/3 so scale should be 10
  // which multiples 0.1 to get 1. This uses s=(log(xNext)-log(xMin))/(log(xMax)-log(xMin))
  double xNext = qExp (qLn (xThetaMin) + s * (qLn (xThetaMax) - qLn (xThetaMin)));
  double scale = xNext / xThetaMin;

  ValuesVectorXOrY values;

  double xTheta = xThetaMin;
  while (xTheta <= xThetaMax) {

    values [xTheta] = true;

    xTheta *= scale;
  }

  return values.keys();
}

ExportValuesXOrY ExportXThetaValuesMergedFunctions::xThetaValues () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesMergedFunctions::xThetaValues";

  if (m_modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC) {

    // Special case that occurs when there are no points
    if (m_modelExport.pointsIntervalFunctions() == 0) {

      ExportValuesXOrY empty;
      return empty;

    } else {

      bool isLinear =  (m_transformation.modelCoords().coordScaleXTheta() == COORD_SCALE_LINEAR);
      if (isLinear) {
        return periodicLinear ();
      } else {
        return periodicLog ();
      }
    }
  } else {

    // Return the gathered values
    return m_xThetaValuesRaw.keys();

  }
}
