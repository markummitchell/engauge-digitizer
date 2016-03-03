/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CallbackGatherXThetaValuesFunctions.h"
#include "CurveConnectAs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportFileFunctions.h"
#include "ExportLayoutFunctions.h"
#include "ExportOrdinalsSmooth.h"
#include "ExportXThetaValuesMergedFunctions.h"
#include "FormatCoordsUnits.h"
#include "Logger.h"
#include <QTextStream>
#include <QVector>
#include "Spline.h"
#include "SplinePair.h"
#include "Transformation.h"
#include <vector>

using namespace std;

ExportFileFunctions::ExportFileFunctions()
{
}

void ExportFileFunctions::exportAllPerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                                              const Document &document,
                                                              const MainWindowModel &modelMainWindow,
                                                              const QStringList &curvesIncluded,
                                                              const ExportValuesXOrY &xThetaValues,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::exportAllPerLineXThetaValuesMerged";

  int curveCount = curvesIncluded.count();
  int xThetaCount = xThetaValues.count();
  QVector<QVector<QString*> > yRadiusValues (curveCount, QVector<QString*> (xThetaCount));
  initializeYRadiusValues (curvesIncluded,
                           xThetaValues,
                           yRadiusValues);
  loadYRadiusValues (modelExportOverride,
                     document,
                     modelMainWindow,
                     curvesIncluded,
                     transformation,
                     xThetaValues,
                     yRadiusValues);

  outputXThetaYRadiusValues (modelExportOverride,
                             document.modelCoords(),
                             modelMainWindow,
                             curvesIncluded,
                             xThetaValues,
                             transformation,
                             yRadiusValues,
                             delimiter,
                             str);
  destroy2DArray (yRadiusValues);
}

void ExportFileFunctions::exportOnePerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                                              const Document &document,
                                                              const MainWindowModel &modelMainWindow,
                                                              const QStringList &curvesIncluded,
                                                              const ExportValuesXOrY &xThetaValues,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::exportOnePerLineXThetaValuesMerged";

  bool isFirst = true;

  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    insertLineSeparator (isFirst,
                         modelExportOverride.header(),
                         str);

    // This curve
    const int CURVE_COUNT = 1;
    QString curveIncluded = *itr;
    QStringList curvesIncluded (curveIncluded);

    int xThetaCount = xThetaValues.count();
    QVector<QVector<QString*> > yRadiusValues (CURVE_COUNT, QVector<QString*> (xThetaCount));
    initializeYRadiusValues (curvesIncluded,
                             xThetaValues,
                             yRadiusValues);
    loadYRadiusValues (modelExportOverride,
                       document,
                       modelMainWindow,
                       curvesIncluded,
                       transformation,
                       xThetaValues,
                       yRadiusValues);
    outputXThetaYRadiusValues (modelExportOverride,
                               document.modelCoords(),
                               modelMainWindow,
                               curvesIncluded,
                               xThetaValues,
                               transformation,
                               yRadiusValues,
                               delimiter,
                               str);
    destroy2DArray (yRadiusValues);
  }
}

void ExportFileFunctions::exportToFile (const DocumentModelExportFormat &modelExportOverride,
                                        const Document &document,
                                        const MainWindowModel &modelMainWindow,
                                        const Transformation &transformation,
                                        QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::exportToFile";

  // Identify curves to be included
  QStringList curvesIncluded = curvesToInclude (modelExportOverride,
                                                document,
                                                document.curvesGraphsNames(),
                                                CONNECT_AS_FUNCTION_SMOOTH,
                                                CONNECT_AS_FUNCTION_STRAIGHT);

  // Delimiter
  const QString delimiter = exportDelimiterToText (modelExportOverride.delimiter());

  // Get x/theta values to be used
  CallbackGatherXThetaValuesFunctions ftor (modelExportOverride,
                                            curvesIncluded,
                                            transformation);
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackGatherXThetaValuesFunctions::callback);
  document.iterateThroughCurvesPointsGraphs(ftorWithCallback);

  ExportXThetaValuesMergedFunctions exportXTheta (modelExportOverride,
                                                  ftor.xThetaValuesRaw(),
                                                  transformation);
  ExportValuesXOrY xThetaValuesMerged = exportXTheta.xThetaValues ();

  // Skip if every curve was a relation
  if (xThetaValuesMerged.count() > 0) {

    // Export in one of two layouts
    if (modelExportOverride.layoutFunctions() == EXPORT_LAYOUT_ALL_PER_LINE) {
      exportAllPerLineXThetaValuesMerged (modelExportOverride,
                                          document,
                                          modelMainWindow,
                                          curvesIncluded,
                                          xThetaValuesMerged,
                                          delimiter,
                                          transformation,
                                          str);
    } else {
      exportOnePerLineXThetaValuesMerged (modelExportOverride,
                                          document,
                                          modelMainWindow,
                                          curvesIncluded,
                                          xThetaValuesMerged,
                                          delimiter,
                                          transformation,
                                          str);
    }
  }
}

