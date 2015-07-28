#include "DlgValidatorDegreesMinutesSeconds.h"
#include "Logger.h"

DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds(CoordScale coordScale,
                                                                     QObject *parent) :
  DlgValidatorAbstract(parent),
  m_coordScale (coordScale)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DlgValidatorDegreesMinutesSeconds::DlgValidatorDegreesMinutesSeconds";
}

QValidator::State DlgValidatorDegreesMinutesSeconds::validate (QString &input,
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
