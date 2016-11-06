/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef EXPORT_FILE_RELATIONS_H
#define EXPORT_FILE_RELATIONS_H

#include "ExportFileAbstractBase.h"
#include "ExportPointsIntervalUnits.h"
#include "ExportValuesOrdinal.h"
#include <QStringList>
#include <QVector>

class Document;
class DocumentModelCoords;
class DocumentModelExportFormat;
class DocumentModelGeneral;
class MainWindowModel;
class QTextStream;
class Transformation;

/// Strategy class for exporting to a file. This strategy is external to the Document class so that class is simpler.
class ExportFileRelations : public ExportFileAbstractBase
{
public:
  /// Single constructor.
  ExportFileRelations();

  /// Export Document points according to the settings. The DocumentModelExportFormat inside the Document is ignored so
  /// DlgSettingsExport can supply its own DocumentModelExportFormat when previewing what would be exported.
  void exportToFile (const DocumentModelExportFormat &modelExportOverride,
                     const Document &document,
                     const MainWindowModel &modelMainWindow,
                     const Transformation &transformation,
                     QTextStream &str) const;

private:
  void exportAllPerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                           const Document &document,
                                           const MainWindowModel &modelMainWindow,
                                           const QStringList &curvesIncluded,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           bool isLogXTheta,
                                           bool isLogYRadius,
                                           QTextStream &str) const;
  void exportOnePerLineXThetaValuesMerged (const DocumentModelExportFormat &modelExportOverride,
                                           const Document &document,
                                           const MainWindowModel &modelMainWindow,
                                           const QStringList &curvesIncluded,
                                           const QString &delimiter,
                                           const Transformation &transformation,
                                           bool isLogXTheta,
                                           bool isLogYRadius,
                                           QTextStream &str) const;
  void initializeXThetaYRadiusValues (const QStringList &curvesIncluded,
                                      QVector<QVector<QString*> > &xThetaYRadiusValues) const;
  QPointF linearlyInterpolate (const Points &points,
                               double ordinal,
                               const Transformation &transformation) const;
  void loadXThetaYRadiusValues (const DocumentModelExportFormat &modelExportOverride,
                                const Document &document,
                                const MainWindowModel &modelMainWindow,
                                const QStringList &curvesIncluded,
                                const Transformation &transformation,
                                bool isLogXTheta,
                                bool isLogYRadius,
                                QVector<QVector<QString*> > &xThetaYRadiusValues) const;
  void loadXThetaYRadiusValuesForCurveInterpolatedSmooth (const DocumentModelCoords &modelCoords,
                                                          const DocumentModelGeneral  &modelGeneral,
                                                          const MainWindowModel &modelMainWindow,
                                                          const Points &points,
                                                          const ExportValuesOrdinal &ordinals,
                                                          QVector<QString*> &xThetaValues,
                                                          QVector<QString*> &yRadiusValues,
                                                          const Transformation &transformation,
                                                          bool isLogXTheta,
                                                          bool isLogYRadius) const;
  void loadXThetaYRadiusValuesForCurveInterpolatedStraight (const DocumentModelCoords &modelCoords,
                                                            const DocumentModelGeneral &modelGeneral,
                                                            const MainWindowModel &modelMainWindow,
                                                            const Points &points,
                                                            const ExportValuesOrdinal &ordinals,
                                                            QVector<QString*> &xThetaValues,
                                                            QVector<QString*> &yRadiusValues,
                                                            const Transformation &transformation) const;
  void loadXThetaYRadiusValuesForCurveRaw (const DocumentModelCoords &modelCoords,
                                           const DocumentModelGeneral &modelGeneral,
                                           const MainWindowModel &modelMainWindow,
                                           const Points &points,
                                           QVector<QString*> &xThetaValues,
                                           QVector<QString*> &yRadiusValues,
                                           const Transformation &transformation) const;
  int maxColumnSizeAllocation (const DocumentModelExportFormat &modelExportOverride,
                               const Document &document,
                               const Transformation &transformation,
                               bool isLogXTheta,
                               bool isLogYRadius,
                               const QStringList &curvesIncluded) const;
  ExportValuesOrdinal ordinalsAtIntervals (double pointsIntervalRelations,
                                           ExportPointsIntervalUnits pointsIntervalUnits,
                                           CurveConnectAs curveConnectAs,
                                           const Transformation &transformation,
                                           bool isLogXTheta,
                                           bool isLogYRadius,
                                           const Points &points) const;
  ExportValuesOrdinal ordinalsAtIntervalsSmoothGraph (double pointsIntervalRelations,
                                                      const Transformation &transformation,
                                                      bool isLogXTheta,
                                                      bool isLogYRadius,
                                                      const Points &points) const;
  ExportValuesOrdinal ordinalsAtIntervalsSmoothScreen (double pointsIntervalRelations,
                                                       const Points &points) const;
  ExportValuesOrdinal ordinalsAtIntervalsStraightGraph (double pointsIntervalRelations,
                                                        const Transformation &transformation,
                                                        const Points &points) const;
  ExportValuesOrdinal ordinalsAtIntervalsStraightScreen (double pointsIntervalRelations,
                                                         const Points &points) const;

  /// Output 2D array with alternating x/theta and y/radius columns
  void outputXThetaYRadiusValues (const DocumentModelExportFormat &modelExport,
                                  const QStringList &curvesIncluded,
                                  QVector<QVector<QString*> > &xThetaYRadiusValues,
                                  const QString &delimiter,
                                  QTextStream &str) const;
};

#endif // EXPORT_FILE_RELATIONS_H
