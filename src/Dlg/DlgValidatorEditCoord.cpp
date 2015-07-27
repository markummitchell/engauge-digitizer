#include "DlgValidatorEditCoord.h"

const int UNUSED_VALUE = 0;
const CoordUnitsDate UNUSED_DATE = COORD_UNITS_DATE_SKIP;
const CoordUnitsTime UNUSED_TIME = COORD_UNITS_TIME_SKIP;

DlgValidatorEditCoord::DlgValidatorEditCoord(CoordScale coordScale,
                                             CoordUnitsNonPolarTheta coordUnits,
                                             CoordUnitsDate coordUnitsDate,
                                             CoordUnitsTime coordUnitsTime,
                                             QObject *parent) :
  QDoubleValidator(parent),
  m_coordScale (coordScale),
  m_isNonPolarTheta (true),
  m_coordUnitsNonPolarTheta (coordUnits),
  m_coordUnitsDate (coordUnitsDate),
  m_coordUnitsTime (coordUnitsTime),
  m_coordUnitsPolarTheta ((CoordUnitsPolarTheta) UNUSED_VALUE)
{
}

DlgValidatorEditCoord::DlgValidatorEditCoord(CoordScale coordScale,
                                             CoordUnitsPolarTheta coordUnits,
                                             QObject *parent) :
  QDoubleValidator(parent),
  m_coordScale (coordScale),
  m_isNonPolarTheta (false),
  m_coordUnitsNonPolarTheta ((CoordUnitsNonPolarTheta) UNUSED_VALUE),
  m_coordUnitsDate (UNUSED_DATE),
  m_coordUnitsTime (UNUSED_TIME),
  m_coordUnitsPolarTheta (coordUnits)
{
}

QValidator::State DlgValidatorEditCoord::validate (QString &input,
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
