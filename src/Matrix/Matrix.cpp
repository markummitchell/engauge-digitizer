/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Matrix.h"
#include <qmath.h>
#include <QTextStream>

Matrix::Matrix (int N)
{
  initialize (N, N);
}

Matrix::Matrix (int rows,
                int cols)
{
  initialize (rows, cols);
}

Matrix::Matrix (const Matrix &other)
{
  m_rows = other.rows();
  m_cols = other.cols();
  m_vector.resize (m_rows * m_cols);
  for (int row = 0; row < m_rows; row++) {
    for (int col = 0; col < m_cols; col++) {
      set (row, col, other.get (row, col));
    }
  }
}

Matrix &Matrix::operator= (const Matrix &other)
{
  m_rows = other.rows();
  m_cols = other.cols();
  m_vector.resize (m_rows * m_cols);
  for (int row = 0; row < m_rows; row++) {
    for (int col = 0; col < m_cols; col++) {
      set (row, col, other.get (row, col));
    }
  }

  return *this;
}

void Matrix::addRowToAnotherWithScaling (int rowFrom,
                                         int rowTo,
                                         double factor)
{
  for (int col = 0; col < cols (); col++) {
    double oldValueFrom = get (rowFrom, col);
    double oldValueTo = get (rowTo, col);
    double newValueTo = oldValueFrom * factor + oldValueTo;
    set (rowTo, col, newValueTo);
  }
}

int Matrix::cols () const
{
  return m_cols;
}

double Matrix::determinant () const
{
  ENGAUGE_ASSERT (m_rows == m_cols);

  double rtn;

  if (m_rows == 1) {

    rtn = m_vector [0];

  } else {

    const int COL = 0; // We arbitrarily iterate through the first column

    // This is a recursive algorithm
    rtn = 0.0;
    double multiplier = +1;
    for (int row = 0; row < m_rows; row++) {
      Matrix min = minorReduced (row, COL);
      rtn += multiplier * get (row, COL) * min.determinant ();
      multiplier *= -1.0;
    }
  }

  return rtn;
}

int Matrix::fold2dIndexes (int row, int col) const
{
  return row * m_cols + col;
}

double Matrix::get (int row, int col) const
{
  int foldedIndex = fold2dIndexes (row, col);
  return m_vector [foldedIndex];
}

void Matrix::initialize (int rows,
                         int cols)
{
  m_rows = rows;
  m_cols = cols;
  m_vector.resize (rows * cols);
  for (int row = 0; row < m_rows; row++) {
    for (int col = 0; col < m_cols; col++) {

      // Identity matrix for square matrix, otherwise zero matrix
      if (row == col && m_rows == m_cols) {
        set (row, col, 1.0);
      } else {
        set (row, col, 0.0);
      }
    }
  }
}

Matrix Matrix::inverse (int significantDigits,
                        MatrixConsistent &matrixConsistent) const
{
  // Set epsilon threshold for valueFailsEpsilonTest
  double maxValue = 0;
  for (int row = 0; row < m_rows; row++) {
    for (int col = 0; col < m_cols; col++) {
      double value = qAbs (get (row, col));
      if (value > maxValue) {
        maxValue = value;
      }
    }
  }

  // Available algorithms are inverseCramersRule and inverseGaussianElimination
  matrixConsistent = MATRIX_CONSISTENT;
  return inverseGaussianElimination (significantDigits,
                                     matrixConsistent);
}

Matrix Matrix::inverseCramersRule (MatrixConsistent & matrixConsistent,
                                   double epsilonThreshold) const
{
  ENGAUGE_ASSERT (m_rows == m_cols);

  Matrix inv (m_rows);
  int row, col;
  
  if (m_rows > 1) {

    // Compute cofactor matrix
    double multiplierStartForRow = 1.0;
    Matrix cofactor (m_rows);
    for (row = 0; row < m_rows; row++) {
      double multiplier = multiplierStartForRow;
      for (col = 0; col < m_cols; col++) {
        Matrix min = minorReduced (row, col);
        double element = multiplier * min.determinant ();
        multiplier *= -1.0;
        cofactor.set (row, col, element);
      }
      multiplierStartForRow *= -1.0;
    }

    // Compute adjoint
    Matrix adjoint = cofactor.transpose ();

    double determ = determinant ();
    if (valueFailsEpsilonTest (determ,
                               epsilonThreshold)) {
      matrixConsistent = MATRIX_INCONSISTENT;
      return inv;
    }

    // Inverse is the adjoint divided by the determinant
    for (row = 0; row < m_rows; row++) {
      for (col = 0; col < m_cols; col++) {
        inv.set (row, col, adjoint.get (row, col) / determ);
      }
    }
  } else {
    double denominator = get (0, 0);
    if (valueFailsEpsilonTest (denominator,
                               epsilonThreshold)) {
      matrixConsistent = MATRIX_INCONSISTENT;
      return inv;
    }
    inv.set (0, 0, 1.0 / denominator);
  }

  return inv;
}

