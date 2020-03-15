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

bool TestFormats::stateDegreesMinutesSeconds (const QString &string, QValidator::State stateExpected)
{
  FormatDegreesMinutesSecondsBase format;
  double value;
  bool success = (stateExpected == format.parseInput (string,
                                                      value));
  return success;
}

bool TestFormats::stateMonthDayYearHourMinuteSecond (const QString &string, QValidator::State stateExpected)
{
  FormatDateTime format;
  double value;
  bool success = (stateExpected == format.parseInput (COORD_UNITS_DATE_MONTH_DAY_YEAR,
                                                      COORD_UNITS_TIME_HOUR_MINUTE_SECOND,
                                                      string,
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

void TestFormats::testDateTimeMdy ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy0 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("0", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash0 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/0", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash20 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/20", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash202 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/202", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 ", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space0 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 0", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon0 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:0", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02Colon ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02:", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02Colon0 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02:0", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03 ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02:03", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03Space ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02:03 ", QValidator::Acceptable));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03SpaceA ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02:03 A", QValidator::Intermediate));
}

void TestFormats::testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03SpaceAM ()
{
  QVERIFY (stateMonthDayYearHourMinuteSecond ("01/02/2020 01:02:03 AM", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd20 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("20", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd202 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("202", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/0", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/0", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 ", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 0", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:0", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02Colon ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02:", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02Colon0 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02:0", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03 ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02:03", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03Space ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02:03 ", QValidator::Acceptable));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03SpaceA ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02:03 A", QValidator::Intermediate));
}

void TestFormats::testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03SpaceAM ()
{
  QVERIFY (stateYearMonthDayHourMinuteSecond ("2020/01/02 01:02:03 AM", QValidator::Acceptable));
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
