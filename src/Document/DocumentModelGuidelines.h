/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_GUIDELINES_H
#define DOCUMENT_MODEL_GUIDELINES_H

#include "DocumentModelAbstractBase.h"
#include "GuidelineValues.h"

class Document;
class QTextStream;

/// Model for managing the coordinate values corresponding Guidelines.
/// The strategy for transition between cartesian and polar reference
/// frames is to discard the old Guideline values since there is no 
/// intuitive mapping between the two sets
class DocumentModelGuidelines : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelGuidelines();

  /// Initial constructor from Document.
  DocumentModelGuidelines(const Document &document);

  /// Copy constructor.
  DocumentModelGuidelines(const DocumentModelGuidelines &other);

  /// Assignment constructor.
  DocumentModelGuidelines &operator=(const DocumentModelGuidelines &other);

  /// Constructor used by Guidelines class to send guidelines to Document
  DocumentModelGuidelines(const GuidelineValues &valuesXT,
                          const GuidelineValues &valuesYR);

  virtual void loadXml(QXmlStreamReader &reader);
  
  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for x/t values
  void setValuesX (const GuidelineValues &valuesX);

  /// Set method for y/r values
  void setValuesY (const GuidelineValues &valuesY);

  /// Get method for x/t values
  GuidelineValues valuesX () const;

  /// Get method for y/r values
  GuidelineValues valuesY () const;

private:

  void loadXmlVector (QXmlStreamReader &reader,
                      const QString &tokenEnd,
                      GuidelineValues &guidelineValues) const;
  void saveXmlVector (QXmlStreamWriter &writer,
                      const QString &tokenAll,
                      const GuidelineValues &values) const;

  GuidelineValues m_valuesX;
  GuidelineValues m_valuesY;  
};

#endif // DOCUMENT_MODEL_GUIDELINES_H
