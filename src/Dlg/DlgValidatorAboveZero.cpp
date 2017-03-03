/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DlgValidatorAboveZero.h"
#include "Logger.h"
#include <QDoubleValidator>
#include <QLocale>

DlgValidatorAboveZero::DlgValidatorAboveZero(const QLocale &locale,
                                             QObject *parent) :
  DlgValidatorAbstract(parent),
  m_locale (locale)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorAboveZero::DlgValidatorAboveZero";
}

QValidator::State DlgValidatorAboveZero::validate (QString &input,
                                                   int &pos) const
{
  // First do standard check
  QDoubleValidator validator;
  validator.setLocale (m_locale);
  QValidator::State state = validator.validate (input,
                                                pos);
  if (state == QValidator::Acceptable) {

    if (m_locale.toDouble (input) <= 0.0) {

      // Cannot allow negative number or zero value
      state = QValidator::Invalid;

    }
  }

  return state;
}
