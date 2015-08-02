#include "CallbackGatherXThetaValuesRelations.h"
#include "CurveConnectAs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportFileRelations.h"
#include "ExportLayoutFunctions.h"
#include "Logger.h"
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

void ExportFileRelations::exportAllPerLineXThetaValuesMerged (const DocumentModelExport &modelExportOverride,
                                                              const Document &document,
                                                              const QStringList &curvesIncluded,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportAllPerLineXThetaValuesMerged";

  int curveCount = curvesIncluded.count();
  int maxColumnSize = maxColumnSizeAllocation (modelExportOverride,
                                               document,
                                               curvesIncluded);

  // Skip if every curve was a function
  if (maxColumnSize > 0) {

    QVector<QVector<QString*> > xThetaYRadiusValues (COLUMNS_PER_CURVE * curveCount, QVector<QString*> (maxColumnSize));
    initializeXThetaYRadiusValues (curvesIncluded,
                                   xThetaYRadiusValues);
    loadXThetaYRadiusValues (modelExportOverride,
                             document,
                             curvesIncluded,
                             transformation,
                             xThetaYRadiusValues);
    outputXThetaYRadiusValues (modelExportOverride,
                               curvesIncluded,
                               xThetaYRadiusValues,
                               delimiter,
                               str);
    destroy2DArray (xThetaYRadiusValues);
  }
}

void ExportFileRelations::exportOnePerLineXThetaValuesMerged (const DocumentModelExport &modelExportOverride,
                                                              const Document &document,
                                                              const QStringList &curvesIncluded,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportOnePerLineXThetaValuesMerged";

  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;

    exportAllPerLineXThetaValuesMerged (modelExportOverride,
                                        document,
                                        QStringList (curveIncluded),
                                        delimiter,
                                        transformation,
                                        str);
  }
}

