#ifndef TEST_FORMATS_H
#define TEST_FORMATS_H

#include <QObject>
#include <QValidator>

/// Unit tests of formats
class TestFormats : public QObject
{
  Q_OBJECT
 public:
  /// Single constructor
  explicit TestFormats(QObject *parent = 0);

 signals:

 private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testDateTimeMdy ();
  void testDateTimeMdy0 ();
  void testDateTimeMdy01 ();
  void testDateTimeMdy01Slash ();
  void testDateTimeMdy01Slash0 ();
  void testDateTimeMdy01Slash02 ();
  void testDateTimeMdy01Slash02Slash ();
  void testDateTimeMdy01Slash02Slash2 ();
  void testDateTimeMdy01Slash02Slash20 ();
  void testDateTimeMdy01Slash02Slash202 ();
  void testDateTimeMdy01Slash02Slash2020 ();    
  void testDateTimeMdy01Slash02Slash2020Space ();
  void testDateTimeMdy01Slash02Slash2020Space0 ();
  void testDateTimeMdy01Slash02Slash2020Space01 ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon0 ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02 ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02Colon ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02Colon0 ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03 ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03Space ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03SpaceA ();
  void testDateTimeMdy01Slash02Slash2020Space01Colon02Colon03SpaceAM ();
  void testDateTimeYmd ();
  void testDateTimeYmd2 ();
  void testDateTimeYmd20 ();
  void testDateTimeYmd202 ();
  void testDateTimeYmd2020 ();
  void testDateTimeYmd2020Slash ();
  void testDateTimeYmd2020Slash0 ();
  void testDateTimeYmd2020Slash01 ();
  void testDateTimeYmd2020Slash01Slash ();
  void testDateTimeYmd2020Slash01Slash0 ();
  void testDateTimeYmd2020Slash01Slash02 ();
  void testDateTimeYmd2020Slash01Slash02Space ();
  void testDateTimeYmd2020Slash01Slash02Space0 ();
  void testDateTimeYmd2020Slash01Slash02Space01 ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon0 ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02 ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02Colon ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02Colon0 ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03 ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03Space ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03SpaceA ();
  void testDateTimeYmd2020Slash01Slash02Space01Colon02Colon03SpaceAM ();  
  void testDegreesMinutesSeconds ();
  void testDegreesMinutesSeconds180 ();
  void testDegreesMinutesSeconds180Space ();
  void testDegreesMinutesSeconds180Space10 ();
  void testDegreesMinutesSeconds180Space10Space ();
  void testDegreesMinutesSeconds180Space10Space20 ();

 private:
  bool stateDegreesMinutesSeconds (const QString &string, QValidator::State stateExpected);
  bool stateMonthDayYearHourMinuteSecond (const QString &string, QValidator::State stateExpected);  
  bool stateYearMonthDayHourMinuteSecond (const QString &string, QValidator::State stateExpected);

};

#endif // TEST_FORMATS_H
