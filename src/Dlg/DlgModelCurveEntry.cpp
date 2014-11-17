#include "DlgModelCurveEntry.h"
#include <QStringList>

const QString DELIMITER ("\t");

DlgModelCurveEntry::  DlgModelCurveEntry () :
  m_curveNameCurrent (""),
  m_curveNameOriginal (""),
  m_numPoints (0)
{
}

DlgModelCurveEntry::DlgModelCurveEntry (const QString &curveNameCurrent,
                                        const QString &curveNameOriginal,
                                        int numPoints) :
  m_curveNameCurrent (curveNameCurrent),
  m_curveNameOriginal (curveNameOriginal),
  m_numPoints (numPoints)
{
}

DlgModelCurveEntry::DlgModelCurveEntry (const QString &fromText)
{
  QStringList values = fromText.split (DELIMITER);
  Q_ASSERT (values.count () == 3);
  m_curveNameCurrent = values.at (0);
  m_curveNameOriginal = values.at (1);
  m_numPoints = values.at (2).toInt();
}

QString DlgModelCurveEntry::curveNameCurrent () const
{
  return m_curveNameCurrent;
}

QString DlgModelCurveEntry::curveNameOriginal () const
{
  return m_curveNameOriginal;
}

int DlgModelCurveEntry::numPoints () const
{
  return m_numPoints;
}

void DlgModelCurveEntry::setCurveNameCurrent (const QString &curveNameCurrent)
{
  m_curveNameCurrent = curveNameCurrent;
}

void DlgModelCurveEntry::setCurveNameOriginal (const QString &curveNameOriginal)
{
  m_curveNameOriginal = curveNameOriginal;
}

void DlgModelCurveEntry::setNumPoints (int numPoints)
{
  m_numPoints = numPoints;
}

QString DlgModelCurveEntry::toString () const
{
  return QString ("%1%2%3%4%5")
      .arg (m_curveNameCurrent)
      .arg (DELIMITER)
      .arg (m_curveNameOriginal)
      .arg (DELIMITER)
      .arg (m_numPoints);
}
