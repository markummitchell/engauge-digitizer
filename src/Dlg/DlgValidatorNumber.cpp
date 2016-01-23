#include "DlgValidatorNumber.h"
#include "Logger.h"

DlgValidatorNumber::DlgValidatorNumber(CoordScale coordScale,
                                       const QLocale &locale,
                                       QObject *parent) :
  DlgValidatorAbstract(parent),
  m_coordScale (coordScale),
  m_locale (locale)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorNumber::DlgValidatorNumber";
}

QValidator::State DlgValidatorNumber::validate (QString &input,
                                                int &pos) const
{
  // First do standard check
  QDoubleValidator validator;
  validator.setLocale (m_locale);
  QValidator::State state = validator.validate (input,
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
