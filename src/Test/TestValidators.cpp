#include "CoordUnitsNonPolarTheta.h"
#include "DlgValidatorDateTime.h"
#include "DlgValidatorDegreesMinutesSeconds.h"
#include "DlgValidatorNumber.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestValidators.h"

QTEST_MAIN (TestValidators)

TestValidators::TestValidators(QObject *parent) :
  QObject(parent)
{
}

void TestValidators::cleanupTestCase ()
{
}

void TestValidators::initTestCase ()
{
  const QString NO_ERROR_REPORT_LOG_FILE;
  const bool DEBUG_FLAG = false;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE);
  w.show ();
}

void TestValidators::testDateTime ()
{
  int pos;

  DlgValidatorDateTime validator (COORD_SCALE_LOG,
                                  COORD_UNITS_DATE_YEAR_MONTH_DAY,
                                  COORD_UNITS_TIME_HOUR_MINUTE_SECOND);

  QString date ("2015/01/02");
  QString time ("01:02:03");
  QString dateTime ("2015/01/02 01:02:03");
  QString dateTimePm ("2015/01/02 01:02:03 PM");

  QVERIFY (validator.validate (date,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (time,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (dateTime,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (dateTimePm,
                               pos) == QValidator::Acceptable);
}

void TestValidators::testDegreesMinutesSeconds ()
{
  int pos;

  DlgValidatorDegreesMinutesSeconds validator (COORD_SCALE_LOG);

  QString degrees ("180");
  QString degreesMinutes ("180 10");
  QString degreesMinutesSeconds ("180 10 20");

  QVERIFY (validator.validate (degrees,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (degreesMinutes,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (degreesMinutesSeconds,
                               pos) == QValidator::Acceptable);
}

void TestValidators::testNumber ()
{
  int pos;

  DlgValidatorNumber validator (COORD_SCALE_LOG);

  QString integer ("1");
  QString real ("1.1");
  QString realBad ("1.1.");

  QVERIFY (validator.validate (integer,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (real,
                               pos) == QValidator::Acceptable);
  QVERIFY (validator.validate (realBad,
                               pos) != QValidator::Acceptable);
}