void ExportFileRelations::exportToFile (const DocumentModelExport &modelExportOverride,
                                        const Document &document,
                                        const Transformation &transformation,
                                        QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportToFile";

  // Identify curves to be included
  QStringList curvesIncluded = curvesToInclude (modelExportOverride,
                                                document,
                                                document.curvesGraphsNames(),
                                                CONNECT_AS_RELATION_SMOOTH,
                                                CONNECT_AS_RELATION_STRAIGHT);

  // Delimiter
  const QString delimiter = exportDelimiterToText (modelExportOverride.delimiter());

  // Get x/theta values to be used
  CallbackGatherXThetaValuesRelations ftor (modelExportOverride,
                                            curvesIncluded,
                                            transformation);
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackGatherXThetaValuesRelations::callback);
  document.iterateThroughCurvesPointsGraphs(ftorWithCallback);

  // Export in one of two layouts
  if (modelExportOverride.layoutFunctions() == EXPORT_LAYOUT_ALL_PER_LINE) {
    exportAllPerLineXThetaValuesMerged (modelExportOverride,
                                        document,
                                        curvesIncluded,
                                        delimiter,
                                        transformation,
                                        str);
  } else {
    exportOnePerLineXThetaValuesMerged (modelExportOverride,
                                        document,
                                        curvesIncluded,
                                        delimiter,
                                        transformation,
                                        str);
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
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::linearlyInterpolate";

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

    ordinalBefore = ordinal;
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

void ExportFileRelations::loadXThetaYRadiusValues (const DocumentModelExport &modelExportOverride,
                                                   const Document &document,
                                                   const QStringList &curvesIncluded,
                                                   const Transformation &transformation,
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
      loadXThetaYRadiusValuesForCurveRaw (points,
                                          xThetaYRadiusValues [colXTheta],
                                          xThetaYRadiusValues [colYRadius],
                                          transformation);
    } else {

      // Interpolation. Points are taken approximately every every modelExport.pointsIntervalRelations
      ExportValuesOrdinal ordinals = ordinalsAtIntervals (modelExportOverride.pointsIntervalRelations(),
                                                          points);

      if (curve->curveStyle().lineStyle().curveConnectAs() == CONNECT_AS_RELATION_SMOOTH) {

        loadXThetaYRadiusValuesForCurveInterpolatedSmooth (points,
                                                           ordinals,
                                                           xThetaYRadiusValues [colXTheta],
                                                           xThetaYRadiusValues [colYRadius],
                                                           transformation);

      } else {

        loadXThetaYRadiusValuesForCurveInterpolatedStraight (points,
                                                             ordinals,
                                                             xThetaYRadiusValues [colXTheta],
                                                             xThetaYRadiusValues [colYRadius],
                                                             transformation);
      }
    }
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth (const Points &points,
                                                                             const ExportValuesOrdinal &ordinals,
                                                                             QVector<QString*> &xThetaValues,
                                                                             QVector<QString*> &yRadiusValues,
                                                                             const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth";

  vector<double> t;
  vector<SplinePair> xy;
  loadSplinePairsWithTransformation (points,
                                     transformation,
                                     t,
                                     xy);

  // Fit a spline
  Spline spline (t,
                 xy);

  // Subdivide the curve into smaller segments so
  // Get value at desired points
  for (int row = 0; row < ordinals.count(); row++) {

    double ordinal = ordinals.at (row);
    SplinePair splinePairFound = spline.interpolateCoeff(ordinal);
    double xTheta = splinePairFound.x ();
    double yRadius = splinePairFound.y ();

    // Save values for this row
    *(xThetaValues [row]) = QString::number (xTheta);
    *(yRadiusValues [row]) = QString::number (yRadius);
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight (const Points &points,
                                                                               const ExportValuesOrdinal &ordinals,
                                                                               QVector<QString*> &xThetaValues,
                                                                               QVector<QString*> &yRadiusValues,
                                                                               const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight";

  // Get value at desired points
  for (int row = 0; row < ordinals.count(); row++) {

    double ordinal = ordinals.at (row);

    QPointF pointInterpolated = linearlyInterpolate (points,
                                                     ordinal,
                                                     transformation);



    // Save value for this row
    *(xThetaValues [row]) = QString::number (pointInterpolated.x());
    *(yRadiusValues [row]) = QString::number (pointInterpolated.y());
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveRaw (const Points &points,
                                                              QVector<QString*> &xThetaValues,
                                                              QVector<QString*> &yRadiusValues,
                                                              const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveRaw";

  for (int pt = 0; pt < points.count(); pt++) {

    const Point &point = points.at (pt);

    QPointF posGraph;
    transformation.transformScreenToRawGraph (point.posScreen(),
                                              posGraph);

    *(xThetaValues [pt]) = QString::number (posGraph.x());
    *(yRadiusValues [pt]) = QString::number (posGraph.y());
  }
}

int ExportFileRelations::maxColumnSizeAllocation (const DocumentModelExport &modelExport,
                                                  const Document &document,
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

      // Interpolation. Points are taken approximately every every modelExport.pointsIntervalRelations
      ExportValuesOrdinal ordinals = ordinalsAtIntervals (modelExport.pointsIntervalRelations(),
                                                          points);

      maxColumnSize = qMax (maxColumnSize,
                            ordinals.count());
    }
  }

  return maxColumnSize;
}

ExportValuesOrdinal ExportFileRelations::ordinalsAtIntervals (double pointsIntervalRelations,
                                                              const Points &points) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::ordinalsAtIntervals";

  const double NUM_SMALLER_INTERVALS = 1000;

  vector<double> t;
  vector<SplinePair> xy;
  loadSplinePairsWithoutTransformation (points,
                                        t,
                                        xy);

  // Fit a spline
  Spline spline (t,
                 xy);

  // Integrate the distances for the subintervals
  double integratedSeparation;
  QPointF posLast = points.first().posScreen();

  // Simplest method to find the intervals is to break up the curve into many smaller intervals, and then aggregate them
  // into intervals that, as much as possible, have the desired length. Simplicity wins out over accuracy in this
  // approach - accuracy is sacrificed to achieve simplicity
  double tMin = t.front();
  double tMax = t.back();

  // Results. Initially empty, but at the end it will have values tMin, ..., tMax
  ExportValuesOrdinal ordinals;

  double tLast = 0.0;
  double integratedSeparationLast = 0;
  int iTLastInterval = 0;
  for (int iT = 0; iT < NUM_SMALLER_INTERVALS; iT++) {

    double t = tMin + ((tMax - tMin) * iT) / (NUM_SMALLER_INTERVALS - 1.0);

    SplinePair pairNew = spline.interpolateCoeff(t);

    QPointF posNew = QPointF (pairNew.x(),
                              pairNew.y());

    QPointF posDelta = posNew - posLast;
    double integratedSeparationDelta = qSqrt (posDelta.x() * posDelta.x() + posDelta.y() * posDelta.y());
    integratedSeparation += integratedSeparationDelta;

    if ((iT == 0) ||
        (integratedSeparation >= pointsIntervalRelations)) {

      // End of current interval, and start of next interval. For better accuracy without having to crank up
      // NUM_SMALLER_INTERVALS by orders of magnitude, we use linear interpolation
      double sInterp = (pointsIntervalRelations - integratedSeparationLast) / (integratedSeparation - integratedSeparationLast);
      double tInterp = (1.0 - sInterp) * tLast + sInterp * t;

      integratedSeparation = (1.0 - sInterp) * integratedSeparationDelta; // Part of delta that was not used gets applied to next interval
      ordinals.push_back (tInterp);
      iTLastInterval = iT;
    }

    tLast = t;
    integratedSeparationLast = integratedSeparation;
    posLast = posNew;
  }

  if (iTLastInterval < NUM_SMALLER_INTERVALS - 1) {

    // Add last point so we end up at tMax
    ordinals.push_back (tMax);

  }

  return ordinals;
}

void ExportFileRelations::outputXThetaYRadiusValues (const DocumentModelExport &modelExportOverride,
                                                     const QStringList &curvesIncluded,
                                                     QVector<QVector<QString*> > &xThetaYRadiusValues,
                                                     const QString &delimiter,
                                                     QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::outputXThetaYRadiusValues";

  // Header
  if (modelExportOverride.header() != EXPORT_HEADER_NONE) {
    if (modelExportOverride.header() == EXPORT_HEADER_GNUPLOT) {
      str << curveSeparator(*str.string());
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
}
