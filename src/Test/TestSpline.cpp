#include "Logger.h"
#include "MainWindow.h"
#include <map>
#include <qmath.h>
#include <QtTest/QtTest>
#include "SplineMultiValued.h"
#include "SplinePair.h"
#include "SplineSingleValued.h"
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

bool TestSpline::coefCheckXVersusT (const vector<double> &t,
#ifdef SHOWCOEFFICIENTS
                                    const vector<SplinePair> &xy,
#else
                                    const vector<SplinePair> & /* xy */,
#endif
                                    const SplineAbstract &s,
                                    double aFinalX,
                                    double bFinalX,
                                    double cFinalX,
                                    double dFinalX) const
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

  // Spot check
  bool success = true;
  success &= (qAbs (aUntranslated - aFinalX) < qAbs (aFinalX) / 10000.0);
  success &= (qAbs (bUntranslated - bFinalX) < qAbs (bFinalX) / 10000.0);
  success &= (qAbs (cUntranslated - cFinalX) < qAbs (cFinalX) / 10000.0);
  success &= (qAbs (dUntranslated - dFinalX) < qAbs (dFinalX) / 10000.0);

  return success;
}

bool TestSpline::coefCheckYVersusT (const vector<double> &t,
#ifdef SHOWCOEFFICIENTS
                                    const vector<SplinePair> &xy,
#else
                                    const vector<SplinePair> & /* xy */,
#endif
                                    const SplineAbstract &s,
                                    double aFinalY,
                                    double bFinalY,
                                    double cFinalY,
                                    double dFinalY) const
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

  // Spot check
  bool success = true;
  success &= (qAbs (aUntranslated - aFinalY) < qAbs (aFinalY) / 10000.0);
  success &= (qAbs (bUntranslated - bFinalY) < qAbs (bFinalY) / 10000.0);
  success &= (qAbs (cUntranslated - cFinalY) < qAbs (cFinalY) / 10000.0);
  success &= (qAbs (dUntranslated - dFinalY) < qAbs (dFinalY) / 10000.0);

  return success;
}

bool TestSpline::coefCheckYVersusX (const vector<SplinePair> &xy,
                                    const SplineAbstract &s,
                                    double aFinalY,
                                    double bFinalY,
                                    double cFinalY,
                                    double dFinalY) const
{
  unsigned int i;
  double aUntranslated = 0, bUntranslated = 0, cUntranslated = 0, dUntranslated = 0;

  // Y coordinate fit
#ifdef SHOWCOEFFICIENTS
  cout << endl
       << "(x,y) inputs to be copied to " << WEBPAGE.toLatin1().data()
       << endl;
  for (i = 0; i < xy.size(); i++) {
    cout << xy[i].x() << "   " << xy[i].y() << endl;
  }
  cout << endl
       << "y=d*(x-xi)^3+c*(x-xi)^2+b*(x-xi)+a natural cubic spline results to be used in this code"
       << endl;
  for (i = 0; i < xy.size() - 1; i++) {
    coefShow ("y =",
              "(x-xi)",
              xy[i].x(),
              xy[i+1].x(),
              s.m_elements[i].a().y(),
              s.m_elements[i].b().y(),
              s.m_elements[i].c().y(),
              s.m_elements[i].d().y());
  }
  cout << endl
       << "y=d*x^3+c*x^2+b*x+a outputs to be compared to results from " << WEBPAGE.toLatin1().data()
       << endl;
#endif
  for (i = 0; i < xy.size() - 1; i++) {
    s.computeUntranslatedCoefficients (s.m_elements[i].a().y(),
                                       s.m_elements[i].b().y(),
                                       s.m_elements[i].c().y(),
                                       s.m_elements[i].d().y(),
                                       xy[i].x(),
                                       aUntranslated,
                                       bUntranslated,
                                       cUntranslated,
                                       dUntranslated);
#ifdef SHOWCOEFFICIENTS
    coefShow ("y =",
              "x",
              xy[i].x(),
              xy[i+1].x(),
              aUntranslated,
              bUntranslated,
              cUntranslated,
              dUntranslated);
#endif
  }

  // Spot check
  bool success = true;
  success &= (qAbs (aUntranslated - aFinalY) < qAbs (aFinalY) / 10000.0);
  success &= (qAbs (bUntranslated - bFinalY) < qAbs (bFinalY) / 10000.0);
  success &= (qAbs (cUntranslated - cFinalY) < qAbs (cFinalY) / 10000.0);
  success &= (qAbs (dUntranslated - dFinalY) < qAbs (dFinalY) / 10000.0);

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

void TestSpline::testCommonCoefficientsFromOrdinals (bool isSingle,
                                                     double aFinalX,
                                                     double bFinalX,
                                                     double cFinalX,
                                                     double dFinalX,
                                                     double aFinalY,
                                                     double bFinalY,
                                                     double cFinalY,
                                                     double dFinalY)
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
  SplineAbstract *s;
  if (isSingle) {
    s = new SplineSingleValued (t, xy);

    success &= coefCheckXVersusT (t,
                                  xy,
                                  *s,
                                  aFinalX,
                                  bFinalX,
                                  cFinalX,
                                  dFinalX);
    success &= coefCheckYVersusX (xy,
                                  *s,
                                  aFinalY,
                                  bFinalY,
                                  cFinalY,
                                  dFinalY);
  } else {
    s = new SplineMultiValued (t, xy);

    success &= coefCheckXVersusT (t,
                                  xy,
                                  *s,
                                  aFinalX,
                                  bFinalX,
                                  cFinalX,
                                  dFinalX);
    success &= coefCheckYVersusT (t,
                                  xy,
                                  *s,
                                  aFinalY,
                                  bFinalY,
                                  cFinalY,
                                  dFinalY);
  }

  delete s;

  QVERIFY(success);
}

