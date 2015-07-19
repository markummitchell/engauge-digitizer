#include "CallbackGatherXThetaValues.h"
#include "Document.h"
#include "ExportLayoutFunctions.h"
#include "ExportToFile.h"
#include "Logger.h"
#include <QTextStream>
#include "Transformation.h"

ExportToFile::ExportToFile()
{
}

QStringList ExportToFile::curvesToInclude (const DocumentModelExport &modelExport,
                                           const QStringList &curvesGraphsNames) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::curvesToInclude";

  QStringList curvesToInclude;

  // Build a list of curves to include by subtracting the excluded curves from the the complete list.
  // Special case is to use only first included curve if appropriate flag is set
  QStringList::const_iterator itr;
  for (itr = curvesGraphsNames.begin(); itr != curvesGraphsNames.end(); itr++) {

    QString curvesGraphName = *itr;

    if (!modelExport.curveNamesNotExported().contains (curvesGraphName)) {

      // Not excluded which means it gets included
      curvesToInclude.push_back (curvesGraphName);

      if (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE) {
        // Quick exit since once curve is all we want
        break;
      }
    }
  }

  return curvesToInclude;
}

void ExportToFile::exportToFile (const DocumentModelExport &modelExport,
                                 const Document &document,
                                 const Transformation &transformation,
                                 QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFile";

  QStringList curvesIncluded = curvesToInclude (modelExport,
                                                document.curvesGraphsNames());

  if (modelExport.layoutFunctions() == EXPORT_LAYOUT_ALL_PER_LINE) {
    exportToFileAllPerLine (modelExport,
                            document,
                            curvesIncluded,
                            transformation,
                            str);
  } else {
    exportToFileOnePerLine (modelExport,
                            document,
                            curvesIncluded,
                            transformation,
                            str);
  }
}

void ExportToFile::exportToFileAllPerLine (const DocumentModelExport &modelExport,
                                           const Document &document,
                                           const QStringList &curvesIncluded,
                                           const Transformation &transformation,
                                           QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFileAllPerLine";

  CallbackGatherXThetaValues ftor (modelExport,
                                   curvesIncluded,
                                   transformation);
  Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                     &CallbackGatherXThetaValues::callback);
  document.iterateThroughCurvesPointsGraphs(ftorWithCallback);

  Values xThetaValues = ftor.xThetaValues();

  Values::const_iterator itr;
  for (itr = xThetaValues.begin(); itr != xThetaValues.end(); itr++) {
    double xTheta = *itr;
    str << xTheta << "\n";
  }
}

void ExportToFile::exportToFileOnePerLine (const DocumentModelExport &modelExport,
                                           const Document &document,
                                           const QStringList &curvesIncluded,
                                           const Transformation &transformation,
                                           QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFileOnePerLine";

  QStringList::const_iterator itr;
  for (itr = curvesIncluded.begin(); itr != curvesIncluded.end(); itr++) {

    QString curveIncluded = *itr;

    CallbackGatherXThetaValues ftor (modelExport,
                                     QStringList (curveIncluded),
                                     transformation);
    Functor2wRet<const QString &, const Point &, CallbackSearchReturn> ftorWithCallback = functor_ret (ftor,
                                                                                                       &CallbackGatherXThetaValues::callback);
    document.iterateThroughCurvesPointsGraphs(ftorWithCallback);

    Values xThetaValues = ftor.xThetaValues();

    Values::const_iterator itr;
    for (itr = xThetaValues.begin(); itr != xThetaValues.end(); itr++) {
      double xTheta = *itr;
      str << xTheta << "\n";
    }
  }
}
