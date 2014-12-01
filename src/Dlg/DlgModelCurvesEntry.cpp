#include "DlgModelCurvesEntry.h"
#include <QStringList>
#include <QXmlStreamWriter>

const QString DELIMITER ("\t");

DlgModelCurvesEntry::  DlgModelCurvesEntry () :
  m_curveNameCurrent (""),
  m_curveNameOriginal (""),
  m_numPoints (0)
{
}

DlgModelCurvesEntry::DlgModelCurvesEntry (const QString &curveNameCurrent,
                                        const QString &curveNameOriginal,
                                        int numPoints) :
  m_curveNameCurrent (curveNameCurrent),
  m_curveNameOriginal (curveNameOriginal),
  m_numPoints (numPoints)
{
}

DlgModelCurvesEntry::DlgModelCurvesEntry (const QString &fromText)
{
  QStringList values = fromText.split (DELIMITER);
  Q_ASSERT (values.count () == 3);
  m_curveNameCurrent = values.at (0);
  m_curveNameOriginal = values.at (1);
  m_numPoints = values.at (2).toInt();
}

QString DlgModelCurvesEntry::curveNameCurrent () const
{
  return m_curveNameCurrent;
}

QString DlgModelCurvesEntry::curveNameOriginal () const
{
  return m_curveNameOriginal;
}

int DlgModelCurvesEntry::numPoints () const
{
  return m_numPoints;
}

void DlgModelCurvesEntry::setCurveNameCurrent (const QString &curveNameCurrent)
{
  m_curveNameCurrent = curveNameCurrent;
}

void DlgModelCurvesEntry::setCurveNameOriginal (const QString &curveNameOriginal)
{
  m_curveNameOriginal = curveNameOriginal;
}

void DlgModelCurvesEntry::setNumPoints (int numPoints)
{
  m_numPoints = numPoints;
}

QString DlgModelCurvesEntry::toString () const
{
  return QString ("%1%2%3%4%5")
      .arg (m_curveNameCurrent)
      .arg (DELIMITER)
      .arg (m_curveNameOriginal)
      .arg (DELIMITER)
      .arg (m_numPoints);
}