Matrix Matrix::inverseGaussianElimination (int significantDigits,
                                           MatrixConsistent &matrixConsistent) const
{
  // From https://en.wikipedia.org/wiki/Gaussian_elimination

  int row, col, rowFrom, rowTo;
  Matrix inv (rows ());

  // Track the row switches that may or may not be performed below
  QVector<int> rowIndexes (rows ());
  for (row = 0; row < rows (); row++) {
    rowIndexes [row] = row;
  }

  // Create the working matrix and populate the left half. Number of columns in the working matrix is twice the number
  // of cols in this matrix, but we will not populate the right half until after the bubble sort below
  Matrix working (rows (), 2 * cols ());
  for (row = 0; row < rows (); row++) {
    for (col = 0; col < cols (); col++) {
      double value = get (row, col);
      working.set (row, col, value);
    }
  }

  // Simple bubble sort to rearrange the rows with 0 leading zeros at start, followed by rows with 1 leading zero at start, ...
  for (int row1 = 0; row1 < rows (); row1++) {
    for (int row2 = row1 + 1; row2 < rows (); row2++) {
      if (working.leadingZeros (row1) > working.leadingZeros (row2)) {
        working.switchRows (row1, row2);

        // Remember this switch
        int row1Index = rowIndexes [row1];
        int row2Index = rowIndexes [row2];
        rowIndexes [row1] = row2Index;
        rowIndexes [row2] = row1Index;
      }
    }
  }

  // Populate the right half now
  for (row = 0; row < rows (); row++) {
    for (col = cols (); col < 2 * cols (); col++) {
      int colIdentitySubmatrix = col - cols ();
      double value  = (row == colIdentitySubmatrix) ? 1 : 0;
      working.set (row, col, value);
    }
  }

  // Loop through the "from" row going down. This results in the lower off-diagonal terms becoming zero, in the left half
  for (rowFrom = 0; rowFrom < rows (); rowFrom++) {
    int colFirstWithNonZero = rowFrom;

    // In pathological situations we have (rowFrom, colFirstWithNonzero) = 0 in which case the solution cannot be obtained
    // so we exit
    if (working.get (rowFrom, colFirstWithNonZero) == 0) {
      matrixConsistent = MATRIX_INCONSISTENT;
      return inv;
    }

    // Normalize the 'from' row with first nonzero term set to 1
    working.normalizeRow (rowFrom, colFirstWithNonZero, significantDigits, matrixConsistent);
    if (matrixConsistent == MATRIX_INCONSISTENT) {
      return inv;
    }

    // Apply the 'from' row to all the 'to' rows
    for (rowTo = rowFrom + 1; rowTo < rows (); rowTo++) {

      if (working.get (rowTo, colFirstWithNonZero) != 0) {

        // We need to merge rowFrom and rowTo into rowTo
        double denominator = working.get (rowFrom, colFirstWithNonZero);
        double factor = -1.0 * working.get (rowTo, colFirstWithNonZero) / denominator;
        working.addRowToAnotherWithScaling (rowFrom, rowTo, factor);
      }
    }
  }

  // Loop through the "from" row doing up. This results in the upper off-diagonal terms becoming zero, in the left half
  for (rowFrom = rows () - 1; rowFrom >= 0; rowFrom--) {
    int colFirstWithNonZero = rowFrom; // This is true since we should have 1s all down the diagonal at this point

    // Normalize the 'from' row with diagonal term set to 1. The first term should be like 0.9999 or 1.0001 but we want exactly one
    MatrixConsistent matrixConsistent;
    working.normalizeRow (rowFrom, colFirstWithNonZero, significantDigits, matrixConsistent);
    if (matrixConsistent == MATRIX_INCONSISTENT) {
      return inv;
    }

    // Apply the 'from' row to all the 'to' rows
    for (rowTo = rowFrom - 1; rowTo >= 0; rowTo--) {

      if (working.get (rowTo, colFirstWithNonZero) != 0) {

        // We need to merge rowFro and rowTo into rowTo
        double denominator = working.get (rowFrom, colFirstWithNonZero);
        double factor = -1.0 * working.get (rowTo, colFirstWithNonZero) / denominator;
        working.addRowToAnotherWithScaling (rowFrom, rowTo, factor);
      }
    }
  }

  // Extract right half of rectangular matrix which is the inverse

  for (row = 0; row < working.rows (); row++) {

    int rowBeforeSort = rowIndexes [row];

    for (col = 0; col < working.rows (); col++) {
      int colRightHalf = col + inv.cols ();
      double value = working.get (rowBeforeSort, colRightHalf);
      inv.set (row, col, value);
    }
  }

  return inv;
}

