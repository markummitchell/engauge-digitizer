#include "DlgValidatorLog.h"

DlgValidatorLog::DlgValidatorLog(QObject *parent) :
  QDoubleValidator(parent)
{
  setBottom (0.0); // Inclusive boundary
}

QValidator::State DlgValidatorLog::validate (QString &input,
                                             int &pos) const
{
  // First do standard check
  QValidator::State state = QDoubleValidator::validate (input,
                                                 pos);
  if (state == QValidator::Acceptable) {

    // Make lower boundary exclusive
    if (input.toDouble() == 0.0) {

      return QValidator::Intermediate;
    }
  }

  return state;
}
