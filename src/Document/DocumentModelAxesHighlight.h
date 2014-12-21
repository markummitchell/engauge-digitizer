#ifndef DOCUMENT_MODEL_AXES_HIGHLIGHT_H
#define DOCUMENT_MODEL_AXES_HIGHLIGHT_H

#include "AxesHighlight.h"
#include "DocumentModelAbstractBase.h"

class Document;

/// Model for DlgSettingsAxesHighlight and CmdSettingsAxesHighlight.
class DocumentModelAxesHighlight : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelAxesHighlight();

  /// Initial constructor from Document.
  DocumentModelAxesHighlight(const Document &document);

  /// Copy constructor.
  DocumentModelAxesHighlight(const DocumentModelAxesHighlight &other);

  /// Assignment constructor.
  DocumentModelAxesHighlight &operator=(const DocumentModelAxesHighlight &other);

  /// Get method for highlight.
  AxesHighlight axesHighlight() const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for highlight.
  void setAxesHighlight (AxesHighlight axesHighlight);

private:

  AxesHighlight m_axesHighlight;
};

#endif // DOCUMENT_MODEL_AXES_HIGHLIGHT_H
