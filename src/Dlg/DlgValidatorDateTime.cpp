#include "DlgValidatorDateTime.h"
#include "Logger.h"

DlgValidatorDateTime::DlgValidatorDateTime(CoordScale coordScale,
                                           CoordUnitsDate coordUnitsDate,
                                           CoordUnitsTime coordUnitsTime,
                                           QObject *parent) :
  DlgValidatorAbstract(parent),
  m_coordScale (coordScale),
  m_coordUnitsDate (coordUnitsDate),
  m_coordUnitsTime (coordUnitsTime)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorDateTime::DlgValidatorDateTime";
}

QValidator::State DlgValidatorDateTime::validate (QString &input,
                                                  int &pos) const
{
  // First do standard check
  QValidator::State state = QDoubleValidator::validate (input,
                                                        pos);
  if (state == QValidator::Acceptable) {

    if (m_coordScale == COORD_SCALE_LOG) {
      if (input.toDouble () < 0.0) {

        // Cannot allow negative number
        state = QValidator::Invalid;

      } if (input.toDouble () == 0.0) {

        // Treat as a leading zero, which is legal
        state = QValidator::Intermediate;
      }
    }
  }

  return state;
}
