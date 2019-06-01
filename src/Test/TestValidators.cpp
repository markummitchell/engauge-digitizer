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
  const bool NO_DROP_REGRESSION = false;
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool NO_EXPORT_ONLY = false;
  const bool NO_EXTRACT_IMAGE_ONLY = false;
  const QString NO_EXTRACT_IMAGE_EXTENSION;
  const bool DEBUG_FLAG = false;
  const QStringList NO_LOAD_STARTUP_FILES;
  const QStringList NO_COMMAND_LINE;  

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow w (NO_ERROR_REPORT_LOG_FILE,
                NO_REGRESSION_OPEN_FILE,
                NO_DROP_REGRESSION,
                NO_REGRESSION_IMPORT,
                NO_GNUPLOT_LOG_FILES,
                NO_RESET,
                NO_EXPORT_ONLY,
                NO_EXTRACT_IMAGE_ONLY,
                NO_EXTRACT_IMAGE_EXTENSION,                
                NO_LOAD_STARTUP_FILES,
                NO_COMMAND_LINE);
  w.show ();
}

bool TestValidators::stateDateTime (const QString &string,
                                    QValidator::State expectedState)
{
  int pos;

  DlgValidatorDateTime validator (COORD_SCALE_LOG,
                                  COORD_UNITS_DATE_YEAR_MONTH_DAY,
                                  COORD_UNITS_TIME_HOUR_MINUTE_SECOND);

  QString stringLocal = string;
  return (validator.validate (stringLocal,
                              pos) == expectedState);
}

bool TestValidators::stateDegreesMinutesSeconds (const QString &string,
                                                 QValidator::State expectedState)
{
  int pos;

  DlgValidatorDegreesMinutesSeconds validator (COORD_SCALE_LOG);

  QString stringLocal = string;
  return (validator.validate (stringLocal,
                               pos) == expectedState);
}

bool TestValidators::stateNumber(const QString &string,
                                 QValidator::State expectedState)
{
  int pos;
  const QLocale locale;

  DlgValidatorNumber validator (COORD_SCALE_LOG,
                                locale);

  QString stringLocal = string;
  return (validator.validate (stringLocal,
                               pos) == expectedState);
}

void TestValidators::testDateTimeDate ()
{
  QVERIFY (stateDateTime ("2015/01/02", QValidator::Acceptable));
}

void TestValidators::testDateTimeDateTime ()
{
  QVERIFY (stateDateTime ("2015/01/02 01:02:03", QValidator::Acceptable));
}

void TestValidators::testDateTimeDateTimePm ()
{
  QVERIFY (stateDateTime ("2015/01/02 01:02:03 PM", QValidator::Acceptable));
}

void TestValidators::testDateTimeTime ()
{
  QVERIFY (stateDateTime ("01:02:03", QValidator::Acceptable));
}

void TestValidators::testDegreesMinutesSecondsDegrees ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180", QValidator::Acceptable));
}

void TestValidators::testDegreesMinutesSecondsDegreesMinutes ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180 10", QValidator::Acceptable));
}

void TestValidators::testDegreesMinutesSecondsDegreesMinutesSeconds ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180 10 20", QValidator::Acceptable));
}

void TestValidators::testNumberInteger ()
{
  QVERIFY (stateNumber ("1", QValidator::Acceptable));
}

void TestValidators::testNumberReal ()
{
  QVERIFY (stateNumber ("1.1", QValidator::Acceptable));
}

void TestValidators::testNumberRealBad ()
{
  QVERIFY (stateNumber ("1.1.", QValidator::Invalid));
}
