#ifndef DOCUMENT_MODEL_FILTER_H
#define DOCUMENT_MODEL_FILTER_H

#include "DocumentModelAbstractBase.h"
#include "FilterParameter.h"

class Document;

/// Model for DlgSettingsFilter and CmdSettingsFilter.
class DocumentModelFilter : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelFilter();

  /// Initial constructor from Document.
  DocumentModelFilter(const Document &document);

  /// Copy constructor.
  DocumentModelFilter(const DocumentModelFilter &other);

  /// Assignment constructor.
  DocumentModelFilter &operator=(const DocumentModelFilter &other);

  /// Get method for filter parameter.
  FilterParameter filterParameter() const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for filter parameter.
  void setFilterParameter(FilterParameter filterParameter);

private:

  FilterParameter m_filterParameter;
};

#endif // DOCUMENT_MODEL_FILTER_H
