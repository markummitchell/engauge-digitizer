#ifndef DOCUMENT_MODEL_COMMON_H
#define DOCUMENT_MODEL_COMMON_H

#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

/// Model for DlgSettingsCommon and CmdSettingsCommon.
class DocumentModelCommon : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelCommon();

  /// Initial constructor from Document.
  DocumentModelCommon(const Document &document);

  /// Copy constructor.
  DocumentModelCommon(const DocumentModelCommon &other);

  /// Assignment constructor.
  DocumentModelCommon &operator=(const DocumentModelCommon &other);

  /// Get method for effective cursor size
  int cursorSize() const;

  /// Get method for extra digits of precsion
  int extraPrecision () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for effective cursor size
  void setCursorSize (int cursorSize);

  /// Set method for extra digits of precision
  void setExtraPrecision (int extraPrecision);

private:

  int m_cursorSize;
  int m_extraPrecision;
};

#endif // DOCUMENT_MODEL_COMMON_H
