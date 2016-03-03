/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_VALIDATOR_NUMBER_H
#define DLG_VALIDATOR_NUMBER_H

#include "CoordScale.h"
#include "CoordUnitsNonPolarTheta.h"
#include "CoordUnitsPolarTheta.h"
#include "DlgValidatorAbstract.h"
#include <QLocale>

/// Validator for generic (=simple) numbers
class DlgValidatorNumber : public DlgValidatorAbstract
{
public:
  /// Single constructor
  DlgValidatorNumber(CoordScale coordScale,
                     const QLocale &locale,
                     QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  DlgValidatorNumber();

  const CoordScale m_coordScale;
  const QLocale m_locale;
};

#endif // DLG_VALIDATOR_NUMBER_H
