#ifndef DOCUMENT_MODEL_AXES_HIGHLIGHTS_H
#define DOCUMENT_MODEL_AXES_HIGHLIGHTS_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"
#include "HighlightsMode.h"

class Document;

/// Model for DlgSettingsAxesHighlights and CmdSettingsAxesHighlights.
class DocumentModelAxesHighlights : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelAxesHighlights();

  /// Initial constructor from Document.
  DocumentModelAxesHighlights(const Document &document);

  /// Copy constructor.
  DocumentModelAxesHighlights(const DocumentModelAxesHighlights &other);

  /// Assignment constructor.
  DocumentModelAxesHighlights &operator=(const DocumentModelAxesHighlights &other);

  /// Get method for highlights lifetime mode.
  HighlightsMode highlightsMode() const;

  /// Get method for highlights lifetime in seconds.
  int highlightsSeconds() const;

  /// Get method for line color.
  ColorPalette lineColor () const;

  virtual void saveModel(QXmlStreamWriter &stream) const;

  /// Set method for highlights mode.
  void setHighlightsMode (HighlightsMode highlightsMode);

  /// Set method for highlights lifetime in seconds.
  void setHighlightsSeconds (int seconds);

  /// Set method for line color.
  void setLineColor (ColorPalette lineColor);

private:

  HighlightsMode m_highlightsMode;
  int m_highlightsSeconds; // Time interval for HIGHLIGHT_MODE_N_SECONDS
  ColorPalette m_lineColor;
};

#endif // DOCUMENT_MODEL_AXES_HIGHLIGHTS_H
