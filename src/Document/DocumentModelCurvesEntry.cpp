#include "DocumentModelCurvesEntry.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QStringList>
#include <QXmlStreamWriter>

const QString DELIMITER ("\t");

DocumentModelCurvesEntry::  DocumentModelCurvesEntry () :
  m_curveNameCurrent (""),
  m_curveNameOriginal (""),
  m_numPoints (0)
{
}

DocumentModelCurvesEntry::DocumentModelCurvesEntry (const QString &curveNameCurrent,
                                        const QString &curveNameOriginal,
                                        int numPoints) :
  m_curveNameCurrent (curveNameCurrent),
  m_curveNameOriginal (curveNameOriginal),
  m_numPoints (numPoints)
{
}

DocumentModelCurvesEntry::DocumentModelCurvesEntry (const QString &fromText)
{
  QStringList values = fromText.split (DELIMITER);
  Q_ASSERT (values.count () == 3);
  m_curveNameCurrent = values.at (0);
  m_curveNameOriginal = values.at (1);
  m_numPoints = values.at (2).toInt();
}

QString DocumentModelCurvesEntry::curveNameCurrent () const
{
  return m_curveNameCurrent;
}

QString DocumentModelCurvesEntry::curveNameOriginal () const
{
  return m_curveNameOriginal;
}

int DocumentModelCurvesEntry::numPoints () const
{
  return m_numPoints;
}

void DocumentModelCurvesEntry::saveDocument(QXmlStreamWriter &stream) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelCurvesEntry::saveDocument";

  stream.writeStartElement(DOCUMENT_SERIALIZE_CURVES_ENTRY);
  stream.writeAttribute (DOCUMENT_SERIALIZE_CURVES_ENTRY_CURVE_NAME_CURRENT, m_curveNameCurrent);
  stream.writeAttribute (DOCUMENT_SERIALIZE_CURVES_ENTRY_CURVE_NAME_ORIGINAL, m_curveNameOriginal);
  stream.writeAttribute (DOCUMENT_SERIALIZE_CURVES_ENTRY_NUM_POINTS, QString::number (m_numPoints));
  stream.writeEndElement();
}

void DocumentModelCurvesEntry::setCurveNameCurrent (const QString &curveNameCurrent)
{
  m_curveNameCurrent = curveNameCurrent;
}

void DocumentModelCurvesEntry::setCurveNameOriginal (const QString &curveNameOriginal)
{
  m_curveNameOriginal = curveNameOriginal;
}

void DocumentModelCurvesEntry::setNumPoints (int numPoints)
{
  m_numPoints = numPoints;
}

QString DocumentModelCurvesEntry::toString () const
{
  return QString ("%1%2%3%4%5")
      .arg (m_curveNameCurrent)
      .arg (DELIMITER)
      .arg (m_curveNameOriginal)
      .arg (DELIMITER)
      .arg (m_numPoints);
}
