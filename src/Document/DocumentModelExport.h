#ifndef DOCUMENT_MODEL_EXPORT_H
#define DOCUMENT_MODEL_EXPORT_H

#include "DocumentModelAbstractBase.h"
#include "ExportDelimiter.h"
#include "ExportHeader.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "ExportPointsSelectionRelations.h"
#include <QStringList>

class CmdMediator;

/// Model for DlgSettingsExport and CmdSettingsExport.
class DocumentModelExport : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelExport();

  /// Initial constructor from Document.
  DocumentModelExport(const CmdMediator &cmdMediator);

  /// Copy constructor.
  DocumentModelExport(const DocumentModelExport &other);

  /// Assignment constructor.
  DocumentModelExport &operator=(const DocumentModelExport &other);

  /// Get method for curve names not exported.
  QStringList curveNamesNotExported() const;

  /// Get method for delimiter.
  ExportDelimiter exportDelimiter() const;

  /// Get method for header.
  ExportHeader exportHeader() const;

  /// Get method for functions layout.
  ExportLayoutFunctions exportLayoutFunctions() const;

  /// Get method for point selection for functions.
  ExportPointsSelectionFunctions exportPointsSelectionFunctions() const;

  /// Get method for point selection for relations.
  ExportPointsSelectionRelations exportPointsSelectionRelations() const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for curve names not exported.
  void setCurveNamesNotExported(const QStringList &curveNamesNotExported);

  /// Set method for delimiter.
  void setExportDelimiter(ExportDelimiter exportDelimiter);

  /// Set method for header.
  void setExportHeader(ExportHeader exportHeader);

  /// Set method for functions layout.
  void setExportLayoutFunctions(ExportLayoutFunctions exportLayoutFunctions);

  /// Set method for point selection for functions.
  void setExportPointsSelectionFunctions(ExportPointsSelectionFunctions exportPointsSelectionFunctions);

  /// Set method for point selection for relations.
  void setExportPointsSelectionRelations(ExportPointsSelectionRelations exportPointsSelectionRelations);

private:

  // Curves to be excluded from export. New curves will not appear in this so they will be exported by default.
  QStringList m_curveNamesNotExported;

  ExportPointsSelectionFunctions m_exportPointsSelectionFunctions;
  ExportPointsSelectionRelations m_exportPointsSelectionRelations;
  ExportLayoutFunctions m_exportLayoutFunctions;
  ExportDelimiter m_exportDelimiter;
  ExportHeader m_exportHeader;
};

#endif // DOCUMENT_MODEL_EXPORT_H
