#include <iostream>
#include "Logger.h"
#include "MainWindow.h"
#include <map>
#include <qmath.h>
#include <QtTest/QtTest>
#include "Spline.h"
#include "SplinePair.h"
#include <sstream>
#include "Test/TestSpline.h"

QTEST_MAIN (TestSpline)

using namespace std;

const QString WEBPAGE ("https://tools.timodenk.com/cubic-spline-interpolation");

// Flags to enable extra information for investigating splines
//#define SHOWCOEFFICIENTS 1
//#define GNUPLOT 1

const int NUM_ITERATIONS = 24;

TestSpline::TestSpline(QObject *parent) :
  QObject(parent)
{
}

void TestSpline::cleanupTestCase ()
{

}

bool TestSpline::coefCheckX (const vector<double> &t,
#ifdef SHOWCOEFFICIENTS
                             const vector<SplinePair> &xy,
#else
                             const vector<SplinePair> & /* xy */,
#endif
                             const Spline &s) const
{
  unsigned int i;
  double aUntranslated = 0, bUntranslated = 0, cUntranslated = 0, dUntranslated = 0;

  // X coordinate fit
#ifdef SHOWCOEFFICIENTS
  cout << endl
       << "(t,x) inputs to be copied to " << WEBPAGE.toLatin1().data()
       << endl;
  for (i = 0; i < t.size(); i++) {
    cout << t[i] << "   " << xy[i].x() << endl;
  }
  cout << endl
       << "x=d*(t-ti)^3+c*(t-ti)^2+b*(t-ti)+a natural cubic spline results to be used in this code"
       << endl;
  for (i = 0; i < t.size() - 1; i++) {
    coefShow ("x =",
              "(t-ti)",
              t[i],
              t[i+1],
              s.m_elements[i].a().x(),
              s.m_elements[i].b().x(),
              s.m_elements[i].c().x(),
              s.m_elements[i].d().x());
  }
  cout << endl
       << "x=d*t^3+c*t^2+b*t+a outputs to be compared to results from " << WEBPAGE.toLatin1().data()
       << endl;
#endif
  for (i = 0; i < t.size() - 1; i++) {
    s.computeUntranslatedCoefficients (s.m_elements[i].a().x(),
                                       s.m_elements[i].b().x(),
                                       s.m_elements[i].c().x(),
                                       s.m_elements[i].d().x(),
                                       t[i],
                                       aUntranslated,
                                       bUntranslated,
                                       cUntranslated,
                                       dUntranslated);
#ifdef SHOWCOEFFICIENTS
    coefShow ("x =",
              "t",
              t[i],
              t[i+1],
              aUntranslated,
              bUntranslated,
              cUntranslated,
              dUntranslated);
#endif
  }

  // Spot check the (arbitrarily chosen) final row with results from the WEBPAGE
  bool success = true;
  success &= (qAbs (aUntranslated - -8.3608) < 8.3608 / 10000.0);
  success &= (qAbs (bUntranslated - 4.2505) < 4.2505 / 10000.0);
  success &= (qAbs (cUntranslated - -0.63092) < 0.63092 / 10000.0);
  success &= (qAbs (dUntranslated - 0.035051) < 0.035051 / 10000.0);

  return success;
}

