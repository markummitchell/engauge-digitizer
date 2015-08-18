#ifndef DOCUMENT_MODEL_EXPORT_FORMAT_H
#define DOCUMENT_MODEL_EXPORT_FORMAT_H

#include "DocumentModelAbstractBase.h"
#include "ExportDelimiter.h"
#include "ExportHeader.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsIntervalUnits.h"
#include "ExportPointsSelectionFunctions.h"
#include "ExportPointsSelectionRelations.h"
#include <QStringList>

class Document;
class QTextStream;

/// Model for DlgSettingsExportFormat and CmdSettingsExportFormat.
class DocumentModelExportFormat : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelExportFormat();

  /// Initial constructor from Document.
  DocumentModelExportFormat(const Document &document);

  /// Copy constructor.
  DocumentModelExportFormat(const DocumentModelExportFormat &other);

  /// Assignment constructor.
  DocumentModelExportFormat &operator=(const DocumentModelExportFormat &other);

  /// Get method for curve names not exported.
  QStringList curveNamesNotExported() const;

  /// Get method for delimiter.
  ExportDelimiter delimiter() const;

  /// Get method for header.
  ExportHeader header() const;

  /// Get method for functions layout.
  ExportLayoutFunctions layoutFunctions() const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for points interval for functions.
  double pointsIntervalFunctions () const;

  /// Get method for relations interval for relations
  double pointsIntervalRelations () const;

  /// Get method for points interval units for functions.
  ExportPointsIntervalUnits pointsIntervalUnitsFunctions () const;

  /// Get method for points interval units for relations.
  ExportPointsIntervalUnits pointsIntervalUnitsRelations () const;

  /// Get method for point selection for functions.
  ExportPointsSelectionFunctions pointsSelectionFunctions() const;

  /// Get method for point selection for relations.
  ExportPointsSelectionRelations pointsSelectionRelations() const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for curve names not exported.
  void setCurveNamesNotExported(const QStringList &curveNamesNotExported);

  /// Set method for delimiter.
  void setDelimiter(ExportDelimiter exportDelimiter);

  /// Set method for header.
  void setHeader(ExportHeader exportHeader);

  /// Set method for functions layout.
  void setLayoutFunctions(ExportLayoutFunctions exportLayoutFunctions);

  /// Set method for points interval for functions
  void setPointsIntervalFunctions (double pointsIntervalFunctions);

  /// Set method for relations interval for relations
  void setPointsIntervalRelations (double pointsIntervalRelations);

  /// Set method for points interval units for functions
  void setPointsIntervalUnitsFunctions (ExportPointsIntervalUnits pointsIntervalUnitsFunctions);

  /// Set method for points interval units for relations
  void setPointsIntervalUnitsRelations (ExportPointsIntervalUnits pointsIntervalUnitsRelations);

  /// Set method for point selection for functions.
  void setPointsSelectionFunctions(ExportPointsSelectionFunctions exportPointsSelectionFunctions);

  /// Set method for point selection for relations.
  void setPointsSelectionRelations(ExportPointsSelectionRelations exportPointsSelectionRelations);

  /// Set method for x label.
  void setXLabel (const QString &xLabel);

  /// Get method for x label.
  QString xLabel () const;

private:

  // Curves to be excluded from export. New curves will not appear in this so they will be exported by default.
  QStringList m_curveNamesNotExported;

  ExportPointsSelectionFunctions m_pointsSelectionFunctions;
  double m_pointsIntervalFunctions;
  ExportPointsIntervalUnits m_pointsIntervalUnitsFunctions;
  ExportPointsSelectionRelations m_pointsSelectionRelations;
  double m_pointsIntervalRelations;
  ExportPointsIntervalUnits m_pointsIntervalUnitsRelations;
  ExportLayoutFunctions m_layoutFunctions;
  ExportDelimiter m_delimiter;
  ExportHeader m_header;
  QString m_xLabel;
};

#endif // DOCUMENT_MODEL_EXPORT_FORMAT_H
