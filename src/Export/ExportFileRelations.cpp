/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveConnectAs.h"
#include "Document.h"
#include "DocumentModelGeneral.h"
#include "EngaugeAssert.h"
#include "ExportFileRelations.h"
#include "ExportLayoutFunctions.h"
#include "ExportOrdinalsSmooth.h"
#include "ExportOrdinalsStraight.h"
#include "FormatCoordsUnits.h"
#include "Logger.h"
#include <qdebug.h>
#include <qmath.h>
#include <QTextStream>
#include <QVector>
#include "Spline.h"
#include "SplinePair.h"
#include "Transformation.h"
#include <vector>

using namespace std;

const int COLUMNS_PER_CURVE = 2;

ExportFileRelations::ExportFileRelations()
{
}

void ExportFileRelations::exportAllPerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                                              const Document &document,
                                                              const MainWindowModel &modelMainWindow,
                                                              const QStringList &curvesIncluded,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              bool isLogXTheta,
                                                              bool isLogYRadius,
                                                              QTextStream &str,
                                                              unsigned int &numWritesSoFar) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportAllPerLineXThetaValuesMerged";

  int maxColumnSize = maxColumnSizeAllocation (modelExportOverride,
                                               document,
                                               transformation,
                                               isLogXTheta,
                                               isLogYRadius,
                                               curvesIncluded);

  // Skip if every curve was a function
  if (maxColumnSize > 0) {

    if (modelExportOverride.pointsSelectionRelations() == EXPORT_POINTS_SELECTION_RELATIONS_INTERPOLATE) {

      exportAllPerLineXThetaValuesMergedMultiplePass (maxColumnSize,
                                                      modelExportOverride,
                                                      document,
                                                      modelMainWindow,
                                                      curvesIncluded,
                                                      delimiter,
                                                      transformation,
                                                      isLogXTheta,
                                                      isLogYRadius,
                                                      str,
                                                      numWritesSoFar);

    } else {

      exportAllPerLineXThetaValuesMergedOnePass (maxColumnSize,
                                                 modelExportOverride,
                                                 document,
                                                 modelMainWindow,
                                                 curvesIncluded,
                                                 delimiter,
                                                 transformation,
                                                 isLogXTheta,
                                                 isLogYRadius,
                                                 str,
                                                 numWritesSoFar);
    }
  }
}

void ExportFileRelations::exportAllPerLineXThetaValuesMergedMultiplePass (int maxColumnSize,
                                                                          const DocumentModelExportFormat &modelExportOverride,
                                                                          const Document &document,
                                                                          const MainWindowModel &modelMainWindow,
                                                                          const QStringList &curvesIncluded,
                                                                          const QString &delimiter,
                                                                          const Transformation &transformation,
                                                                          bool isLogXTheta,
                                                                          bool isLogYRadius,
                                                                          QTextStream &str,
                                                                          unsigned int &numWritesSoFar) const
{
  // For interpolation of relations in general a single set of x/theta values cannot be created that work for every
  // relation curve, since one curve may have M y/radius values for a specific x/radius while another curve has
  // N y/radius values for that same x/radius value. So we export each curve into memory separately and then merge
  // the results. Why? Since the methods called from this method all assume a single set of x/theta values can be
  // used for all curves

  const int CURVE_COUNT_PER_PASS = 1;

  int curveCount = curvesIncluded.count ();

  QVector<QVector<QString*> > xThetaYRadiusValuesAll (COLUMNS_PER_CURVE * curveCount, QVector<QString*> (maxColumnSize));

  initializeXThetaYRadiusValues (curvesIncluded,
                                 xThetaYRadiusValuesAll);

  // One pass per curve
  int colX = 0, colY = colX + 1;
  for (int c = 0; c < curvesIncluded.count (); c++) {
    QString curve = curvesIncluded [c];

    QStringList curvesIncludedInPass;
    curvesIncludedInPass << curve;
    ENGAUGE_ASSERT (curvesIncludedInPass.count () == CURVE_COUNT_PER_PASS);

    QVector<QVector<QString*> > xThetaYRadiusValuesOne (COLUMNS_PER_CURVE * CURVE_COUNT_PER_PASS, QVector<QString*> (maxColumnSize));

    initializeXThetaYRadiusValues (curvesIncludedInPass,
                                   xThetaYRadiusValuesOne);
    loadXThetaYRadiusValues (modelExportOverride,
                             document,
                             modelMainWindow,
                             curvesIncludedInPass,
                             transformation,
                             isLogXTheta,
                             isLogYRadius,
                             xThetaYRadiusValuesOne);

    // Merge one curve array into all curves array
    for (int row = 0; row < maxColumnSize; row++) {
      *(xThetaYRadiusValuesAll [colX] [row]) = *(xThetaYRadiusValuesOne [0] [row]);
      *(xThetaYRadiusValuesAll [colY] [row]) = *(xThetaYRadiusValuesOne [1] [row]);
    }

    destroy2DArray (xThetaYRadiusValuesOne);

    colX += 2;
    colY += 2;
  }

  outputXThetaYRadiusValues (modelExportOverride,
                             curvesIncluded,
                             xThetaYRadiusValuesAll,
                             delimiter,
                             str,
                             numWritesSoFar);
  destroy2DArray (xThetaYRadiusValuesAll);
}

