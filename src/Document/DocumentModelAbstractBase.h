#ifndef DOCUMENT_MODEL_ABSTRACT_BASE_H
#define DOCUMENT_MODEL_ABSTRACT_BASE_H

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
  /// Save entire model as xml into stream.
  virtual void saveModel(QXmlStreamWriter &stream) const = 0;
};

#endif // DOCUMENT_MODEL_ABSTRACT_BASE_H
