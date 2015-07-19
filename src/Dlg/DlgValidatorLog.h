#ifndef DLG_VALIDATOR_LOG_H
#define DLG_VALIDATOR_LOG_H

#include "CoordScale.h"
#include <QDoubleValidator>

/// Validator for linear or log scale. Once created for linear or log scale, this sticks with that scale and must
/// be replaced if the scale type is changed
class DlgValidatorLog : public QDoubleValidator
{
public:
  /// Single constructor
  DlgValidatorLog(CoordScale coordScale,
                  QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  CoordScale m_coordScale;
};

#endif // DLG_VALIDATOR_LOG_H
