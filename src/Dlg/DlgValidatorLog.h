#ifndef DLG_VALIDATOR_LOG_H
#define DLG_VALIDATOR_LOG_H

#include "CoordScale.h"
#include <QDoubleValidator>

/// Validator for log scale value. Zero and negative values are invalid
class DlgValidatorLog : public QDoubleValidator
{
public:
  /// Single constructor
  DlgValidatorLog(QObject *parent = 0);

  /// Remember if scale is log or linear. This method is needed since CoordScale argument cannot be added to virtual validate method
  void prepareForValidate (CoordScale coordScale);

  /// Apply the standard validation with 0 as the exclusive minimum. Call setCoordScale just before calling this method
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

private:
  CoordScale m_coordScale;
};

#endif // DLG_VALIDATOR_LOG_H