void ExportFileFunctions::initializeYRadiusValues (const QStringList &curvesIncluded,
                                                   const ExportValuesXOrY &xThetaValuesMerged,
                                                   QVector<QVector<QString*> > &yRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::initializeYRadiusValues";

  // Initialize every entry with empty string
  int curveCount = curvesIncluded.count();
  int xThetaCount = xThetaValuesMerged.count();
  for (int row = 0; row < xThetaCount; row++) {
    for (int col = 0; col < curveCount; col++) {
      yRadiusValues [col] [row] = new QString;
    }
  }
}

double ExportFileFunctions::linearlyInterpolate (const Points &points,
                                                 double xThetaValue,
                                                 const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::linearlyInterpolate";

  double yRadius = 0;
  QPointF posGraphBefore; // Not set until ip=1
  bool foundIt = false;
  for (int ip = 0; ip < points.count(); ip++) {

    const Point &point = points.at (ip);
    QPointF posGraph;
    transformation.transformScreenToRawGraph (point.posScreen(),
                                                posGraph);

    if (xThetaValue <= posGraph.x()) {

      foundIt = true;
      if (ip == 0) {

        // Use first point
        yRadius = posGraph.y();

      } else {

        // Between posGraphBefore and posGraph. Note that if posGraph.x()=posGraphBefore.x() then
        // previous iteration of loop would have been used for interpolation, and then the loop was exited
        double s = (xThetaValue - posGraphBefore.x()) / (posGraph.x() - posGraphBefore.x());
        yRadius = (1.0 -s) * posGraphBefore.y() + s * posGraph.y();
      }

      break;
    }

    posGraphBefore = posGraph;
  }

  if (!foundIt) {

    // Use last point
    yRadius = posGraphBefore.y();

  }

  return yRadius;
}

void ExportFileFunctions::loadYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                                             const Document &document,
                                             const MainWindowModel &modelMainWindow,
                                             const QStringList &curvesIncluded,
                                             const Transformation &transformation,
                                             const ExportValuesXOrY &xThetaValues,
                                             QVector<QVector<QString*> > &yRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::loadYRadiusValues";

  // Loop through curves
  int curveCount = curvesIncluded.count();
  for (int col = 0; col < curveCount; col++) {

    const QString curveName = curvesIncluded.at (col);

    const Curve *curve = document.curveForCurveName (curveName);
    const Points points = curve->points ();

    if (modelExportOverride.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_RAW) {

      // No interpolation. Raw points
      loadYRadiusValuesForCurveRaw (document.modelCoords(),
                                    modelMainWindow,
                                    points,
                                    xThetaValues,
                                    transformation,
                                    yRadiusValues [col]);
    } else {

      // Interpolation
      if (curve->curveStyle().lineStyle().curveConnectAs() == CONNECT_AS_FUNCTION_SMOOTH) {

        loadYRadiusValuesForCurveInterpolatedSmooth (document.modelCoords(),
                                                     modelMainWindow,
                                                     points,
                                                     xThetaValues,
                                                     transformation,
                                                     yRadiusValues [col]);

      } else {

        loadYRadiusValuesForCurveInterpolatedStraight (document.modelCoords(),
                                                       modelMainWindow,
                                                       points,
                                                       xThetaValues,
                                                       transformation,
                                                       yRadiusValues [col]);
      }
    }
  }
}

