#include "DlgValidatorEditCoord.h"

const int UNUSED_VALUE = 0;

DlgValidatorEditCoord::DlgValidatorEditCoord(CoordScale coordScale,
                                             CoordUnitsNonPolarTheta coordUnits,
                                             QObject *parent) :
  QDoubleValidator(parent),
  m_coordScale (coordScale),
  m_isNonPolarTheta (true),
  m_coordUnitsNonPolarTheta (coordUnits),
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