void ExportFileRelations::exportAllPerLineXThetaValuesMergedOnePass (int maxColumnSize,
                                                                     const DocumentModelExportFormat &modelExportOverride,
                                                                     const Document &document,
                                                                     const MainWindowModel &modelMainWindow,
                                                                     const QStringList &curvesIncluded,
                                                                     const QString &delimiter,
                                                                     const Transformation &transformation,
                                                                     bool isLogXTheta,
                                                                     bool isLogYRadius,
                                                                     QTextStream &str,
                                                                     unsigned int &numWritesSoFar) const
{
  int curveCount = curvesIncluded.count ();

  QVector<QVector<QString*> > xThetaYRadiusValues (COLUMNS_PER_CURVE * curveCount, QVector<QString*> (maxColumnSize));
  initializeXThetaYRadiusValues (curvesIncluded,
                                 xThetaYRadiusValues);
  loadXThetaYRadiusValues (modelExportOverride,
                           document,
                           modelMainWindow,
                           curvesIncluded,
                           transformation,
                           isLogXTheta,
                           isLogYRadius,
                           xThetaYRadiusValues);
  outputXThetaYRadiusValues (modelExportOverride,
                             curvesIncluded,
                             xThetaYRadiusValues,
                             delimiter,
                             str,
                             numWritesSoFar);
  destroy2DArray (xThetaYRadiusValues);
}

void ExportFileRelations::exportOnePerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                                              const Document &document,
                                                              const MainWindowModel &modelMainWindow,
                                                              const QStringList &curvesIncluded,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              bool isLogXTheta,
                                                              bool isLogYRadius,
                                                              QTextStream &str,
                                                              unsigned int &numWritesSoFar) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportOnePerLineXThetaValuesMerged";

  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;

    exportAllPerLineXThetaValuesMerged (modelExportOverride,
                                        document,
                                        modelMainWindow,
                                        QStringList (curveIncluded),
                                        delimiter,
                                        transformation,
                                        isLogXTheta,
                                        isLogYRadius,
                                        str,
                                        numWritesSoFar);
  }
}

void ExportFileRelations::exportToFile (const DocumentModelExportFormat &modelExportOverride,
                                        const Document &document,
                                        const MainWindowModel &modelMainWindow,
                                        const Transformation &transformation,
                                        QTextStream &str,
                                        unsigned int &numWritesSoFar) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportToFile";

  // Log coordinates must be temporarily transformed to linear coordinates
  bool isLogXTheta = (document.modelCoords().coordScaleXTheta() == COORD_SCALE_LOG);
  bool isLogYRadius = (document.modelCoords().coordScaleYRadius() == COORD_SCALE_LOG);

  // Identify curves to be included
  QStringList curvesIncluded = curvesToInclude (modelExportOverride,
                                                document,
                                                document.curvesGraphsNames(),
                                                CONNECT_AS_RELATION_SMOOTH,
                                                CONNECT_AS_RELATION_STRAIGHT);

  // Delimiter
  const QString delimiter = exportDelimiterToText (modelExportOverride.delimiter(),
                                                   modelExportOverride.header() == EXPORT_HEADER_GNUPLOT);

  // Export in one of two layouts
  if (modelExportOverride.layoutFunctions() == EXPORT_LAYOUT_ALL_PER_LINE) {
    exportAllPerLineXThetaValuesMerged (modelExportOverride,
                                        document,
                                        modelMainWindow,
                                        curvesIncluded,
                                        delimiter,
                                        transformation,
                                        isLogXTheta,
                                        isLogYRadius,
                                        str,
                                        numWritesSoFar);
  } else {
    exportOnePerLineXThetaValuesMerged (modelExportOverride,
                                        document,
                                        modelMainWindow,
                                        curvesIncluded,
                                        delimiter,
                                        transformation,
                                        isLogXTheta,
                                        isLogYRadius,
                                        str,
                                        numWritesSoFar);
  }
}

