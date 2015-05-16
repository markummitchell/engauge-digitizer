#ifndef DOCUMENT_MODEL_SEGMENTS_H
#define DOCUMENT_MODEL_SEGMENTS_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

/// Model for DlgSettingsSegments and CmdSettingsSegments.
class DocumentModelSegments : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelSegments();

  /// Initial constructor from Document.
  DocumentModelSegments(const Document &document);

  /// Copy constructor.
  DocumentModelSegments(const DocumentModelSegments &other);

  /// Assignment constructor.
  DocumentModelSegments &operator=(const DocumentModelSegments &other);

  /// Get method for fill corners.
  bool fillCorners () const;

  /// Get method for line color.
  ColorPalette lineColor() const;

  /// Get method for line width.
  double lineWidth() const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for min length.
  double minLength() const;

  /// Get method for point separation.
  double pointSeparation() const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for fill corners.
  void setFillCorners (bool fillCorners);

  /// Set method for line color.
  void setLineColor(ColorPalette lineColor);

  /// Set method for line width.
  void setLineWidth (double lineWidth);

  /// Set method for min length.
  void setMinLength(double minLength);

  /// Set method for point separation.
  void setPointSeparation(double pointSeparation);

private:

  double m_pointSeparation;
  double m_minLength;
  bool m_fillCorners;
  double m_lineWidth;
  ColorPalette m_lineColor;
};

#endif // DOCUMENT_MODEL_SEGMENTS_H