bool TestSpline::coefCheckY (const vector<double> &t,
#ifdef SHOWCOEFFICIENTS
                             const vector<SplinePair> &xy,
#else
                             const vector<SplinePair> & /* xy */,
#endif
                             const Spline &s) const
{
  unsigned int i;
  double aUntranslated = 0, bUntranslated = 0, cUntranslated = 0, dUntranslated = 0;

  // Y coordinate fit
#ifdef SHOWCOEFFICIENTS
  cout << endl
       << "(t,y) inputs to be copied to " << WEBPAGE.toLatin1().data()
       << endl;
  for (i = 0; i < xy.size(); i++) {
    cout << t[i] << "   " << xy[i].y() << endl;
  }
  cout << endl
       << "y=d*(t-ti)^3+c*(t-ti)^2+b*(t-ti)+a natural cubic spline results to be used in this code"
       << endl;
  for (i = 0; i < xy.size() - 1; i++) {
    coefShow ("y =",
              "(t-ti)",
              t[i],
              t[i+1],
              s.m_elements[i].a().y(),
              s.m_elements[i].b().y(),
              s.m_elements[i].c().y(),
              s.m_elements[i].d().y());
  }
  cout << endl
       << "y=d*t^3+c*t^2+b*t+a outputs to be compared to results from " << WEBPAGE.toLatin1().data()
       << endl;
#endif
  for (i = 0; i < t.size() - 1; i++) {
    s.computeUntranslatedCoefficients (s.m_elements[i].a().y(),
                                       s.m_elements[i].b().y(),
                                       s.m_elements[i].c().y(),
                                       s.m_elements[i].d().y(),
                                       t[i],
                                       aUntranslated,
                                       bUntranslated,
                                       cUntranslated,
                                       dUntranslated);
#ifdef SHOWCOEFFICIENTS
    coefShow ("y =",
              "t",
              t[i],
              t[i+1],
              aUntranslated,
              bUntranslated,
              cUntranslated,
              dUntranslated);
#endif
  }

  // Spot check the (arbitrarily chosen) final row with results from the WEBPAGE
  bool success = true;
  success &= (qAbs (aUntranslated - -7.0) < 7.0 / 10000.0);
  success &= (qAbs (bUntranslated - 3.5667) < 3.5667 / 10000.0);
  success &= (qAbs (cUntranslated - -0.6) < 0.6 / 10000.0);
  success &= (qAbs (dUntranslated - 0.033333) < 0.033333 / 10000.0);

  return success;
}

void TestSpline::coefShow (const QString &leftHandSide,
                           const QString &independentVariable,
                           double tLow,
                           double tHigh,
                           double a,
                           double b,
                           double c,
                           double d) const
{
  cout << leftHandSide.toLatin1().data() << scientific
       << d << "*" << independentVariable.toLatin1().data() << "^3 + "
       << c << "*" << independentVariable.toLatin1().data() << "^2 + "
       << b << "*" << independentVariable.toLatin1().data() << " + "
       << a << " (" << tLow << "<t<" << tHigh << ")" << endl;

}

void TestSpline::initTestCase ()
{
  const bool NO_DROP_REGRESSION = false;
  const QString NO_ERROR_REPORT_LOG_FILE;
  const QString NO_REGRESSION_OPEN_FILE;
  const bool NO_GNUPLOT_LOG_FILES = false;
  const bool NO_REGRESSION_IMPORT = false;
  const bool NO_RESET = false;
  const bool NO_EXPORT_ONLY = false;
  const bool NO_EXPORT_IMAGE_ONLY = false;
  const QString NO_EXPORT_IMAGE_EXTENSION;
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
                NO_EXPORT_IMAGE_ONLY,
                NO_EXPORT_IMAGE_EXTENSION,                
                NO_LOAD_STARTUP_FILES,
                NO_COMMAND_LINE);
  w.show ();
}

void TestSpline::testCoefficientsFromOrdinals ()
{
  bool success = true;
  vector<double> t;
  vector<SplinePair> xy;

  // Input data for testSharpTransition
  xy.push_back (SplinePair (0.1, 1.0));
  xy.push_back (SplinePair (0.5, 1.0));
  xy.push_back (SplinePair (0.8, 1.0));
  xy.push_back (SplinePair (1.0, 0.5));
  xy.push_back (SplinePair (1.01, 0));
  xy.push_back (SplinePair (1.5, 0.0));
  xy.push_back (SplinePair (2.0, 0.0));

  int counter = 0;
  vector<SplinePair>::const_iterator itr;
  for (itr = xy.begin(); itr != xy.end(); itr++) {
    t.push_back (counter++);
  }

  // Generate the spline
  Spline s (t, xy);

  success &= coefCheckX (t,
                         xy,
                         s);
  success &= coefCheckY (t,
                         xy,
                         s);

  QVERIFY(success);
}