void ExportFileRelations::initializeXThetaYRadiusValues (const QStringList &curvesIncluded,
                                                         QVector<QVector<QString*> > &xThetaYRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::initializeXThetaYRadiusValues";

  // Initialize every entry with empty string
  int curveCount = curvesIncluded.count();
  int xThetaCount = xThetaYRadiusValues [0].count();
  for (int row = 0; row < xThetaCount; row++) {
    for (int col = 0; col < COLUMNS_PER_CURVE * curveCount; col++) {
      xThetaYRadiusValues [col] [row] = new QString;
    }
  }
}

QPointF ExportFileRelations::linearlyInterpolate (const Points &points,
                                                  double ordinal,
                                                  const Transformation &transformation) const
{
  //  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::linearlyInterpolate";

  double xTheta = 0, yRadius = 0;
  double ordinalBefore = 0; // Not set until ip=1
  QPointF posGraphBefore; // Not set until ip=1
  bool foundIt = false;
  for (int ip = 0; ip < points.count(); ip++) {

    const Point &point = points.at (ip);
    QPointF posGraph;
    transformation.transformScreenToRawGraph (point.posScreen(),
                                              posGraph);

    if (ordinal <= point.ordinal()) {

      foundIt = true;
      if (ip == 0) {

        // Use first point
        xTheta = posGraph.x();
        yRadius = posGraph.y();

      } else {

        // Between posGraphBefore and posGraph. Note that if posGraph.x()=posGraphBefore.x() then
        // previous iteration of loop would have been used for interpolation, and then the loop was exited
        double s = (ordinal - ordinalBefore) / (point.ordinal() - ordinalBefore);
        xTheta =  (1.0 - s) * posGraphBefore.x() + s * posGraph.x();
        yRadius = (1.0 - s) * posGraphBefore.y() + s * posGraph.y();
      }

      break;
    }

    ordinalBefore = point.ordinal();
    posGraphBefore = posGraph;
  }

  if (!foundIt) {

    // Use last point
    xTheta = posGraphBefore.x();
    yRadius = posGraphBefore.y();

  }

  return QPointF (xTheta,
                  yRadius);
}

