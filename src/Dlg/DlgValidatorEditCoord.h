#ifndef DLG_VALIDATOR_EDIT_COORD_H
#define DLG_VALIDATOR_EDIT_COORD_H

#include "CoordScale.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include <QDoubleValidator>

/// Validator for linear or log scale. Once created for linear or log scale, this sticks with that scale and must
/// be replaced if the scale type is changed
class DlgValidatorEditCoord : public QDoubleValidator
{
public:
  /// Constructor for non-polar coordinate
  DlgValidatorEditCoord(CoordScale coordScale,
                        CoordUnitsNonPolarTheta coordUnits,
                        CoordUnitsDate coordUnitsDate,
                        CoordUnitsTime coordUnitsTime,
                        QObject *parent = 0);

  /// Constructor for polar coordinate
  DlgValidatorEditCoord(CoordScale coordScale,
                        CoordUnitsPolarTheta coordUnits,
                        QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  const CoordScale m_coordScale;
  const bool m_isNonPolarTheta;

  // Applies when m_isNonPolarTheta is true, with date/time also requiring m_coordUnitsNonPolarTheta=COORD_UNITS_NON_POLAR_THETA_DATE_TIME
  const CoordUnitsNonPolarTheta m_coordUnitsNonPolarTheta;
  const CoordUnitsDate m_coordUnitsDate;
  const CoordUnitsTime m_coordUnitsTime;

  // Applies when m_isNonPolarTheta is false
  const CoordUnitsPolarTheta m_coordUnitsPolarTheta;
};

#endif // DLG_VALIDATOR_EDIT_COORD_H