unsigned int Matrix::leadingZeros (int row) const
{
  unsigned int sum = 0;
  for (int col = 0; col < cols (); col++) {
    if (get (row, col) != 0) {
      ++sum;
    }
  }

  return sum;
}

Matrix Matrix::minorReduced (int rowOmit, int colOmit) const
{
  ENGAUGE_ASSERT (m_rows == m_cols);

  Matrix outMinor (m_rows - 1);
  int rowMinor = 0;
  for (int row = 0; row < m_rows; row++) {
    
    if (row != rowOmit) {
      
      int colMinor = 0;
      for (int col = 0; col < m_cols; col++) {

        if (col != colOmit) {

          outMinor.set (rowMinor, colMinor, get (row, col));
          ++colMinor;
        }
      }
      ++rowMinor;
    }
  }

  return outMinor;
}

void Matrix::normalizeRow (int rowToNormalize,
                           int colToNormalize,
                           int significantDigits,
                           MatrixConsistent &matrixConsistent)
{
  double denominator = get (rowToNormalize, colToNormalize);

  // Epsilon is computed from smallest value in row
  double smallestAbsValue = 0;
  for (int col = 0; col < cols (); col++) {
    double absValue = qAbs (get (rowToNormalize, 0));
    if (col == 0 || absValue < smallestAbsValue) {
      smallestAbsValue = absValue;
    }
  }
  double epsilonThreshold = smallestAbsValue / qPow (10.0, significantDigits);

  if (valueFailsEpsilonTest (denominator,
                             epsilonThreshold)) {

    matrixConsistent = MATRIX_INCONSISTENT;

  } else {

    matrixConsistent = MATRIX_CONSISTENT;

    double factor = 1.0 / denominator;
    for (int col = 0; col < cols (); col++) {
      double value = get (rowToNormalize, col);
      set (rowToNormalize, col, factor * value);
    }
  }
}

Matrix Matrix::operator* (const Matrix &other) const
{
  ENGAUGE_ASSERT (m_cols == other.rows ());

  Matrix out (m_rows, other.cols ());

  for (int row = 0; row < m_rows; row++) {
    for (int col = 0; col < other.cols (); col++) {
      double sum = 0;
      for (int index = 0; index < m_cols; index++) {
        sum += get (row, index) * other.get (index, col);
      }
      out.set (row, col, sum);
    }
  }

  return out;
}

QVector<double> Matrix::operator* (const QVector<double> other) const
{
  ENGAUGE_ASSERT (m_cols == other.size ());

  QVector<double> out;
  out.resize (m_rows);
  for (int row = 0; row < m_rows; row++) {
    double sum = 0;
    for (int col = 0; col < m_cols; col++) {
      sum += get (row, col) * other [col];
    }

    out [row] = sum;
  }

  return out;
}

int Matrix::rows () const
{
  return m_rows;
}

void Matrix::set (int row, int col, double value)
{
  m_vector [fold2dIndexes (row, col)] = value;
}

void Matrix::switchRows (int row1,
                         int row2)
{
  // Switch rows
  for (int col = 0; col < cols (); col++) {
    double temp1 = get (row1, col);
    double temp2 = get (row2, col);
    set (row2, col, temp2);
    set (row1, col, temp1);
  }
}

QString Matrix::toString () const
{
  QString out;
  QTextStream str (&out);

  str << "(";
  for (int row = 0; row < rows (); row++) {
    if (row > 0) {
      str << ", ";
    }
    str << "(";
    for (int col = 0; col < cols (); col++) {
      if (col > 0) {
        str << ", ";
      }
      str << get (row, col);
    }
    str << ")";
  }
  str << ")";

  return out;
}

Matrix Matrix::transpose () const
{
  Matrix out (m_cols, m_rows);

  for (int row = 0; row < m_rows; row++) {
    for (int col = 0; col < m_cols; col++) {
      out.set (col, row, get (row, col));
    }
  }

  return out;
}

bool Matrix::valueFailsEpsilonTest (double value,
                                    double epsilonThreshold) const
{
  return qAbs (value) < qAbs (epsilonThreshold);
}
