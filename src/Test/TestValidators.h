#ifndef TEST_VALIDATORS_H
#define TEST_VALIDATORS_H

#include "DlgValidatorDateTime.h"
#include "DlgValidatorDegreesMinutesSeconds.h"
#include "DlgValidatorNumber.h"
#include <QObject>

/// Unit tests of validators
class TestValidators : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestValidators(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testDateTimeDate ();
  void testDateTimeDateTime ();
  void testDateTimeDateTimePm ();
  void testDateTimeTime ();
  void testDegreesMinutesSecondsDegrees ();
  void testDegreesMinutesSecondsDegreesMinutes ();
  void testDegreesMinutesSecondsDegreesMinutesSeconds ();
  void testNumberInteger ();
  void testNumberReal ();
  void testNumberRealBad ();

private:

  bool stateDateTime (const QString &string,
                      QValidator::State expectedState);
  bool stateDegreesMinutesSeconds (const QString &string,
                                   QValidator::State expectedState);
  bool stateNumber (const QString &string,
                    QValidator::State expectedState);

  DlgValidatorDateTime *m_validatorDateTime;
  DlgValidatorDegreesMinutesSeconds *m_validatorDegreesMinutesSeconds;
  DlgValidatorNumber *m_validatorNumber;
};

#endif // TEST_VALIDATORS_H
