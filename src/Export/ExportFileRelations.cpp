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

void ExportFileRelations::loadXThetaYRadiusValues (const DocumentModelExport &modelExport,
                                                   const Document &document,
                                                   const QStringList &curvesIncluded,
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
                                                           xThetaYRadiusValues [colXTheta],
                                                           xThetaYRadiusValues [colYRadius],
                                                           transformation);

      } else {

        loadXThetaYRadiusValuesForCurveInterpolatedStraight (points,
                                                             xThetaYRadiusValues [colXTheta],
                                                             xThetaYRadiusValues [colYRadius],
                                                             transformation);
      }
    }
  }
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth (const Points &points,
                                                                             QVector<QString*> &xThetaValues,
                                                                             QVector<QString*> &yRadiusValues,
                                                                             const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedSmooth";
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight (const Points &points,
                                                                               QVector<QString*> &xThetaValues,
                                                                               QVector<QString*> &yRadiusValues,
                                                                               const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveInterpolatedStraight";
}

void ExportFileRelations::loadXThetaYRadiusValuesForCurveRaw (const Points &points,
                                                              QVector<QString*> &xThetaValues,
                                                              QVector<QString*> &yRadiusValues,
                                                              const Transformation &transformation) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::loadXThetaYRadiusValuesForCurveRaw";
}

void ExportFileRelations::outputXThetaYRadiusValues (const DocumentModelExport &modelExport,
                                                     const QStringList &curvesIncluded,
                                                     QVector<QVector<QString*> > &xThetaYRadiusValues,
                                                     const QString &delimiter,
                                                     QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileRelations::outputXThetaYRadiusValues";
}