void ExportFileFunctions::loadYRadiusValuesForCurveInterpolatedSmooth (const DocumentModelCoords &modelCoords,
                                                                       const MainWindowModel &modelMainWindow,
                                                                       const Points &points,
                                                                       const ExportValuesXOrY &xThetaValues,
                                                                       const Transformation &transformation,
                                                                       QVector<QString*> &yRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::loadYRadiusValuesForCurveInterpolatedSmooth";

  // Convert screen coordinates to graph coordinates, in vectors suitable for spline fitting
  vector<double> t;
  vector<SplinePair> xy;
  ExportOrdinalsSmooth ordinalsSmooth;

  ordinalsSmooth.loadSplinePairsWithTransformation (points,
                                                    transformation,
                                                    t,
                                                    xy);

  // Formatting
  FormatCoordsUnits format;
  QString dummyXThetaOut;

  if (points.count() == 0) {

    // Since there are no values, leave the field empty
    for (int row = 0; row < xThetaValues.count(); row++) {
      *(yRadiusValues [row]) = "";
    }

  } else if (points.count() == 1 ||
             points.count() == 2) {

    // Apply the single value everywhere (N=1) or do linear interpolation (N=2)
    for (int row = 0; row < xThetaValues.count(); row++) {

      double xTheta = xThetaValues.at (row);
      double yRadius;
      if (points.count() == 1) {
        yRadius = xy.at (0).y ();
      } else {
        double x0 = xy.at (0).x ();
        double x1 = xy.at (1).x ();
        double y0 = xy.at (0).y ();
        double y1 = xy.at (1).y ();
        if (x0 == x1) {
          // Cannot do linear interpolation using two points at the same x value
          yRadius = xy.at (0).y ();
        } else {
          double s = (xTheta - x0) / (x1 - x0);
          yRadius = (1.0 - s) * y0 + s * y1;
        }
      }
      format.unformattedToFormatted (xTheta,
                                     yRadius,
                                     modelCoords,
                                     modelMainWindow,
                                     dummyXThetaOut,
                                     *(yRadiusValues [row]),
                                     transformation);
    }

  } else {

    // Iteration accuracy versus number of iterations 8->256, 10->1024, 12->4096. Single pixel accuracy out of
    // typical image size of 1024x1024 means around 10 iterations gives decent accuracy for numbers much bigger
    // than 1. A value of 12 gave some differences in the least significant figures of numbers like 10^-3 in
    // the regression tests. Toggling between 30 and 32 made no difference in the regression tests.
    const int MAX_ITERATIONS = 32;

    // Fit a spline
    Spline spline (t,
                   xy);

    // Get value at desired points
    for (int row = 0; row < xThetaValues.count(); row++) {

      double xTheta = xThetaValues.at (row);
      SplinePair splinePairFound = spline.findSplinePairForFunctionX (xTheta,
                                                                      MAX_ITERATIONS);
      double yRadius = splinePairFound.y ();

      // Save y/radius value for this row into yRadiusValues, after appropriate formatting
      QString dummyXThetaOut;
      format.unformattedToFormatted (xTheta,
                                     yRadius,
                                     modelCoords,
                                     modelMainWindow,
                                     dummyXThetaOut,
                                     *(yRadiusValues [row]),
                                     transformation);
    }
  }
}

void ExportFileFunctions::loadYRadiusValuesForCurveInterpolatedStraight (const DocumentModelCoords &modelCoords,
                                                                         const MainWindowModel &modelMainWindow,
                                                                         const Points &points,
                                                                         const ExportValuesXOrY &xThetaValues,
                                                                         const Transformation &transformation,
                                                                         QVector<QString*> &yRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::loadYRadiusValuesForCurveInterpolatedStraight";

  FormatCoordsUnits format;

  // Get value at desired points
  for (int row = 0; row < xThetaValues.count(); row++) {

    double xThetaValue = xThetaValues.at (row);

    double yRadius = linearlyInterpolate (points,
                                          xThetaValue,
                                          transformation);

    // Save y/radius value for this row into yRadiusValues, after appropriate formatting
    QString dummyXThetaOut;
    format.unformattedToFormatted (xThetaValue,
                                   yRadius,
                                   modelCoords,
                                   modelMainWindow,
                                   dummyXThetaOut,
                                   *(yRadiusValues [row]),
                                   transformation);
  }
}

