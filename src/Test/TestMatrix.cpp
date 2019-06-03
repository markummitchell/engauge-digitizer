#include "Logger.h"
#include "MainWindow.h"
#include <qmath.h>
#include <QtTest/QtTest>
#include "Test/TestMatrix.h"

QTEST_MAIN (TestMatrix)

const int SIGNIFICANT_DIGITS = 7;

TestMatrix::TestMatrix(QObject *parent) :
  QObject(parent)
{
}

void TestMatrix::cleanupTestCase ()
{
}

void TestMatrix::initTestCase ()
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

void TestMatrix::testDeterminant ()
{
  Matrix m (3);
  double a00 = 1, a01 = 2, a10 = 3, a11 = 4;
  
  m.set (0, 0, a00);
  m.set (0, 1, a01);
  m.set (1, 0, a10);
  m.set (1, 1, a11);
  QVERIFY ((m.determinant () == a00 * a11 - a01 * a10));
}

void TestMatrix::testInverse ()
{
  bool success = true;
  int row, col;
  
  // Try 3x3 matrix. The 3 rows would be parallel if we had ((1,2,3),(4,5,6),(7,8,9)) which means there
  // is no inverse so the last element is slightly tweaked
  Matrix before (3);
  int counter = 0;
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
    }
  }
  before.set (2, 2, 10);

  MatrixConsistent matrixConsistent;
  Matrix after = before.inverse (SIGNIFICANT_DIGITS,
                                 matrixConsistent);

  if (matrixConsistent != MATRIX_CONSISTENT) {
    success = false;
  } else {
    Matrix product = before * after;
    Matrix identity (3);
    for (row = 0; row < 3; row++) {
      for (col = 0; col < 3; col++) {
        if (qAbs (product.get (row, col) - identity.get (row, col)) > 0.00001) {
          success = false;
          break;
        }
      }
    }
  }

  QVERIFY (success);
}

void TestMatrix::testInverse2 ()
{
  bool success = true;
  int row, col;
  
  // Try 2x2 matrix
  Matrix before (2);
  before.set (0, 0, 2);
  before.set (0, 1, 1);
  before.set (1, 0, 1);
  before.set (1, 1, 1);

  MatrixConsistent matrixConsistent;
  Matrix after = before.inverse (SIGNIFICANT_DIGITS,
                                 matrixConsistent);

  if (matrixConsistent != MATRIX_CONSISTENT) {
    success = false;
  } else {
    Matrix product = before * after;
    Matrix identity (2);
    for (row = 0; row < 2; row++) {
      for (col = 0; col < 2; col++) {
        if (qAbs (product.get (row, col) - identity.get (row, col)) > 0.00001) {
          success = false;
          break;
        }
      }
    }
  }

  QVERIFY (success);
}

void TestMatrix::testMultiplyNonSquareMatrix ()
{
  bool success = true;
  int row, col;
  
  // Try 2x3 matrix with its own transpose
  Matrix before (2, 3);
  int counter = 0;
  for (row = 0; row < 2; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
    }
  }

  // Multiply by its transpose
  Matrix afterGot = before * before.transpose ();
  Matrix afterWanted (2);

  if (afterGot.rows () == afterWanted.rows () &&
      afterGot.cols () == afterWanted.cols ()) {

    afterWanted.set (0, 0, 1 * 1 + 2 * 2 + 3 * 3);
    afterWanted.set (0, 1, 1 * 4 + 2 * 5 + 3 * 6);
    afterWanted.set (1, 0, 4 * 1 + 5 * 2 + 6 * 3);
    afterWanted.set (1, 1, 4 * 4 + 5 * 5 + 6 * 6);

    for (row = 0; row < 2; row++) {
      for (col = 0; col < 2; col++) {
        if (qAbs (afterWanted.get (row, col) - afterGot.get (row, col)) > 0.0001) {
          success = false;
          break;
        }
      }
    }
  } else {
    success = false;
  }

  QVERIFY (success);
}

