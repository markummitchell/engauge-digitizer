#include "DocumentModelCoords.h"
#include "DocumentModelGeneral.h"
#include "Logger.h"
#include "MainWindow.h"
#include "MainWindowModel.h"
#include <map>
#include <qmath.h>
#include <QtTest/QtTest>
#include "Spline.h"
#include "SplineDrawer.h"
#include "SplinePair.h"
#include <sstream>
#include "Test/TestSplineDrawer.h"
#include "Transformation.h"

QTEST_MAIN (TestSplineDrawer)

using namespace std;

TestSplineDrawer::TestSplineDrawer(QObject *parent) :
  QObject(parent)
{
}

void TestSplineDrawer::cleanupTestCase ()
{

}

void TestSplineDrawer::initTestCase ()
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

bool TestSplineDrawer::testMultiValuedGeneric (const vector<SplinePair> &xy,
                                               const vector<bool> &isMultiValued) const
{
  bool success = true;
  vector<double> t;

  // Models
  DocumentModelCoords modelCoords;
  DocumentModelGeneral modelGeneral;
  MainWindowModel modelMainWindow;

  modelCoords.setCoordScaleXTheta (COORD_SCALE_LOG);
  modelCoords.setCoordScaleYRadius (COORD_SCALE_LINEAR);

  // Transformation
  Transformation trans;
  trans.setModelCoords (modelCoords,
                        modelGeneral,
                        modelMainWindow);
  QTransform matrixScreen (198.5  , 627.562, 55.625 ,
                           562.562, 562.562, 155.562,
                           1      , 1      , 1      );
  QTransform matrixGraph (0.001, 1.0, 0.0001,
                          0    , 0  , 30    ,
                          1    , 1  , 1     );
  trans.updateTransformFromMatrices (matrixScreen,
                                     matrixGraph);

  int counter = 0;
  vector<SplinePair>::const_iterator itr;
  for (itr = xy.begin(); itr != xy.end(); itr++) {
    t.push_back (counter++);
  }

  // Generate the spline
  Spline s (t, xy);

  SplineDrawer sd (trans);
  for (unsigned int segment = 0; segment < isMultiValued.size(); segment++) {
    if (isMultiValued [segment] != sd.segmentIsMultiValued (s,
                                                            xy.size(),
                                                            segment)) {
      success = false;
    }
  }

  return success;
}

void TestSplineDrawer::testMultiValuedLeadingOverlap ()
{
  vector<SplinePair> xy;
  vector<bool> isMultiValued;

  xy.push_back (SplinePair (198.388, 426.423)); isMultiValued.push_back (true);
  xy.push_back (SplinePair (198.531, 399.463)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (384.589, 263.384)); isMultiValued.push_back (true);
  xy.push_back (SplinePair (409.525, 250.684)); isMultiValued.push_back (true);
  xy.push_back (SplinePair (441.360, 535.685)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (484.557, 358.601)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (495.663, 454.633)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (527.411, 182.426)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (633.561, 155.353)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (756.603, 358.646)); // Last point has no corresponding segment

  bool success = testMultiValuedGeneric (xy,
                                         isMultiValued);

  QVERIFY (success);
}

void TestSplineDrawer::testMultiValuedTrailingOverlap ()
{
  vector<SplinePair> xy;
  vector<bool> isMultiValued;

  // Same data as testMultiValuedLeadingOverlap but horizontally flipped about x=(198+756)/2
  double maxPlusMin = 756.603 + 198.388;
  xy.push_back (SplinePair (maxPlusMin - 756.603, 358.646)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (maxPlusMin - 633.561, 155.353)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (maxPlusMin - 527.411, 182.426)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (maxPlusMin - 495.663, 454.633)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (maxPlusMin - 484.557, 358.601)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (maxPlusMin - 441.360, 535.685)); isMultiValued.push_back (true);
  xy.push_back (SplinePair (maxPlusMin - 409.525, 250.684)); isMultiValued.push_back (true);
  xy.push_back (SplinePair (maxPlusMin - 384.589, 263.384)); isMultiValued.push_back (false);
  xy.push_back (SplinePair (maxPlusMin - 198.531, 399.463)); isMultiValued.push_back (true);
  xy.push_back (SplinePair (maxPlusMin - 198.388, 426.423)); // Last point has no corresponding segment

  bool success = testMultiValuedGeneric (xy,
                                         isMultiValued);

  QVERIFY (success);
}
