#include "CurveConnectAs.h"
#include "Document.h"
#include "EngaugeAssert.h"
#include "ExportFileAbstractBase.h"
#include "Logger.h"
#include <QTextStream>
#include <QVector>
#include "Transformation.h"

ExportFileAbstractBase::ExportFileAbstractBase()
{
}

QStringList ExportFileAbstractBase::curvesToInclude (const DocumentModelExport &modelExport,
                                                     const Document &document,
                                                     const QStringList &curvesGraphsNames,
                                                     CurveConnectAs curveConnectAs1,
                                                     CurveConnectAs curveConnectAs2) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileAbstractBase::curvesToInclude";

  QStringList curvesToInclude;

  // Build a list of curves to include by subtracting the excluded curves from the the complete list.
  // Special case is to use only first included curve if appropriate flag is set
  QStringList::const_iterator itr;
  for (itr = curvesGraphsNames.begin(); itr != curvesGraphsNames.end(); itr++) {

    QString curvesGraphName = *itr;

    if (!modelExport.curveNamesNotExported().contains (curvesGraphName)) {

      const Curve *curve = document.curveForCurveName(curvesGraphName);
      ENGAUGE_CHECK_PTR (curve);

      // Not excluded which means it gets included, but only if it is a function
      if (curve->curveStyle().lineStyle().curveConnectAs() == curveConnectAs1 ||
          curve->curveStyle().lineStyle().curveConnectAs() == curveConnectAs2) {

        curvesToInclude.push_back (curvesGraphName);
      }
    }
  }

  return curvesToInclude;
}

void ExportFileAbstractBase::destroyYRadiusValues (QVector<QVector<QString*> > &yRadiusValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileAbstractBase::destroyYRadiusValues";

  int colCount = yRadiusValues.count();
  int rowCount = yRadiusValues [0].count();
  for (int row = 0; row < rowCount; row++) {
    for (int col = 0; col < colCount; col++) {
      delete yRadiusValues [col] [row];
    }
  }
}

void ExportFileAbstractBase::initializeYRadiusValues (const QStringList &curvesIncluded,
                                                      const ExportValues &xThetaValuesMerged,
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

void ExportFileAbstractBase::outputXThetaYRadiusValues (const DocumentModelExport &modelExport,
                                                        const QStringList &curvesIncluded,
                                                        const ExportValues &xThetaValuesMerged,
                                                        QVector<QVector<QString*> > &yRadiusValues,
                                                        const QString &delimiter,
                                                        QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::outputXThetaYRadiusValues";

  // Header
  str << modelExport.xLabel();
  QStringList::const_iterator itrHeader;
  for (itrHeader = curvesIncluded.begin(); itrHeader != curvesIncluded.end(); itrHeader++) {
    QString curveName = *itrHeader;
    str << delimiter << curveName;
  }
  str << "\n";

  for (int row = 0; row < xThetaValuesMerged.count(); row++) {

    double xTheta = xThetaValuesMerged.at (row);

    str << xTheta;

    for (int col = 0; col < yRadiusValues.count(); col++) {

      str << delimiter << *(yRadiusValues [col] [row]);
    }

    str << "\n";
  }
}
