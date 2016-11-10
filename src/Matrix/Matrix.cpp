/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "EngaugeAssert.h"
#include "Matrix.h"

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

int Matrix::cols () const
{
  return m_cols;
}

double Matrix::determinant () const
{
  ENGAUGE_ASSERT (m_rows == m_cols);

  if (m_rows == 1) {

    return m_vector [0];

  } else {

    const int COL = 0; // We arbitrarily iterate through the first column

    // This is a recursive algorithm
    double sum = 0.0;
    double multiplier = +1;
    for (int row = 0; row < m_rows; row++) {
      Matrix min = minorReduced (row, COL);
      sum += multiplier * get (row, COL) * min.determinant ();
      multiplier *= -1.0;
    }

    return sum;
  }
}

int Matrix::fold2dIndexes (int row, int col) const
{
  return row * m_cols + col;
}

double Matrix::get (int row, int col) const
{
  return m_vector [fold2dIndexes (row, col)];
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

Matrix Matrix::inverse () const
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

    // Inverse is the adjoint divided by the determinant
    for (row = 0; row < m_rows; row++) {
      for (col = 0; col < m_cols; col++) {
        inv.set (row, col, adjoint.get (row, col) / determ);
      }
    }
  } else {
    inv.set (0, 0, 1.0 / get (0, 0));
  }

  return inv;
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
