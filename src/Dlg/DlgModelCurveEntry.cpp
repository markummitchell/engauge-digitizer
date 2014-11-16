#include "DlgModelCurveEntry.h"
#include <QStringList>

const QString DELIMITER ("\t");

DlgModelCurveEntry::DlgModelCurveEntry (const QString &curveNameCurrent,
                                        const QString &curveNameOriginal) :
  m_curveNameCurrent (curveNameCurrent),
  m_curveNameOriginal (curveNameOriginal)
{

}

DlgModelCurveEntry::DlgModelCurveEntry (const QString &fromText)
{
  QStringList curveNames = fromText.split (DELIMITER);
  Q_ASSERT (curveNames.count () == 2);
  m_curveNameCurrent = curveNames.at (0);
  m_curveNameOriginal = curveNames.at (1);
}

QString DlgModelCurveEntry::curveNameCurrent () const
{
  return m_curveNameCurrent;
}

QString DlgModelCurveEntry::curveNameOriginal () const
{
  return m_curveNameOriginal;
}

QString DlgModelCurveEntry::toString () const
{
  return m_curveNameCurrent + DELIMITER + m_curveNameOriginal;
}
