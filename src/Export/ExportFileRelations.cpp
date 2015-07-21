#include "CallbackGatherXThetaValuesRelations.h"
#include "CurveConnectAs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportFileRelations.h"
#include "ExportLayoutFunctions.h"
#include "Logger.h"
#include <QTextStream>
#include <QVector>
#include "Transformation.h"

const int COLUMNS_PER_CURVE = 2;

ExportFileRelations::ExportFileRelations()
{
}

void ExportFileRelations::exportAllPerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                                              const Document &document,
                                                              const QStringList &curvesIncluded,
                                                              const CallbackGatherXThetaValuesRelations &ftor,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportAllPerLineXThetaValuesMerged";

  int curveCount = curvesIncluded.count();
  int maxColumnSize = ftor.maxColumnSize(curvesIncluded);

  QVector<QVector<QString*> > xThetaYRadiusValues (COLUMNS_PER_CURVE * curveCount, QVector<QString*> (maxColumnSize));
  initializeXThetaYRadiusValues (curvesIncluded,
                                 ftor,
                                 xThetaYRadiusValues);
  loadXThetaYRadiusValues (modelExport,
                           document,
                           curvesIncluded,
                           ftor,
                           transformation,
                           xThetaYRadiusValues);
  outputXThetaYRadiusValues (modelExport,
                             curvesIncluded,
                             xThetaYRadiusValues,
                             delimiter,
                             str);
  destroy2DArray (xThetaYRadiusValues);
}

void ExportFileRelations::exportOnePerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                                              const Document &document,
                                                              const QStringList &curvesIncluded,
                                                              const CallbackGatherXThetaValuesRelations &ftor,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportOnePerLineXThetaValuesMerged";

  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;

    exportAllPerLineXThetaValuesMerged (modelExport,
                                        document,
                                        QStringList (curveIncluded),
                                        ftor,
                                        delimiter,
                                        transformation,
                                        str);
  }
}

void ExportFileRelations::exportToFile (const DocumentModelExport &modelExport,
                                        const Document &document,
                                        const Transformation &transformation,
                                        QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::exportToFile";

  // Identify curves to be included
  QStringList curvesIncluded = curvesToInclude (modelExport,
                                                document,
                                                document.curvesGraphsNames(),
                                                CONNECT_AS_RELATION_SMOOTH,
                                                CONNECT_AS_RELATION_STRAIGHT);

  // Delimiter
  const QString delimiter = exportDelimiterToText (modelExport.delimiter());

  // Get x/theta values to be used
  CallbackGatherXThetaValuesRelations ftor (modelExport,
                                            curvesIncluded,
                                            transformation);
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackGatherXThetaValuesRelations::callback);
  document.iterateThroughCurvesPointsGraphs(ftorWithCallback);

  // Export in one of two layouts
  if (modelExport.layoutFunctions() == EXPORT_LAYOUT_ALL_PER_LINE) {
    exportAllPerLineXThetaValuesMerged (modelExport,
                                        document,
                                        curvesIncluded,
                                        ftor,
                                        delimiter,
                                        transformation,
                                        str);
  } else {
    exportOnePerLineXThetaValuesMerged (modelExport,
                                        document,
                                        curvesIncluded,
                                        ftor,
                                        delimiter,
                                        transformation,
                                        str);
  }
}

void ExportFileRelations::initializeXThetaYRadiusValues (const QStringList &curvesIncluded,
                                                         const CallbackGatherXThetaValuesRelations &ftor,
                                                         QVector<QVector<QString*> > &xThetaYRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::initializeXThetaYRadiusValues";

  // Initialize every entry with empty string
  int curveCount = curvesIncluded.count();
  int xThetaCount = ftor.maxColumnSize(curvesIncluded);
  for (int row = 0; row < xThetaCount; row++) {
    for (int col = 0; col < 2 * curveCount; col++) {
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

void ExportFileRelations::loadXThetaYRadiusValues (const DocumentModelExport &modelExport,
                                                   const Document &document,
                                                   const QStringList &curvesIncluded,
                                                   const CallbackGatherXThetaValuesRelations &ftor,
                                                   const Transformation &transformation,
                                                   QVector<QVector<QString*> > &xThetaYRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValues";

  for (int ic = 0; ic < curvesIncluded.count(); ic++) {

    int colXTheta = 2 * ic;
    int colYRadius = 2 * ic + 1;

    const QString curveName = curvesIncluded.at (ic);

    const Curve *curve = document.curveForCurveName (curveName);
    const Points points = curve->points ();

    if (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_RAW) {

      // No interpolation. Raw points
      loadXThetaYRadiusValuesForCurveRaw (points,
                                          xThetaYRadiusValues [colXTheta],
                                          xThetaYRadiusValues [colYRadius],
                                          transformation);
    } else {

      // Interpolation
      if (curve->curveStyle().lineStyle().curveConnectAs() == CONNECT_AS_FUNCTION_SMOOTH) {

        loadXThetaYRadiusValuesForCurveInterpolatedSmooth (points,
                                                           ftor,
                                                           curveName,
                                                           xThetaYRadiusValues [colXTheta],
                                                           xThetaYRadiusValues [colYRadius],
                                                           transformation);

      } else {

        loadXThetaYRadiusValuesForCurveInterpolatedStraight (points,
                                                             ftor,
                                                             curveName,
                                                             xThetaYRadiusValues [colXTheta],
                                                             xThetaYRadiusValues [colYRadius],
                                                             transformation);
      }
    }
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth (const Points &points,
                                                                             const CallbackGatherXThetaValuesRelations &ftor,
                                                                             const QString &curveName,
                                                                             QVector<QString*> &xThetaValues,
                                                                             QVector<QString*> &yRadiusValues,
                                                                             const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth";
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight (const Points &points,
                                                                               const CallbackGatherXThetaValuesRelations &ftor,
                                                                               const QString &curveName,
                                                                               QVector<QString*> &xThetaValues,
                                                                               QVector<QString*> &yRadiusValues,
                                                                               const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight";

  // Get value at desired points
  for (int row = 0; row < ftor.ordinals(curveName).count(); row++) {

    double ordinal = ftor.ordinals(curveName).at (row);

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

void ExportFileRelations::outputXThetaYRadiusValues (const DocumentModelExport &modelExport,
                                                     const QStringList &curvesIncluded,
                                                     QVector<QVector<QString*> > &xThetaYRadiusValues,
                                                     const QString &delimiter,
                                                     QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::outputXThetaYRadiusValues";
}
