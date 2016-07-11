#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <QCryptographicHash>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QList>
#include <qmath.h>
#include <QTextStream>
#include <QtTest/QtTest>
#include "Segment.h"
#include "SegmentFactory.h"
#include "Spline.h"
#include "SplinePair.h"
#include "Test/TestSegmentFill.h"

QTEST_MAIN (TestSegmentFill)

using namespace std;

TestSegmentFill::TestSegmentFill(QObject *parent) :
  QObject(parent)
{
}

void TestSegmentFill::cleanupTestCase ()
{

}

void TestSegmentFill::initTestCase ()
{
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool DEBUG_FLAG = false;
  const QStringList NO_LOAD_STARTUP_FILES;

  initializeLogging ("engauge_test",
                     "engauge_test.log",
                     DEBUG_FLAG);

  MainWindow m (NO_ERROR_REPORT_LOG_FILE,
                NO_REGRESSION_OPEN_FILE,
                NO_GNUPLOT_LOG_FILES,
                NO_REGRESSION_IMPORT,
                NO_RESET,
                NO_LOAD_STARTUP_FILES);
  m.show ();
}

void TestSegmentFill::testFindSegments()
{
  const bool NO_GNUPLOT = false;
  const bool NO_DLG = false;
  const QString OUT_FILE_ACTUAL ("../test/test_segment_fill.gnuplot_actual");
  const QString OUT_FILE_EXPECTED ("../test/test_segment_fill.gnuplot_expected");

  QList<Segment*> segments;

  // The relative paths in this method will fail unless the directory is correct
  QDir::setCurrent (QApplication::applicationDirPath());

  QImage img ("../samples/corners.png");

  QGraphicsScene *scene = new QGraphicsScene;
  SegmentFactory segmentFactory (*scene,
                                 NO_GNUPLOT);

  DocumentModelSegments modelSegments;

  segmentFactory.clearSegments (segments);

  // This will crash if dialog box appears since QApplication is not executing and therefore cannot process events
  segmentFactory.makeSegments (img,
                               modelSegments,
                               segments,
                               NO_DLG);

  // Open output file
  QFile out (OUT_FILE_ACTUAL);
  QTextStream outStr (&out);

  out.open(QIODevice::WriteOnly | QIODevice::Text);

  // Output to file
  for (int indexS = 0; indexS < segments.count(); indexS++) {
    Segment* segment = segments [indexS];

    QList<QPoint> points = segment->fillPoints (modelSegments);

    // Skip segments with only one point since they are apparently random
    if (points.count() > 1) {

      for (int indexP = 0; indexP < points.count(); indexP++) {
        QPoint point = points [indexP];
      
        // Output in gnuplot format for plotting. A space precedes each field. This can be plotted with
        //    plot "../test/test_segment_fill.gnuplot_actual" w lp
        outStr << point.x() << " " << point.y() << endl;
      }

      // Blank line between curves
      outStr << endl;
    }
  }

  out.close();

  // Hash values
  QCryptographicHash hashActual (QCryptographicHash::Sha1);
  QCryptographicHash hashExpected (QCryptographicHash::Sha1);
  QFile fileActual (OUT_FILE_ACTUAL);
  QFile fileExpected (OUT_FILE_EXPECTED);

  bool success = false;
  if (fileActual.open(QIODevice::ReadOnly) && fileExpected.open(QIODevice::ReadOnly)) {
    hashActual.addData (fileActual.readAll());
    hashExpected.addData (fileExpected.readAll());
    QByteArray signatureActual = hashActual.result();
    QByteArray signatureExpected = hashExpected.result();

    // Compare
    success = (signatureActual == signatureExpected);
  }

  QVERIFY (success);
}
