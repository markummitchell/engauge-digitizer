/******************************************************************************************************
 * (C) 2017 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef DLG_VALIDATOR_ABOVE_ZERO_H
#define DLG_VALIDATOR_ABOVE_ZERO_H

#include "DlgValidatorAbstract.h"
#include <QLocale>

/// Validator for generic (=simple) numbers that must be greater than zero
class DlgValidatorAboveZero : public DlgValidatorAbstract
{
public:
  /// Single constructor
  DlgValidatorAboveZero(const QLocale &locale,
                        QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  DlgValidatorAboveZero();

  const QLocale m_locale;
};

#endif // DLG_VALIDATOR_ABOVE_ZERO_H
