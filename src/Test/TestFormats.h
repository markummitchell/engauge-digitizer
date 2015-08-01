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

  void testDateTime ();
  void testDateTime2 ();
  void testDateTime20 ();
  void testDateTime201 ();
  void testDateTime2015 ();
  void testDateTime2015Slash ();
  void testDateTime2015Slash0 ();
  void testDateTime2015Slash01 ();
  void testDateTime2015Slash01Slash ();
  void testDateTime2015Slash01Slash0 ();
  void testDateTime2015Slash01Slash02 ();
  void testDateTime2015Slash01Slash02Space ();
  void testDateTime2015Slash01Slash02Space0 ();
  void testDateTime2015Slash01Slash02Space01 ();
  void testDateTime2015Slash01Slash02Space01Colon ();
  void testDateTime2015Slash01Slash02Space01Colon0 ();
  void testDateTime2015Slash01Slash02Space01Colon02 ();
  void testDateTime2015Slash01Slash02Space01Colon02Colon ();
  void testDateTime2015Slash01Slash02Space01Colon02Colon0 ();
  void testDateTime2015Slash01Slash02Space01Colon02Colon03 ();
  void testDateTime2015Slash01Slash02Space01Colon02Colon03Space ();
  void testDateTime2015Slash01Slash02Space01Colon02Colon03SpaceA ();
  void testDateTime2015Slash01Slash02Space01Colon02Colon03SpaceAM ();
  void testDegreesMinutesSeconds ();
  void testDegreesMinutesSeconds180 ();
  void testDegreesMinutesSeconds180Space ();
  void testDegreesMinutesSeconds180Space10 ();
  void testDegreesMinutesSeconds180Space10Space ();
  void testDegreesMinutesSeconds180Space10Space20 ();

 private:
  bool stateDegreesMinutesSeconds (const QString &string, QValidator::State stateExpected);
  bool stateYearMonthDayHourMinuteSecond (const QString &string, QValidator::State stateExpected);

};

#endif // TEST_FORMATS_H
