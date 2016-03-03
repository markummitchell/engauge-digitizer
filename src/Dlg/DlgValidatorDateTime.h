/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_VALIDATOR_DATE_TIME_H
#define DLG_VALIDATOR_DATE_TIME_H

#include "CoordScale.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "DlgValidatorAbstract.h"

/// Validator for numeric value expressed as date and/or time
class DlgValidatorDateTime : public DlgValidatorAbstract
{
public:
  /// Single constructor
  DlgValidatorDateTime(CoordScale coordScale,
                       CoordUnitsDate coordUnitsDate,
                       CoordUnitsTime coordUnitsTime,
                       QObject *parent = 0);

  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  DlgValidatorDateTime();

  const CoordScale m_coordScale;
  const CoordUnitsDate m_coordUnitsDate;
  const CoordUnitsTime m_coordUnitsTime;
};

#endif // DLG_VALIDATOR_DATE_TIME_H
