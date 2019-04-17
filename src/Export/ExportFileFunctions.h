/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_FILE_FUNCTIONS_H
#define EXPORT_FILE_FUNCTIONS_H

#include "CurveLimits.h"
#include "ExportFileAbstractBase.h"
#include "ExportValuesXOrY.h"
#include "Points.h"
#include <QStringList>
#include <QVector>
#include "ValuesVectorXOrY.h"

class Document;
class DocumentModelCoords;
class DocumentModelExportFormat;
class DocumentModelGeneral;
class MainWindowModel;
class QTextStream;
class Transformation;

/// Strategy class for exporting to a file. This strategy is external to the Document class so that class is simpler.
class ExportFileFunctions : public ExportFileAbstractBase
{
  // For unit testing
  friend class TestExport;

public:
  /// Single constructor.
  ExportFileFunctions();

  /// Export Document points according to the settings. The DocumentModelExportFormat inside the Document is ignored so
  /// DlgSettingsExport can supply its own DocumentModelExportFormat when previewing what would be exported.
  void exportToFile (const DocumentModelExportFormat &modelExportOverride,
                     const Document &document,
                     const MainWindowModel &modelMainWindow,
                     const Transformation &transformation,
                     QTextStream &str,
                     unsigned int &numWritesSoFar) const;

private:

  void exportAllPerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                           const Document &document,
                                           const MainWindowModel &modelMainWindow,
                                           const QStringList &curvesIncluded,
                                           const ExportValuesXOrY &xThetaValues,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           bool isLogXTheta,
                                           bool isLogYRadius,
                                           const CurveLimits curveLimitsMin,
                                           const CurveLimits curveLimitsMax,
                                           QTextStream &str,
                                           unsigned int &numWritesSoFar) const;
  void exportOnePerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                           const Document &document,
                                           const MainWindowModel &modelMainWindow,
                                           const QStringList &curvesIncluded,
                                           const ExportValuesXOrY &xThetaValues,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           bool isLogXTheta,
                                           bool isLogYRadius,
                                           const CurveLimits curveLimitsMin,
                                           const CurveLimits curveLimitsMax,
                                           QTextStream &str,
                                           unsigned int &numWritesSoFar) const;

  /// Allocate a 2D y/radius array indexed by (included) curve and x/theta.
  /// Array rows and columns are set up so yRadiusValues[N] gives vector for Nth curve. Values are strings
  /// so non-applicable entries can be blank
  void initializeYRadiusValues (const QStringList &curvesIncluded,
                                const ExportValuesXOrY &xThetaValuesMerged,
                                QVector<QVector<QString*> > &yRadiusValues) const;

  double linearlyInterpolate (const Points &points,
                              double xThetaValue,
                              const Transformation &transformation) const;
  void loadYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                          const Document &document,
                          const MainWindowModel &modelMainWindow,
                          const QStringList &curvesIncluded,
                          const Transformation &transformation,
                          bool isLogXTheta,
                          bool isLogYRadius,
                          const ExportValuesXOrY &xThetaValues,
                          const CurveLimits &curveLimitsMin,
                          const CurveLimits &curveLimitsMax,
                          QVector<QVector<QString*> > &yRadiusValues) const;
  void loadYRadiusValuesForCurveInterpolatedSmooth (const DocumentModelCoords &modelCoords,
                                                    const DocumentModelGeneral &modelGeneral,
                                                    const MainWindowModel &modelMainWindow,
                                                    const Points &points,
                                                    const ExportValuesXOrY &xThetaValues,
                                                    const Transformation &transformation,
                                                    bool isLogXTheta,
                                                    bool isLogYRadius,
                                                    const QString &curveName,
                                                    const CurveLimits &curveLimitsMin,
                                                    const CurveLimits &curveLimitsMax,
                                                    QVector<QString*> &yRadiusValues) const;
  void loadYRadiusValuesForCurveInterpolatedStraight (const DocumentModelCoords &modelCoords,
                                                      const DocumentModelGeneral &modelGeneral,
                                                      const MainWindowModel &modelMainWindow,
                                                      const Points &points,
                                                      const ExportValuesXOrY &xThetaValues,
                                                      const Transformation &transformation,
                                                      const QString &curveName,
                                                      const CurveLimits &curveLimitsMin,
                                                      const CurveLimits &curveLimitsMax,
                                                      QVector<QString*> &yRadiusValues) const;
  void loadYRadiusValuesForCurveRaw (const DocumentModelCoords &modelCoords,
                                     const DocumentModelGeneral &modelGeneral,
                                     const MainWindowModel &modelMainWindow,
                                     const Points &points,
                                     const ExportValuesXOrY &xThetaValues,
                                     const Transformation &transformation,
                                     const QString &curveName,
                                     const CurveLimits &curveLimitsMin,
                                     const CurveLimits &curveLimitsMax,
                                     QVector<QString*> &yRadiusValues) const;

  /// Output 2D y/radius array along with x/theta vector in first column
  void outputXThetaYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                                  const DocumentModelCoords &modelCoords,
                                  const DocumentModelGeneral &modelGeneral,
                                  const MainWindowModel &modelMainWindow,
                                  const QStringList &curvesIncluded,
                                  const ExportValuesXOrY &xThetaValuesMerged,
                                  const Transformation &transformation,
                                  QVector<QVector<QString*> > &yRadiusValues,
                                  const QString &delimiter,
                                  QTextStream &str,
                                  unsigned int &numWritesSoFar) const;
  // Only include rows that have at least one y/radius entry. This check is required when outputing one curve per row
  // since the union of all x/theta values is applied to each curve
  bool rowHasAtLeastOneYRadiusEntry (const QVector<QVector<QString*> > &yRadiusValues,
                                     int row) const;

  // If there are bounds for the curve, make sure xTheta is within those bounds
  bool xThetaIsNotOutOfBounds (double xTheta,
                               const QString &curveName,
                               const CurveLimits &curveLimitsMin,
                               const CurveLimits &curveLimitsMax) const;
};

#endif // EXPORT_FILE_FUNCTIONS_H
