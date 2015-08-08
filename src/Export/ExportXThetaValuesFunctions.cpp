#include "ExportXThetaValuesFunctions.h"
#include "ExportAlignLinear.h"
#include "ExportAlignLog.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "Logger.h"
#include "Point.h"
#include "Transformation.h"

ExportXThetaValuesFunctions::ExportXThetaValuesFunctions(const DocumentModelExport &modelExport,
                                                         const ValuesVectorXOrY &xThetaValuesRaw,
                                                         const Transformation &transformation) :
  m_modelExport (modelExport),
  m_xThetaValuesRaw (xThetaValuesRaw),
  m_isLinear (transformation.modelCoords().coordScaleXTheta() == COORD_SCALE_LINEAR)
{
}

void ExportXThetaValuesFunctions::firstSimplestNumberLinear (double &xThetaFirstSimplestNumber,
                                                             double &xThetaMin,
                                                             double &xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::firstSimplestNumberLinear";

  // X/theta range
  xThetaMin = m_xThetaValuesRaw.firstKey();
  xThetaMax = m_xThetaValuesRaw.lastKey();

  // Compute offset that gives the simplest numbers
  ExportAlignLinear alignLinear (xThetaMin,
                                 xThetaMax);

  xThetaFirstSimplestNumber = alignLinear.firstSimplestNumber();
}

void ExportXThetaValuesFunctions::firstSimplestNumberLog (double &xThetaFirstSimplestNumber,
                                                          double &xThetaMin,
                                                          double &xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::firstSimplestNumberLog";

  // X/theta range
  xThetaMin = m_xThetaValuesRaw.firstKey();
  xThetaMax = m_xThetaValuesRaw.lastKey();

  // Compute offset that gives the simplest numbers
  ExportAlignLog alignLog (xThetaMin,
                           xThetaMax);

  xThetaFirstSimplestNumber = alignLog.firstSimplestNumber();
}

ExportValuesXOrY ExportXThetaValuesFunctions::periodicLinear() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::periodicLinear";

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
    return periodicLinearScreen(xThetaFirstSimplestNumber,
                                xThetaMin,
                                xThetaMax);
  }
}

ExportValuesXOrY ExportXThetaValuesFunctions::periodicLinearGraph(double xThetaFirstSimplestNumber,
                                                                  double xThetaMin,
                                                                  double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::periodicLinearGraph";

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

ExportValuesXOrY ExportXThetaValuesFunctions::periodicLinearScreen (double xThetaFirstSimplestNumber,
                                                                               double xThetaMin,
                                                                               double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::periodicLinearScreen";

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

ExportValuesXOrY ExportXThetaValuesFunctions::periodicLog() const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::periodicLog";

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
    return periodicLogScreen(xThetaFirstSimplestNumber,
                             xThetaMin,
                             xThetaMax);
  }
}

ExportValuesXOrY ExportXThetaValuesFunctions::periodicLogGraph (double xThetaFirstSimplestNumber,
                                                                double xThetaMin,
                                                                double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::periodicLogGraph";

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

ExportValuesXOrY ExportXThetaValuesFunctions::periodicLogScreen (double xThetaFirstSimplestNumber,
                                                                 double xThetaMin,
                                                                 double xThetaMax) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::periodicLogScreen";

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

ExportValuesXOrY ExportXThetaValuesFunctions::xThetaValues () const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportXThetaValuesFunctions::xThetaValues";

  if (m_modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_PERIODIC) {

    if (m_isLinear) {
      return periodicLinear ();
    } else {
      return periodicLog ();
    }

  } else {

    // Return the gathered values
    return m_xThetaValuesRaw.keys();

  }
}
