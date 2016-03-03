/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_GENERAL_H
#define DOCUMENT_MODEL_GENERAL_H

#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

/// Model for DlgSettingsGeneral and CmdSettingsGeneral.
class DocumentModelGeneral : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelGeneral();

  /// Initial constructor from Document.
  DocumentModelGeneral(const Document &document);

  /// Copy constructor.
  DocumentModelGeneral(const DocumentModelGeneral &other);

  /// Assignment constructor.
  DocumentModelGeneral &operator=(const DocumentModelGeneral &other);

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

#endif // DOCUMENT_MODEL_GENERAL_H
