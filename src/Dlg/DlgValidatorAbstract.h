#ifndef DLG_VALIDATOR_ABSTRACT_H
#define DLG_VALIDATOR_ABSTRACT_H

#include <QDoubleValidator>
#include <QString>

/// Abstract validator for all numeric formats
class DlgValidatorAbstract : public QDoubleValidator
{
public:
  /// Single constructor
  DlgValidatorAbstract(QObject *parent = 0);

  virtual ~DlgValidatorAbstract();

  /// Validate according to the numeric format specific to the leaf class
  virtual QValidator::State validate (QString &input,
                                      int &pos) const = 0;

private:

};

#endif // DLG_VALIDATOR_ABSTRACT_H