void ExportFileFunctions::loadYRadiusValuesForCurveRaw (const DocumentModelCoords &modelCoords,
                                                        const MainWindowModel &modelMainWindow,
                                                        const Points &points,
                                                        const ExportValuesXOrY &xThetaValues,
                                                        const Transformation &transformation,
                                                        QVector<QString*> &yRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::loadYRadiusValuesForCurveRaw";

  FormatCoordsUnits format;

  // Since the curve points may be a subset of xThetaValues (in which case the non-applicable xThetaValues will have
  // blanks for the yRadiusValues), we iterate over the smaller set
  for (int pt = 0; pt < points.count(); pt++) {

    const Point &point = points.at (pt);

    QPointF posGraph;
    transformation.transformScreenToRawGraph (point.posScreen(),
                                              posGraph);

    // Find the closest point in xThetaValues. This is probably an N-squared algorithm, which is less than optimial,
    // but the delay should be insignificant with normal-sized export files
    double closestSeparation = 0.0;
    int rowClosest = 0;
    for (int row = 0; row < xThetaValues.count(); row++) {

      double xThetaValue = xThetaValues.at (row);

      double separation = qAbs (posGraph.x() - xThetaValue);

      if ((row == 0) ||
          (separation < closestSeparation)) {

        closestSeparation = separation;
        rowClosest = row;

      }
    }

    // Save y/radius value for this row into yRadiusValues, after appropriate formatting
    QString dummyXThetaOut;
    format.unformattedToFormatted (posGraph.x(),
                                   posGraph.y(),
                                   modelCoords,
                                   modelMainWindow,
                                   dummyXThetaOut,
                                   *(yRadiusValues [rowClosest]),
                                   transformation);
  }
}

void ExportFileFunctions::outputXThetaYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                                                     const DocumentModelCoords &modelCoords,
                                                     const MainWindowModel &modelMainWindow,
                                                     const QStringList &curvesIncluded,
                                                     const ExportValuesXOrY &xThetaValuesMerged,
                                                     const Transformation &transformation,
                                                     QVector<QVector<QString*> > &yRadiusValues,
                                                     const QString &delimiter,
                                                     QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::outputXThetaYRadiusValues";

  // Header
  if (modelExportOverride.header() != EXPORT_HEADER_NONE) {
    if (modelExportOverride.header() == EXPORT_HEADER_GNUPLOT) {
      str << curveSeparator (str.string());
      str << gnuplotComment();
    }
    str << modelExportOverride.xLabel();
    QStringList::const_iterator itrHeader;
    for (itrHeader = curvesIncluded.begin(); itrHeader != curvesIncluded.end(); itrHeader++) {
      QString curveName = *itrHeader;
      str << delimiter << curveName;
    }
    str << "\n";
  }

  FormatCoordsUnits format;
  const double DUMMY_Y_RADIUS = 1.0;

  for (int row = 0; row < xThetaValuesMerged.count(); row++) {

    if (rowHasAtLeastOneYRadiusEntry (yRadiusValues,
                                      row)) {

      double xTheta = xThetaValuesMerged.at (row);

      // Output x/theta value for this row
      QString xThetaString, yRadiusString;
      format.unformattedToFormatted (xTheta,
                                     DUMMY_Y_RADIUS,
                                     modelCoords,
                                     modelMainWindow,
                                     xThetaString,
                                     yRadiusString,
                                     transformation);
      str << xThetaString;

      for (int col = 0; col < yRadiusValues.count(); col++) {

        str << delimiter << *(yRadiusValues [col] [row]);
      }

      str << "\n";
    }
  }
}

bool ExportFileFunctions::rowHasAtLeastOneYRadiusEntry (const QVector<QVector<QString*> > &yRadiusValues,
                                                        int row) const
{
  bool hasEntry = false;

  for (int col = 0; col < yRadiusValues.count(); col++) {

    QString entry = *(yRadiusValues [col] [row]);
    if (!entry.isEmpty()) {

      hasEntry = true;
      break;

    }
  }

  return hasEntry;
}
