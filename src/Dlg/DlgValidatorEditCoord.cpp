#include "DlgValidatorEditCoord.h"

DlgValidatorEditCoord::DlgValidatorEditCoord(bool isCartesian,
                                             bool isXThetaElseYRadius,
                                             CoordScale coordScale,
                                             QObject *parent) :
  QDoubleValidator(parent),
  m_isCartesian (isCartesian),
  m_isXThetaElseYRadius (isXThetaElseYRadius),
  m_coordScale (coordScale)
{
}

QValidator::State DlgValidatorEditCoord::validate (QString &input,
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
