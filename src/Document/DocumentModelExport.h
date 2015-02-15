#ifndef DOCUMENT_MODEL_EXPORT_H
#define DOCUMENT_MODEL_EXPORT_H

#include "DocumentModelAbstractBase.h"
#include "ExportDelimiter.h"
#include "ExportHeader.h"
#include "ExportLayoutFunctions.h"
#include "ExportPointsSelectionFunctions.h"
#include "ExportPointsSelectionRelations.h"
#include <QStringList>

class Document;

/// Model for DlgSettingsExport and CmdSettingsExport.
class DocumentModelExport : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelExport();

  /// Initial constructor from Document.
  DocumentModelExport(const Document &document);

  /// Copy constructor.
  DocumentModelExport(const DocumentModelExport &other);

  /// Assignment constructor.
  DocumentModelExport &operator=(const DocumentModelExport &other);

  /// Get method for curve names not exported.
  QStringList curveNamesNotExported() const;

  /// Get method for delimiter.
  ExportDelimiter delimiter() const;

  /// Get method for header.
  ExportHeader header() const;

  /// Get method for functions layout.
  ExportLayoutFunctions layoutFunctions() const;

  virtual void loadDocument(QXmlStreamReader &reader);

  /// Get method for points interval.
  double pointsInterval () const;

  /// Get method for point selection for functions.
  ExportPointsSelectionFunctions pointsSelectionFunctions() const;

  /// Get method for point selection for relations.
  ExportPointsSelectionRelations pointsSelectionRelations() const;

  /// Get method for relations interval.
  double relationsInterval () const;

  virtual void saveDocument(QXmlStreamWriter &writer) const;

  /// Set method for curve names not exported.
  void setCurveNamesNotExported(const QStringList &curveNamesNotExported);

  /// Set method for delimiter.
  void setDelimiter(ExportDelimiter exportDelimiter);

  /// Set method for header.
  void setHeader(ExportHeader exportHeader);

  /// Set method for functions layout.
  void setLayoutFunctions(ExportLayoutFunctions exportLayoutFunctions);

  /// Set method for points interval.
  void setPointsInterval (double pointsInterval);

  /// Set method for point selection for functions.
  void setPointsSelectionFunctions(ExportPointsSelectionFunctions exportPointsSelectionFunctions);

  /// Set method for point selection for relations.
  void setPointsSelectionRelations(ExportPointsSelectionRelations exportPointsSelectionRelations);

  /// Set method for relations interval.
  void setRelationsInterval (double relationsInterval);

  /// Set method for x label.
  void setXLabel (const QString &xLabel);

  /// Get method for x label.
  QString xLabel () const;

private:

  // Curves to be excluded from export. New curves will not appear in this so they will be exported by default.
  QStringList m_curveNamesNotExported;

  ExportPointsSelectionFunctions m_pointsSelectionFunctions;
  double m_pointsInterval;
  ExportPointsSelectionRelations m_pointsSelectionRelations;
  double m_relationsInterval;
  ExportLayoutFunctions m_layoutFunctions;
  ExportDelimiter m_delimiter;
  ExportHeader m_header;
  QString m_xLabel;
};

#endif // DOCUMENT_MODEL_EXPORT_H
