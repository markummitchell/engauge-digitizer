/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_VALIDATOR_DEGREES_MINUTES_SECONDS_H
#define DLG_VALIDATOR_DEGREES_MINUTES_SECONDS_H

#include "CoordScale.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "DlgValidatorAbstract.h"

/// Validator for angles in real degrees, integer degrees and real minutes, or integer degrees with integer minutes with 
/// real seconds
class DlgValidatorDegreesMinutesSeconds : public DlgValidatorAbstract
{
public:
  /// Single constructor
  DlgValidatorDegreesMinutesSeconds(CoordScale coordScale,
                                    QObject *parent = 0);

  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  DlgValidatorDegreesMinutesSeconds();

  const CoordScale m_coordScale;
};

#endif // DLG_VALIDATOR_DEGREES_MINUTES_SECONDS_H
