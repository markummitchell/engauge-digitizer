#ifndef DOCUMENT_MODEL_AXES_CHECKER_H
#define DOCUMENT_MODEL_AXES_CHECKER_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"
#include "CheckerMode.h"

class Document;
class QTextStream;

/// Model for DlgSettingsAxesChecker and CmdSettingsAxesChecker.
class DocumentModelAxesChecker : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelAxesChecker();

  /// Initial constructor from Document.
  DocumentModelAxesChecker(const Document &document);

  /// Copy constructor.
  DocumentModelAxesChecker(const DocumentModelAxesChecker &other);

  /// Assignment constructor.
  DocumentModelAxesChecker &operator=(const DocumentModelAxesChecker &other);

  /// Get method for checker lifetime mode.
  CheckerMode checkerMode() const;

  /// Get method for checker lifetime in seconds.
  int checkerSeconds() const;

  /// Get method for line color.
  ColorPalette lineColor () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for checker mode.
  void setCheckerMode (CheckerMode checkerMode);

  /// Set method for checker lifetime in seconds.
  void setCheckerSeconds (int seconds);

  /// Set method for line color.
  void setLineColor (ColorPalette lineColor);

private:

  CheckerMode m_checkerMode;
  int m_checkerSeconds; // Time interval for CHECKER_MODE_N_SECONDS
  ColorPalette m_lineColor;
};

#endif // DOCUMENT_MODEL_AXES_CHECKER_H
