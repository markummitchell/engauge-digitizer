/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_ABSTRACT_BASE_H
#define DOCUMENT_MODEL_ABSTRACT_BASE_H

#include <QXmlStreamReader>

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

  /// Load model from serialized xml
  virtual void loadXml(QXmlStreamReader &reader) = 0;

  /// Save entire model as xml into stream.
  virtual void saveXml(QXmlStreamWriter &writer) const = 0;
};

#endif // DOCUMENT_MODEL_ABSTRACT_BASE_H
