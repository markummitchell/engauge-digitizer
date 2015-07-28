#include "DlgValidatorDegreesMinutesSeconds.h"
#include "Logger.h"

const int UNUSED_VALUE = 0;
const CoordUnitsDate UNUSED_DATE = COORD_UNITS_DATE_SKIP;
const CoordUnitsTime UNUSED_TIME = COORD_UNITS_TIME_SKIP;

DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds(CoordScale coordScale,
                                                                     QObject *parent) :
  DlgValidatorAbstract(parent),
  m_coordScale (coordScale)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds";
}

QValidator::State DlgValidatorDegreesMinutesSeconds::validate (QString &input,
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
