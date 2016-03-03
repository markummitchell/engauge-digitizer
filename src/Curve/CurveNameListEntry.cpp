/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "CurveNameListEntry.h"
#include "DocumentSerialize.h"
#include "EngaugeAssert.h"
#include "Logger.h"
#include <QStringList>
#include <QXmlStreamWriter>

const QString DELIMITER ("\t");

CurveNameListEntry::  CurveNameListEntry () :
  m_curveNameCurrent (""),
  m_curveNameOriginal (""),
  m_numPoints (0)
{
}

CurveNameListEntry::CurveNameListEntry (const QString &curveNameCurrent,
                                        const QString &curveNameOriginal,
                                        int numPoints) :
  m_curveNameCurrent (curveNameCurrent),
  m_curveNameOriginal (curveNameOriginal),
  m_numPoints (numPoints)
{
}

CurveNameListEntry::CurveNameListEntry (const QString &fromText)
{
  QStringList values = fromText.split (DELIMITER);
  ENGAUGE_ASSERT (values.count () == 3);
  m_curveNameCurrent = values.at (0);
  m_curveNameOriginal = values.at (1);
  m_numPoints = values.at (2).toInt();
}

QString CurveNameListEntry::curveNameCurrent () const
{
  return m_curveNameCurrent;
}

QString CurveNameListEntry::curveNameOriginal () const
{
  return m_curveNameOriginal;
}

int CurveNameListEntry::numPoints () const
{
  return m_numPoints;
}

void CurveNameListEntry::setCurveNameCurrent (const QString &curveNameCurrent)
{
  m_curveNameCurrent = curveNameCurrent;
}

void CurveNameListEntry::setCurveNameOriginal (const QString &curveNameOriginal)
{
  m_curveNameOriginal = curveNameOriginal;
}

void CurveNameListEntry::setNumPoints (int numPoints)
{
  m_numPoints = numPoints;
}

QString CurveNameListEntry::toString () const
{
  return QString ("%1%2%3%4%5")
      .arg (m_curveNameCurrent)
      .arg (DELIMITER)
      .arg (m_curveNameOriginal)
      .arg (DELIMITER)
      .arg (m_numPoints);
}
