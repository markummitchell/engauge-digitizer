#ifndef DOCUMENT_MODEL_ABSTRACT_BASE_H
#define DOCUMENT_MODEL_ABSTRACT_BASE_H

#include <QXmlStreamReader>

class QTextStream;
class QXmlStreamWriter;

/// Abstract base class for document models. This class enforces a common interface for the leaf subclasses.
class DocumentModelAbstractBase
{
public:
  /// Single constructor.
  DocumentModelAbstractBase();

  /// Single destructor.
  virtual ~DocumentModelAbstractBase();

protected:

  /// Load model from serialized xml
  virtual void loadXml(QXmlStreamReader &reader) = 0;

  /// Save entire model as xml into stream.
  virtual void saveXml(QXmlStreamWriter &writer) const = 0;
};

#endif // DOCUMENT_MODEL_ABSTRACT_BASE_H
