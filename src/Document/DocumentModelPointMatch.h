/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_POINT_MATCH_H
#define DOCUMENT_MODEL_POINT_MATCH_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

/// Model for DlgSettingsPointMatch and CmdSettingsPointMatch.
class DocumentModelPointMatch : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelPointMatch();

  /// Initial constructor from Document.
  DocumentModelPointMatch(const Document &document);

  /// Copy constructor.
  DocumentModelPointMatch(const DocumentModelPointMatch &other);

  /// Assignment constructor.
  DocumentModelPointMatch &operator=(const DocumentModelPointMatch &other);

  virtual void loadXml(QXmlStreamReader &reader);

  /// Get method for max point size.
  double maxPointSize() const;

  /// Get method for accepted color.
  ColorPalette paletteColorAccepted() const;

  /// Get method for candidate color.
  ColorPalette paletteColorCandidate() const;

  /// Get method for rejected color.
  ColorPalette paletteColorRejected() const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for max point size.
  void setMaxPointSize (double maxPointSize);

  /// Set method for accepted color.
  void setPaletteColorAccepted(ColorPalette paletteColorAccepted);

  /// Set method for candidate color.
  void setPaletteColorCandidate(ColorPalette paletteColorCandidate);

  /// Set method for rejected color.
  void setPaletteColorRejected(ColorPalette paletteColorRejected);

private:

  double m_minPointSeparation;
  double m_maxPointSize;
  ColorPalette m_paletteColorAccepted;
  ColorPalette m_paletteColorCandidate;
  ColorPalette m_paletteColorRejected;
};

#endif // DOCUMENT_MODEL_POINT_MATCH_H
