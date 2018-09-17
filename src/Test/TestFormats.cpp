#include "FormatDateTime.h"
#include "FormatDegreesMinutesSecondsBase.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QtTest/QtTest>
#include "Test/TestFormats.h"

QTEST_MAIN (TestFormats)

TestFormats::TestFormats(QObject *parent) :
  QObject(parent)
{
}

void TestFormats::cleanupTestCase ()
{
}

void TestFormats::initTestCase ()
{
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

bool TestFormats::stateDegreesMinutesSeconds (const QString &string, QValidator::State stateExpected)
{
  FormatDegreesMinutesSecondsBase format;
  double value;
  bool success = (stateExpected == format.parseInput (string,
                                                      value));
  return success;
}

bool TestFormats::stateYearMonthDayHourMinuteSecond (const QString &string, QValidator::State stateExpected)
{
  FormatDateTime format;
  double value;
  bool success = (stateExpected == format.parseInput (COORD_UNITS_DATE_YEAR_MONTH_DAY,
                                                      COORD_UNITS_TIME_HOUR_MINUTE_SECOND,
                                                      string,
                                                      value));
  return success;
}

void TestFormats::testDateTime ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("", QValidator::Intermediate));
}

void TestFormats::testDateTime2 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2", QValidator::Intermediate));
}

void TestFormats::testDateTime20 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("20", QValidator::Intermediate));
}

void TestFormats::testDateTime201 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("201", QValidator::Intermediate));
}

void TestFormats::testDateTime2015 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/0", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/0", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash02Space ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 ", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash02Space0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 0", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02Space01 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:0", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02Colon ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02:", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02Colon0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02:0", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02Colon03 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02:03", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02Colon03Space ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02:03 ", QValidator::Acceptable));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02Colon03SpaceA ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02:03 A", QValidator::Intermediate));
}

void TestFormats::testDateTime2015Slash01Slash02Space01Colon02Colon03SpaceAM ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2015/01/02 01:02:03 AM", QValidator::Acceptable));
}

void TestFormats::testDegreesMinutesSeconds ()
{
  QVERIFY (stateDegreesMinutesSeconds ("", QValidator::Intermediate));
}

void TestFormats::testDegreesMinutesSeconds180 ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180", QValidator::Acceptable));
}

void TestFormats::testDegreesMinutesSeconds180Space ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180 ", QValidator::Acceptable));
}

void TestFormats::testDegreesMinutesSeconds180Space10 ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180 10", QValidator::Acceptable));
}

void TestFormats::testDegreesMinutesSeconds180Space10Space ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180 10 ", QValidator::Acceptable));
}

void TestFormats::testDegreesMinutesSeconds180Space10Space20 ()
{
  QVERIFY (stateDegreesMinutesSeconds ("180 10 20", QValidator::Acceptable));
}