void TestMatrix::testMultiplyNonSquareMatrixAndVector ()
{
  bool success = true;
  int row, col;
  
  // Try 2x3 matrix and 3x1 vector
  Matrix before (2, 3);
  QVector<double> vec (3);
  int counter = 0;
  for (row = 0; row < 2; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
      vec [col] = col + 1;
    }
  }

  // Multiply by itself
  QVector<double> afterGot = before * vec;
  QVector<double> afterWanted (2);

  if (afterGot.size () == afterWanted.size ()) {

    afterWanted [0] = 1 * 1 + 2 * 2 + 3 * 3;
    afterWanted [1] = 4 * 1 + 5 * 2 + 6 * 3;

    for (row = 0; row < 2; row++) {
      if (qAbs (afterWanted [row] - afterGot [row]) > 0.0001) {
          success = false;
          break;
      }
    }
  } else {
    success = false;
  }

  QVERIFY (success);
}

void TestMatrix::testMultiplySquareMatrix ()
{
  bool success = true;
  int row, col;
  
  // Try 3x3 matrix
  Matrix before (3);
  int counter = 0;
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
    }
  }

  // Multiply by itself
  Matrix afterGot = before * before;
  Matrix afterWanted (3);

  if (afterGot.rows() == afterWanted.rows() &&
      afterGot.cols() == afterWanted.cols()) {

    afterWanted.set (0, 0, 1 * 1 + 2 * 4 + 3 * 7);
    afterWanted.set (0, 1, 1 * 2 + 2 * 5 + 3 * 8);
    afterWanted.set (0, 2, 1 * 3 + 2 * 6 + 3 * 9);
    afterWanted.set (1, 0, 4 * 1 + 5 * 4 + 6 * 7);
    afterWanted.set (1, 1, 4 * 2 + 5 * 5 + 6 * 8);
    afterWanted.set (1, 2, 4 * 3 + 5 * 6 + 6 * 9);
    afterWanted.set (2, 0, 7 * 1 + 8 * 4 + 9 * 7);
    afterWanted.set (2, 1, 7 * 2 + 8 * 5 + 9 * 8);
    afterWanted.set (2, 2, 7 * 3 + 8 * 6 + 9 * 9);

    for (row = 0; row < 3; row++) {
      for (col = 0; col < 3; col++) {
        if (qAbs (afterWanted.get (row, col) - afterGot.get (row, col)) > 0.0001) {
          success = false;
          break;
        }
      }
    }
  } else {
    success = false;
  }

  QVERIFY (success);
}

void TestMatrix::testMultiplySquareMatrixAndVector ()
{
  bool success = true;
  int row, col;
  
  // Try 3x3 matrix and 3x1 vector
  Matrix before (3);
  QVector<double> vec (3);
  int counter = 0;
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
    }
    vec [row] = row + 1;
  }

  // Multiply by itself
  QVector<double> afterGot = before * vec;
  QVector<double> afterWanted (3);

  if (afterGot.size() == afterWanted.size()) {

    afterWanted [0] = 1 * 1 + 2 * 2 + 3 * 3;
    afterWanted [1] = 4 * 1 + 5 * 2 + 6 * 3;
    afterWanted [2] = 7 * 1 + 8 * 2 + 9 * 3;

    for (row = 0; row < 3; row++) {
      if (qAbs (afterWanted [row] - afterGot [row]) > 0.0001) {
          success = false;
          break;
      }
    }
  } else {
    success = false;
  }

  QVERIFY (success);
}  

void TestMatrix::testTranspose ()
{
  bool success = true;
  int row, col;
  
  // Try 3x3 matrix
  Matrix before (3);
  int counter = 0;
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      before.set (row, col, ++counter);
    }
  }

  Matrix after = before.transpose ();
  for (row = 0; row < 3; row++) {
    for (col = 0; col < 3; col++) {
      if (before.get (row, col) != after.get (col, row)) {
        success = false;
        break;
      }
    }
  }
  
  QVERIFY (success);
}
