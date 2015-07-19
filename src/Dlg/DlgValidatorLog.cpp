#include "DlgValidatorLog.h"

DlgValidatorLog::DlgValidatorLog(QObject *parent) :
  QDoubleValidator(parent)
{
}

void DlgValidatorLog::prepareForValidate (CoordScale coordScale)
{
  m_coordScale = coordScale;
}

QValidator::State DlgValidatorLog::validate (QString &input,
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
