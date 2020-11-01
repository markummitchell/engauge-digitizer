/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DOCUMENT_MODEL_GUIDELINE_H
#define DOCUMENT_MODEL_GUIDELINE_H

#include "ColorPalette.h"
#include "DocumentModelAbstractBase.h"
#include "GuidelineValues.h"

class Document;
class QTextStream;

/// Model for managing the coordinate values corresponding Guidelines.
/// The strategy for transition between cartesian and polar reference
/// frames is to discard the old Guideline values since there is no 
/// intuitive mapping between the two sets
class DocumentModelGuideline : public DocumentModelAbstractBase
{
public:
  /// Default constructor.
  DocumentModelGuideline();

  /// Initial constructor from Document.
  DocumentModelGuideline(const Document &document);

  /// Copy constructor.
  DocumentModelGuideline(const DocumentModelGuideline &other);

  /// Assignment constructor.
  DocumentModelGuideline &operator=(const DocumentModelGuideline &other);

  /// Get method for creation circle radius in pixels
  double creationCircleRadius () const;
  
  /// Get method for line color
  ColorPalette lineColor() const;

  /// Get method for line width
  double lineWidth () const;
  
  virtual void loadXml(QXmlStreamReader &reader);
  
  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str) const;

  virtual void saveXml(QXmlStreamWriter &writer) const;

  /// Set method for creation circle radius in pixels
  void setCreationCircleRadius (double radius);
  
  /// Set method for line color
  void setLineColor (ColorPalette lineColor);

  /// Set method for line width
  void setLineWidth (double lineWidth);
  
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
  double m_creationCircleRadius;
  ColorPalette m_lineColor;
  double m_lineWidth;
};

#endif // DOCUMENT_MODEL_GUIDELINE_H
