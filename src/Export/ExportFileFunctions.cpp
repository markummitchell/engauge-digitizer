#include "CallbackGatherXThetaValues.h"
#include "CurveConnectAs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportFileFunctions.h"
#include "ExportLayoutFunctions.h"
#include "Logger.h"
#include <QTextStream>
#include <QVector>
#include "Transformation.h"

ExportFileFunctions::ExportFileFunctions()
{
}

void ExportFileFunctions::exportAllPerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                                              const Document &document,
                                                              const QStringList &curvesIncluded,
                                                              const ExportValues &xThetaValuesMerged,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::exportAllPerLineXThetaValuesMerged";

  // Header
  str << modelExport.xLabel();
  QStringList::const_iterator itrHeader;
  for (itrHeader = curvesIncluded.begin(); itrHeader != curvesIncluded.end(); itrHeader++) {
    QString curveName = *itrHeader;
    str << delimiter << curveName;
  }
  str << "\n";

  int curveCount = curvesIncluded.count();
  int xThetaCount = xThetaValuesMerged.count();
  QVector<QVector<QString*> > yPhiValues (xThetaCount, QVector<QString*> (curveCount));
  initializeYPhiValues (curvesIncluded,
                        xThetaValuesMerged,
                        yPhiValues);
  loadYPhiValues (document,
                  curvesIncluded,
                  transformation,
                  xThetaValuesMerged,
                  yPhiValues);

  outputXThetaYPhiValues (xThetaValuesMerged,
                          yPhiValues,
                          delimiter,
                          str);
  destroyYPhiValues (yPhiValues);
}

void ExportFileFunctions::loadYPhiValues (const Document &document,
                                          const QStringList &curvesIncluded,
                                          const Transformation &transformation,
                                          const ExportValues &xThetaValuesMerged,
                                          QVector<QVector<QString*> > &yPhiValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::loadYPhiValues";
  
  // Initialize every entry with empty string
  int curveCount = curvesIncluded.count();
  int xThetaCount = xThetaValuesMerged.count();
  for (int ix = 0; ix < xThetaCount; ix++) {
    for (int ic = 0; ic < curveCount; ic++) {
    }
  }
}

void ExportFileFunctions::exportOnePerLineXThetaValuesMerged (const DocumentModelExport &modelExport,
                                                              const Document &document,
                                                              const QStringList &curvesIncluded,
                                                              const ExportValues &xThetaValuesMerged,
                                                              const QString &delimiter,
                                                              const Transformation &transformation,
                                                              QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::exportOnePerLineXThetaValuesMerged";

  const int NUM_CURVES_PER_LINE = 1;
  bool isFirst = true;

  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    // Insert line(s) between previous curve and this curve
    if (isFirst) {
      isFirst = false;
    } else {
      if (modelExport.header() == EXPORT_HEADER_GNUPLOT) {
        str << "\n\n"; // Gnuplot requires two blank lines between curves
      } else {
        str << "\n"; // Single blank line
      }
    }

    // This curve
    QString curveIncluded = *itr;

//    QVector<QVector<QString> > vector (curvesIncluded.count ()), QVector<QString>(NUM_CURVES_PER_LINE);

    // Output this curve
    str << modelExport.xLabel();

    ExportValues::const_iterator itr;
    for (itr = xThetaValuesMerged.begin(); itr != xThetaValuesMerged.end(); itr++) {
      double xTheta = *itr;
      str << xTheta << "\n";
    }
  }
}

void ExportFileFunctions::exportToFile (const DocumentModelExport &modelExport,
                                        const Document &document,
                                        const Transformation &transformation,
                                        QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::exportToFile";

  // Identify curves to be included
  QStringList curvesIncluded = curvesToInclude (modelExport,
                                                document,
                                                document.curvesGraphsNames(),
                                                CONNECT_AS_FUNCTION_SMOOTH,
                                                CONNECT_AS_FUNCTION_STRAIGHT);

  // Delimiter
  const QString delimiter = exportDelimiterToString (modelExport.delimiter());

  // Get x/theta values to be used
  CallbackGatherXThetaValues ftor (modelExport,
                                   curvesIncluded,
                                   transformation);
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackGatherXThetaValues::callback);
  document.iterateThroughCurvesPointsGraphs(ftorWithCallback);

  ExportValues xThetaValuesMerged = ftor.xThetaValues();

  // Export in one of two layouts
  if (modelExport.layoutFunctions() == EXPORT_LAYOUT_ALL_PER_LINE) {
    exportAllPerLineXThetaValuesMerged (modelExport,
                                        document,
                                        curvesIncluded,
                                        xThetaValuesMerged,
                                        delimiter,
                                        transformation,
                                        str);
  } else {
    exportOnePerLineXThetaValuesMerged (modelExport,
                                        document,
                                        curvesIncluded,
                                        xThetaValuesMerged,
                                        delimiter,
                                        transformation,
                                        str);
  }
}
