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

  void testDateTime ();
  void testDegreesMinutesSeconds ();
  void testNumber ();

private:

  DlgValidatorDateTime *m_validatorDateTime;
  DlgValidatorDegreesMinutesSeconds *m_validatorDegreesMinutesSeconds;
  DlgValidatorNumber *m_validatorNumber;
};

#endif // TEST_VALIDATORS_H
