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

        if (modelExport.pointsSelectionFunctions() == EXPORT_POINTS_SELECTION_FUNCTIONS_INTERPOLATE_FIRST_CURVE) {
          // Quick exit since once curve is all we want
          break;
        }
      }
    }
  }

  return curvesToInclude;
}

void ExportFileAbstractBase::destroyYPhiValues (QVector<QVector<QString*> > &yPhiValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileAbstractBase::destroyYPhiValues";

  int rowCount = yPhiValues.count();
  int colCount = yPhiValues [0].count();
  for (int row = 0; row < rowCount; row++) {
    for (int col = 0; col < colCount; col++) {
      delete yPhiValues [row] [col];
    }
  }
}

void ExportFileAbstractBase::initializeYPhiValues (const QStringList &curvesIncluded,
                                                   const ExportValues &xThetaValuesMerged,
                                                   QVector<QVector<QString*> > &yPhiValues) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::initializeYPhiValues";

  // Initialize every entry with empty string
  int curveCount = curvesIncluded.count();
  int xThetaCount = xThetaValuesMerged.count();
  for (int ix = 0; ix < xThetaCount; ix++) {
    for (int ic = 0; ic < curveCount; ic++) {
      yPhiValues [ic] [ix] = new QString;
    }
  }
}

void ExportFileAbstractBase::outputXThetaYPhiValues (const ExportValues &xThetaValuesMerged,
                                                     QVector<QVector<QString*> > &yPhiValues,
                                                     const QString &delimiter,
                                                     QTextStream &str) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "ExportFileFunctions::outputXThetaYPhiValues";

  for (int row = 0; row < xThetaValuesMerged.count(); row++) {

    double xTheta = xThetaValuesMerged.at (row);

    str << xTheta;

    for (int col = 0; col < yPhiValues.count(); col++) {

      str << delimiter << *(yPhiValues [row] [col]);
    }

    str << "\n";
  }
}
