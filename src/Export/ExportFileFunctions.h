#ifndef EXPORT_FILE_FUNCTIONS_H
#define EXPORT_FILE_FUNCTIONS_H

#include "ExportFileAbstractBase.h"
#include "ExportValuesXOrY.h"
#include <QStringList>
#include <QVector>

class Document;
class DocumentModelCoords;
class DocumentModelExportFormat;
class MainWindowModel;
class QTextStream;
class Transformation;

/// Strategy class for exporting to a file. This strategy is external to the
/// Document class so that class is simpler.
class ExportFileFunctions : public ExportFileAbstractBase {
public:
  /// Single constructor.
  ExportFileFunctions();

  /// Export Document points according to the settings. The
  /// DocumentModelExportFormat inside the Document is ignored so
  /// DlgSettingsExport can supply its own DocumentModelExportFormat when
  /// previewing what would be exported.
  void exportToFile(const DocumentModelExportFormat &modelExportOverride,
                    const Document &document,
                    const MainWindowModel &modelMainWindow,
                    const Transformation &transformation,
                    QTextStream &str) const;

private:
  void exportAllPerLineXThetaValuesMerged(
      const DocumentModelExportFormat &modelExportOverride,
      const Document &document, const MainWindowModel &modelMainWindow,
      const QStringList &curvesIncluded, const ExportValuesXOrY &xThetaValues,
      const QString &delimiter, const Transformation &transformation,
      QTextStream &str) const;
  void exportOnePerLineXThetaValuesMerged(
      const DocumentModelExportFormat &modelExportOverride,
      const Document &document, const MainWindowModel &modelMainWindow,
      const QStringList &curvesIncluded, const ExportValuesXOrY &xThetaValues,
      const QString &delimiter, const Transformation &transformation,
      QTextStream &str) const;

  /// Allocate a 2D y/radius array indexed by (included) curve and x/theta.
  /// Array rows and columns are set up so yRadiusValues[N] gives vector for Nth
  /// curve. Values are strings
  /// so non-applicable entries can be blank
  void
  initializeYRadiusValues(const QStringList &curvesIncluded,
                          const ExportValuesXOrY &xThetaValuesMerged,
                          QVector<QVector<QString *>> &yRadiusValues) const;

  double linearlyInterpolate(const Points &points, double xThetaValue,
                             const Transformation &transformation) const;
  void loadYRadiusValues(const DocumentModelExportFormat &modelExport,
                         const Document &document,
                         const MainWindowModel &modelMainWindow,
                         const QStringList &curvesIncluded,
                         const Transformation &transformation,
                         const ExportValuesXOrY &xThetaValues,
                         QVector<QVector<QString *>> &yRadiusValues) const;
  void loadYRadiusValuesForCurveInterpolatedSmooth(
      const DocumentModelCoords &modelCoords,
      const MainWindowModel &modelMainWindow, const Points &points,
      const ExportValuesXOrY &xThetaValues,
      const Transformation &transformation,
      QVector<QString *> &yRadiusValues) const;
  void loadYRadiusValuesForCurveInterpolatedStraight(
      const DocumentModelCoords &modelCoords,
      const MainWindowModel &modelMainWindow, const Points &points,
      const ExportValuesXOrY &xThetaValues,
      const Transformation &transformation,
      QVector<QString *> &yRadiusValues) const;
  void loadYRadiusValuesForCurveRaw(const DocumentModelCoords &modelCoords,
                                    const MainWindowModel &modelMainWindow,
                                    const Points &points,
                                    const ExportValuesXOrY &xThetaValues,
                                    const Transformation &transformation,
                                    QVector<QString *> &yRadiusValues) const;

  /// Output 2D y/radius array along with x/theta vector in first column
  void outputXThetaYRadiusValues(
      const DocumentModelExportFormat &modelExportOverride,
      const DocumentModelCoords &modelCoords,
      const MainWindowModel &modelMainWindow, const QStringList &curvesIncluded,
      const ExportValuesXOrY &xThetaValuesMerged,
      const Transformation &transformation,
      QVector<QVector<QString *>> &yRadiusValues, const QString &delimiter,
      QTextStream &str) const;
  // Only include rows that have at least one y/radius entry. This check is
  // required when outputing one curve per row
  // since the union of all x/theta values is applied to each curve
  bool
  rowHasAtLeastOneYRadiusEntry(const QVector<QVector<QString *>> &yRadiusValues,
                               int row) const;
};

#endif // EXPORT_FILE_FUNCTIONS_H
