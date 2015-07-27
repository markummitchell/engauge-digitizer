#ifndef DLG_VALIDATOR_EDIT_COORD_H
#define DLG_VALIDATOR_EDIT_COORD_H

#include "CoordScale.h"
#include <QDoubleValidator>

/// Validator for linear or log scale. Once created for linear or log scale, this sticks with that scale and must
/// be replaced if the scale type is changed
class DlgValidatorEditCoord : public QDoubleValidator
{
public:
  /// Single constructor
  DlgValidatorEditCoord(bool isCartesian,
                        bool isXThetaElseYRadius,
                        CoordScale coordScale,
                        QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  const bool m_isCartesian;
  const bool m_isXThetaElseYRadius;
  const CoordScale m_coordScale;
};

#endif // DLG_VALIDATOR_EDIT_COORD_H
