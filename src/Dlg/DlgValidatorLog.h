#ifndef DLG_VALIDATOR_LOG_H
#define DLG_VALIDATOR_LOG_H

#include <QDoubleValidator>

/// Validator for log scale value. Zero and negative values are invalid
class DlgValidatorLog : public QDoubleValidator
{
public:
  /// Single constructor
  DlgValidatorLog(QObject *parent = 0);

  /// Apply the standard validation with 0 as the exclusive minimum
  virtual QValidator::State validate (QString &input,
                                      int &pos) const;

};

#endif // DLG_VALIDATOR_LOG_H