void ExportFileRelations::loadXThetaYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                                                   const Document &document,
                                                   const MainWindowModel &modelMainWindow,
                                                   const QStringList &curvesIncluded,
                                                   const Transformation &transformation,
                                                   bool isLogXTheta,
                                                   bool isLogYRadius,
                                                   QVector<QVector<QString*> > &xThetaYRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValues";

  // The curve processing logic here is mirrored in maxColumnSizeAllocation so the array allocations are in sync
  for (int ic = 0; ic < curvesIncluded.count(); ic++) {

    int colXTheta = 2 * ic;
    int colYRadius = 2 * ic + 1;

    const QString curveName = curvesIncluded.at (ic);

    const Curve *curve = document.curveForCurveName (curveName);
    const Points points = curve->points ();

    if (modelExportOverride.pointsSelectionRelations() == EXPORT_POINTS_SELECTION_RELATIONS_RAW) {

      // No interpolation. Raw points
      loadXThetaYRadiusValuesForCurveRaw (document.modelCoords(),
                                          document.modelGeneral(),
                                          modelMainWindow,
                                          points,
                                          xThetaYRadiusValues [colXTheta],
                                          xThetaYRadiusValues [colYRadius],
                                          transformation);
    } else {

      const LineStyle &lineStyle = document.modelCurveStyles().lineStyle(curveName);

      // Interpolation. Points are taken approximately every every modelExport.pointsIntervalRelations
      ExportValuesOrdinal ordinals = ordinalsAtIntervals (modelExportOverride.pointsIntervalRelations(),
                                                          modelExportOverride.pointsIntervalUnitsRelations(),
                                                          lineStyle.curveConnectAs(),
                                                          transformation,
                                                          isLogXTheta,
                                                          isLogYRadius,
                                                          points);

      if (curve->curveStyle().lineStyle().curveConnectAs() == CONNECT_AS_RELATION_SMOOTH) {

        loadXThetaYRadiusValuesForCurveInterpolatedSmooth (document.modelCoords(),
                                                           document.modelGeneral(),
                                                           modelMainWindow,
                                                           points,
                                                           ordinals,
                                                           xThetaYRadiusValues [colXTheta],
                                                           xThetaYRadiusValues [colYRadius],
                                                           transformation,
                                                           isLogXTheta,
                                                           isLogYRadius);

      } else {

        loadXThetaYRadiusValuesForCurveInterpolatedStraight (document.modelCoords(),
                                                             document.modelGeneral(),
                                                             modelMainWindow,
                                                             points,
                                                             ordinals,
                                                             xThetaYRadiusValues [colXTheta],
                                                             xThetaYRadiusValues [colYRadius],
                                                             transformation);
      }
    }
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth (const DocumentModelCoords &modelCoords,
                                                                             const DocumentModelGeneral &modelGeneral,
                                                                             const MainWindowModel &modelMainWindow,
                                                                             const Points &points,
                                                                             const ExportValuesOrdinal &ordinals,
                                                                             QVector<QString*> &xThetaValues,
                                                                             QVector<QString*> &yRadiusValues,
                                                                             const Transformation &transformation,
                                                                             bool isLogXTheta,
                                                                             bool isLogYRadius) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth";

  vector<double> t;
  vector<SplinePair> xy;
  ExportOrdinalsSmooth ordinalsSmooth;

  ordinalsSmooth.loadSplinePairsWithTransformation (points,
                                                    transformation,
                                                    isLogXTheta,
                                                    isLogYRadius,
                                                    t,
                                                    xy);

  // Spline class requires at least one point
  if (xy.size() > 0) {

    // Fit a spline
    Spline spline (t,
                   xy);

    FormatCoordsUnits format;

    // Extract the points
    for (int row = 0; row < ordinals.count(); row++) {

      double ordinal = ordinals.at (row);
      SplinePair splinePairFound = spline.interpolateCoeff(ordinal);
      double xTheta = splinePairFound.x ();
      double yRadius = splinePairFound.y ();

      // Save values for this row into xThetaValues and yRadiusValues, after appropriate formatting
      format.unformattedToFormatted (xTheta,
                                     yRadius,
                                     modelCoords,
                                     modelGeneral,
                                     modelMainWindow,
                                     *(xThetaValues [row]),
                                     *(yRadiusValues [row]),
                                     transformation);
    }
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight (const DocumentModelCoords &modelCoords,
                                                                               const DocumentModelGeneral &modelGeneral,
                                                                               const MainWindowModel &modelMainWindow,
                                                                               const Points &points,
                                                                               const ExportValuesOrdinal &ordinals,
                                                                               QVector<QString*> &xThetaValues,
                                                                               QVector<QString*> &yRadiusValues,
                                                                               const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight";

  FormatCoordsUnits format;

  // Get value at desired points
  for (int row = 0; row < ordinals.count(); row++) {

    double ordinal = ordinals.at (row);

    QPointF pointInterpolated = linearlyInterpolate (points,
                                                     ordinal,
                                                     transformation);

    // Save values for this row into xThetaValues and yRadiusValues, after appropriate formatting
    format.unformattedToFormatted (pointInterpolated.x(),
                                   pointInterpolated.y(),
                                   modelCoords,
                                   modelGeneral,
                                   modelMainWindow,
                                   *(xThetaValues [row]),
                                   *(yRadiusValues [row]),
                                   transformation);
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveRaw (const DocumentModelCoords &modelCoords,
                                                              const DocumentModelGeneral &modelGeneral,
                                                              const MainWindowModel &modelMainWindow,
                                                              const Points &points,
                                                              QVector<QString*> &xThetaValues,
                                                              QVector<QString*> &yRadiusValues,
                                                              const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveRaw";

  FormatCoordsUnits format;

  for (int pt = 0; pt < points.count(); pt++) {

    const Point &point = points.at (pt);

    QPointF posGraph;
    transformation.transformScreenToRawGraph (point.posScreen(),
                                              posGraph);

    // Save values for this row into xThetaValues and yRadiusValues, after appropriate formatting
    format.unformattedToFormatted (posGraph.x(),
                                   posGraph.y(),
                                   modelCoords,
                                   modelGeneral,
                                   modelMainWindow,
                                   *(xThetaValues [pt]),
                                   *(yRadiusValues [pt]),
                                   transformation);
  }
}

int ExportFileRelations::maxColumnSizeAllocation (const DocumentModelExportFormat &modelExport,
                                                  const Document &document,
                                                  const Transformation &transformation,
                                                  bool isLogXTheta,
                                                  bool isLogYRadius,
                                                  const QStringList &curvesIncluded) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::maxColumnSizeAllocation";

  int maxColumnSize = 0;

  // The curve processing logic here is mirrored in loadXThetaYRadiusValues so the array allocations are in sync
  for (int ic = 0; ic < curvesIncluded.count(); ic++) {

    const QString curveName = curvesIncluded.at (ic);

    const Curve *curve = document.curveForCurveName (curveName);
    const Points points = curve->points ();

    if (modelExport.pointsSelectionRelations() == EXPORT_POINTS_SELECTION_RELATIONS_RAW) {

      // No interpolation. Raw points
      maxColumnSize = qMax (maxColumnSize,
                            points.count());

    } else {

      const LineStyle &lineStyle = document.modelCurveStyles().lineStyle(curveName);


      // Interpolation. Points are taken approximately every every modelExport.pointsIntervalRelations
      ExportValuesOrdinal ordinals = ordinalsAtIntervals (modelExport.pointsIntervalRelations(),
                                                          modelExport.pointsIntervalUnitsRelations(),
                                                          lineStyle.curveConnectAs(),
                                                          transformation,
                                                          isLogXTheta,
                                                          isLogYRadius,
                                                          points);

      maxColumnSize = qMax (maxColumnSize,
                            ordinals.count());
    }
  }

  return maxColumnSize;
}

ExportValuesOrdinal ExportFileRelations::ordinalsAtIntervals (double pointsIntervalRelations,
                                                              ExportPointsIntervalUnits pointsIntervalUnits,
                                                              CurveConnectAs curveConnectAs,
                                                              const Transformation &transformation,
                                                              bool isLogXTheta,
                                                              bool isLogYRadius,
                                                              const Points &points) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::ordinalsAtIntervals";

  if (pointsIntervalUnits == EXPORT_POINTS_INTERVAL_UNITS_GRAPH) {
    if (curveConnectAs == CONNECT_AS_RELATION_SMOOTH) {

      return ordinalsAtIntervalsSmoothGraph (pointsIntervalRelations,
                                             transformation,
                                             isLogXTheta,
                                             isLogYRadius,
                                             points);

    } else {

      return ordinalsAtIntervalsStraightGraph (pointsIntervalRelations,
                                               transformation,
                                               points);

    }
  } else {

    if (curveConnectAs == CONNECT_AS_RELATION_SMOOTH) {

      return ordinalsAtIntervalsSmoothScreen (pointsIntervalRelations,
                                              points);

    } else {

      return ordinalsAtIntervalsStraightScreen (pointsIntervalRelations,
                                                points);

    }
  }
}

ExportValuesOrdinal ExportFileRelations::ordinalsAtIntervalsSmoothGraph (double pointsIntervalRelations,
                                                                         const Transformation &transformation,
                                                                         bool isLogXTheta,
                                                                         bool isLogYRadius,
                                                                         const Points &points) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::ordinalsAtIntervalsSmoothGraph";

  ExportValuesOrdinal ordinals;

  // Prevent infinite loop when there are no points or will be too many points
  if ((pointsIntervalRelations > 0) &&
      (points.count() > 0)) {

    vector<double> t;
    vector<SplinePair> xy;
    ExportOrdinalsSmooth ordinalsSmooth;

    ordinalsSmooth.loadSplinePairsWithTransformation (points,
                                                      transformation,
                                                      isLogXTheta,
                                                      isLogYRadius,
                                                      t,
                                                      xy);

    ordinals = ordinalsSmooth.ordinalsAtIntervalsGraph (t,
                                                        xy,
                                                        pointsIntervalRelations);
  }

  return ordinals;
}

ExportValuesOrdinal ExportFileRelations::ordinalsAtIntervalsSmoothScreen (double pointsIntervalRelations,
                                                                          const Points &points) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::ordinalsAtIntervalsSmoothScreen"
                              << " pointCount=" << points.count();

  // Results
  ExportValuesOrdinal ordinals;

  // Prevent infinite loop when there are no points or will be too many points
  if ((pointsIntervalRelations > 0) &&
      (points.count() > 0)) {

    vector<double> t;
    vector<SplinePair> xy;
    ExportOrdinalsSmooth ordinalsSmooth;

    ordinalsSmooth.loadSplinePairsWithoutTransformation (points,
                                                         t,
                                                         xy);

    ordinals = ordinalsSmooth.ordinalsAtIntervalsGraph (t,
                                                        xy,
                                                        pointsIntervalRelations);
  }

  return ordinals;
}

