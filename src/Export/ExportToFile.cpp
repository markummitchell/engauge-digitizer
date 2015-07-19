#include "CallbackGatherXThetaValues.h"
#include "Document.h"
#include "ExportToFile.h"
#include "Logger.h"
#include <QTextStream>
#include "Transformation.h"

ExportToFile::ExportToFile()
{
}

void ExportToFile::exportToFile (const DocumentModelExport &modelExport,
                                 const Document &document,
                                 const Transformation &transformation,
                                 QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportToFile::exportToFile";

  CallbackGatherXThetaValues ftor (modelExport,
                                   document.curvesGraphsNames(),
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