void TestSpline::testSharpTransition ()
{
  const int NUM_T = 60;
  const double SPLINE_EPSILON = 0.01;

  map<double, bool> xMerged; // Preserve order

  bool success = true;

  vector<double> t;
  vector<SplinePair> xyBefore;

  // Values with a sharp transition that can trigger overlap (=not a function)
  xyBefore.push_back (SplinePair (0.1, 1.0));
  xyBefore.push_back (SplinePair (0.5, 1.0));
  xyBefore.push_back (SplinePair (0.8, 1.0));
  xyBefore.push_back (SplinePair (1.0, 0.5));
  xyBefore.push_back (SplinePair (1.01, 0));
  xyBefore.push_back (SplinePair (1.5, 0.0));
  xyBefore.push_back (SplinePair (2.0, 0.0));

  // Copy x values into t vector and initial version of xMerged vector
  vector<SplinePair>::const_iterator itrB;
  for (itrB = xyBefore.begin(); itrB != xyBefore.end(); itrB++) {
    const SplinePair &pair = *itrB;
    t.push_back (pair.x());
    xMerged [pair.x ()] = true;
  }

  // Merge many more plotting points into xMerged
  double tStart = t[0];
  double tStop = t[t.size() - 1];
  for (int i = 0; i <= NUM_T; i++) {
    double t = tStart + (double) i * (tStop - tStart) / (double) NUM_T;

    if (xMerged.find (t) == xMerged.end ()) {
      xMerged [t] = true;
    }
  }

  // Generate the spline
  Spline s (t, xyBefore, SPLINE_DISABLE_T_CHECK);

  // Plot the points after generating the spline
  vector<SplinePair> xyAfter;
  map<double, bool>::const_iterator itrX;
  for (itrX = xMerged.begin(); itrX != xMerged.end(); itrX++) {
    double x = itrX->first;
    SplinePair pair = s.interpolateCoeff (x);
    xyAfter.push_back (pair);
  }

#ifdef GNUPLOT
  cout << "set datafile missing \"?\"" << endl;
  cout << "plot \"gnuplot.in\" using 1:2 with linespoints, \"gnuplot.in\" using 1:3 with lines" << endl;
#endif

  // Output the merged before/after curves
  map<double, bool>::const_iterator itrM;
  for (itrM = xMerged.begin(); itrM != xMerged.end(); itrM++) {
    double x = itrM->first;

    string yB = "?", yA = "?";

    vector<SplinePair>::iterator itrB;
    for (itrB = xyBefore.begin(); itrB != xyBefore.end(); itrB++) {
      if (itrB->x() == x) {
        ostringstream osB;
        osB << itrB->y();
        yB = osB.str();
        break;
      }
    }

    vector<SplinePair>::iterator itrA;
    for (itrA = xyAfter.begin(); itrA != xyAfter.end(); itrA++) {
      if (itrA->x() == x) {
        ostringstream osA;
        osA << itrA->y();
        yA = osA.str();
        break;
      }
    }

    if (itrB != xyBefore.end() &&
        itrA != xyAfter.end()) {

      // This x value has y values from both before and after that we can compare for success
      double yBefore = itrB->y();
      double yAfter = itrA->y();
      if (qAbs (yBefore - yAfter) > SPLINE_EPSILON) {
        success = false;
      }
    }

#ifdef GNUPLOT
    cout << x << ", " << yB << ", " << yA << endl;
#endif
  }

  QVERIFY (success);
}

void TestSpline::testSplinesAsControlPoints ()
{
  const int T_START = 1, T_STOP = 7;
  const double SPLINE_EPSILON = 0.01;
  const int NUM_T = 60;

  bool success = true;

  vector<double> t;
  vector<SplinePair> xy;
  
  // Independent variable are evenly spaced
  t.push_back (T_START);
  t.push_back (2);
  t.push_back (3);
  t.push_back (4);
  t.push_back (5);
  t.push_back (6);
  t.push_back (T_STOP);

  // Simple curve, with x values tweaked slightly (from even spacing) to make the test data more stressing
  xy.push_back (SplinePair (1, 0.22));
  xy.push_back (SplinePair (1.8, 0.04));
  xy.push_back (SplinePair (3.2, -0.13));
  xy.push_back (SplinePair (4.3, -0.17));
  xy.push_back (SplinePair (5, -0.04));
  xy.push_back (SplinePair (5.8, 0.09));
  xy.push_back (SplinePair (7, 0.11));

  Spline s (t, xy);

  for (int i = 0; i <= NUM_T; i++) {
    double t = T_START + (double) i * (T_STOP - T_START) / (double) NUM_T;
    SplinePair spCoeff = s.interpolateCoeff (t);
    SplinePair spBezier = s.interpolateControlPoints (t);

    double xCoeff = spCoeff.x();
    double yCoeff = spCoeff.y();
    double xControl = spBezier.x();
    double yControl = spBezier.y();

    if (qAbs (xCoeff - xControl) > SPLINE_EPSILON) {
      success = false;
    }

    if (qAbs (yCoeff - yControl) > SPLINE_EPSILON) {
      success = false;
    }
  }

  QVERIFY (success);
}