ExportValuesOrdinal ExportFileRelations::ordinalsAtIntervalsStraightGraph (double pointsIntervalRelations,
                                                                           const Transformation &transformation,
                                                                           const Points &points) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::ordinalsAtIntervalsStraightGraph";

  ExportValuesOrdinal ordinals;

  // Prevent infinite loop when there are no points or will be too many points
  if ((pointsIntervalRelations > 0) &&
      (points.count() > 0)) {

    ExportOrdinalsStraight ordinalsStraight;

    ordinals = ordinalsStraight.ordinalsAtIntervalsGraphWithTransformation (points,
                                                                            transformation,
                                                                            pointsIntervalRelations);
  }

  return ordinals;
}

ExportValuesOrdinal ExportFileRelations::ordinalsAtIntervalsStraightScreen (double pointsIntervalRelations,
                                                                            const Points &points) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::ordinalsAtIntervalsStraightScreen"
                              << " pointCount=" << points.count();

  // Results
  ExportValuesOrdinal ordinals;

  // Prevent infinite loop when there are no points or will be too many points
  if ((pointsIntervalRelations > 0) &&
      (points.count() > 0)) {

    ExportOrdinalsStraight ordinalsStraight;

    ordinals = ordinalsStraight.ordinalsAtIntervalsGraphWithoutTransformation (points,
                                                                               pointsIntervalRelations);
  }

  return ordinals;
}

