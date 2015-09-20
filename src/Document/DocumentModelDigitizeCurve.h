#ifndef DOCUMENT_MODEL_DIGITIZE_CURVE_H
#define DOCUMENT_MODEL_DIGITIZE_CURVE_H

#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

/// Model for DlgSettingsDigitizeCurve and CmdSettingsDigitizeCurve. No color is involved because
/// the documentation in QCursor suggests that not all platforms support colored cursors
class DocumentModelDigitizeCurve : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelDigitizeCurve();

  /// Initial constructor from Document.
  DocumentModelDigitizeCurve(const Document &document);

  /// Copy constructor.
  DocumentModelDigitizeCurve(const DocumentModelDigitizeCurve &other);

  /// Assignment constructor.
  DocumentModelDigitizeCurve &operator=(const DocumentModelDigitizeCurve &other);

  /// Set method for cursor inner radius.
  int cursorInnerRadius () const;

  /// Set method for cursor line length.
  int cursorLineLength () const;

  /// Set method for cursor line width.
  int cursorLineWidth () const;

  /// Set method for cursor type.
  bool cursorStandardCross () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for cursor inner radius.
  void setCursorInnerRadius (int innerRadius);

  /// Set method for cursor line length.
  void setCursorLineLength (int lineLength);

  /// Set method for cursor line width.
  void setCursorLineWidth (int lineWidth);

  /// Set method for cursor type.
  void setCursorStandardCross (bool cursorStandardCross);

private:

  bool m_cursorStandardCross;
  int m_cursorInnerRadius;
  int m_cursorLineLength;
  int m_cursorLineWidth;
};

#endif // DOCUMENT_MODEL_DIGITIZE_CURVE_H