void TestSpline::testCommonSharpTransition (bool isSingle)
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
  SplineAbstract *s;
  if (isSingle) {
    s = new SplineSingleValued (t, xyBefore, SPLINE_DISABLE_T_CHECK);
  } else {
    s = new SplineMultiValued (t, xyBefore, SPLINE_DISABLE_T_CHECK);
  }

  // Plot the points after generating the spline
  vector<SplinePair> xyAfter;
  map<double, bool>::const_iterator itrX;
  for (itrX = xMerged.begin(); itrX != xMerged.end(); itrX++) {
    double x = itrX->first;
    SplinePair pair = s->interpolateCoeff (x);
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

  delete s;

  QVERIFY (success);
}

void TestSpline::testCommonSplinesAsControlPoints (bool isSingle)
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

  SplineAbstract *s;
  if (isSingle) {
    s = new SplineSingleValued (t, xy);
  } else {
    s = new SplineMultiValued (t, xy);
  }

  for (int i = 0; i <= NUM_T; i++) {
    double t = T_START + (double) i * (T_STOP - T_START) / (double) NUM_T;
    SplinePair spCoeff = s->interpolateCoeff (t);
    SplinePair spBezier = s->interpolateControlPoints (t);

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

  delete s;

  QVERIFY (success);
}

void TestSpline::testMultiCoefficientsFromOrdinals ()
{
  // The (arbitrarily chosen) final row with results from the WEBPAGE, using inputs displayed by SHOWCOEFFICIENTS
  testCommonCoefficientsFromOrdinals (false,
                                      -8.3608,
                                      4.2505,
                                      -0.63092,
                                      0.035051,
                                      -7.0,
                                      3.566667,
                                      -0.6,
                                      0.033333);
}

void TestSpline::testMultiSharpTransition ()
{
  testCommonSharpTransition (false);
}

void TestSpline::testMultiSplinesAsControlPoints ()
{
  testCommonSplinesAsControlPoints (false);
}

//void TestSpline::testSingleCoefficientsFromOrdinals ()
//{
//  // The (arbitrarily chosen) final row with results from the WEBPAGE, using inputs displayed by SHOWCOEFFICIENTS
//  testCommonCoefficientsFromOrdinals (true,
//                                      -8.3608,
//                                      4.2505,
//                                      -0.63092,
//                                      0.035051,
//                                      -216.54,
//                                      339.25,
//                                      -173.23,
//                                      28.872);
//}

void TestSpline::testSingleSharpTransition ()
{
  testCommonSharpTransition (true);
}

void TestSpline::testSingleSplinesAsControlPoints ()
{
  testCommonSplinesAsControlPoints (true);
}