void ExportFileRelations::outputXThetaYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                                                     const QStringList &curvesIncluded,
                                                     QVector<QVector<QString*> > &xThetaYRadiusValues,
                                                     const QString &delimiter,
                                                     QTextStream &str,
                                                     unsigned int &numWritesSoFar) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::outputXThetaYRadiusValues";

  // Header
  if (modelExportOverride.header() != EXPORT_HEADER_NONE) {
    insertLineSeparator (numWritesSoFar == 0,
                         modelExportOverride.header (),
                         str);
    if (modelExportOverride.header() == EXPORT_HEADER_GNUPLOT) {
      str << gnuplotComment();
    }
    QString delimiterForRow;
    QStringList::const_iterator itr;
    for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {
      QString curveName = *itr;
      str << delimiterForRow << modelExportOverride.xLabel();
      delimiterForRow = delimiter;
      str << delimiterForRow << curveName;
    }
    str << "\n";
  }

  for (int row = 0; row < xThetaYRadiusValues [0].count(); row++) {

    QString delimiterForRow;
    for (int col = 0; col < xThetaYRadiusValues.count(); col++) {

      str << delimiterForRow << *(xThetaYRadiusValues [col] [row]);
      delimiterForRow = delimiter;
    }

    str << "\n";
  }

  ++numWritesSoFar;
}
