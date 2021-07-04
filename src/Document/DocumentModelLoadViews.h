/******************************************************************************************************
 * (C) 2021 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_LOAD_VIEWS_H
#define DOCUMENT_MODEL_LOAD_VIEWS_H

#include "DocumentModelAbstractBase.h"

class Document;
class QTextStream;

/// Model for storing enabled/disabled states of views for optional restoration during loading
class DocumentModelLoadViews : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelLoadViews();

  /// Initial constructor from Document.
  DocumentModelLoadViews(const Document &document);

  /// Copy constructor.
  DocumentModelLoadViews(const DocumentModelLoadViews &other);

  /// Assignment constructor.
  DocumentModelLoadViews &operator=(const DocumentModelLoadViews &other);

  /// Get method for gridlines.
  bool gridlines () const;

  /// Get method for guidelines.
  bool guidelines () const;

  virtual void loadXml(QXmlStreamReader &reader);

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for gridlines.
  void setGridlines (bool gridlines);

  /// Set method for guidelines.
  void setGuidelines (bool guidelines);

private:

  bool m_gridlines;
  bool m_guidelines;
};

#endif // DOCUMENT_MODEL_LOAD_VIEWS_H
