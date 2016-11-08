/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "Matrix.h"

Matrix::Matrix (int N)
{
  m_N = N;
  m_vector.resize (N * N);
  for (int row = 0; row < N; row++) {
    for (int col = 0; col < N; col++) {
      if (row == col) {
        set (row, col, 1.0);
      } else {
        set (row, col, 0.0);
      }
    }
  }
}

Matrix::Matrix (const Matrix &other)
{
  m_N = other.N ();
  m_vector.resize (m_N * m_N);
  for (int row = 0; row < m_N; row++) {
    for (int col = 0; col < m_N; col++) {
      set (row, col, other.get (row, col));
    }
  }
}

double Matrix::determinant () const
{
  if (m_N == 1) {

    return m_vector [0];

  } else {

    const int COL = 0; // We arbitrarily iterate through the first column
    
    // This is a recursive algorithm
    double sum = 0.0;
    double multiplier = +1;
    for (int row = 0; row < m_N; row++) {
      Matrix min = minorReduced (row, COL);
      sum += multiplier * get (row, COL) * min.determinant ();
      multiplier *= -1.0;
    }

    return sum;
  }
}

Matrix &Matrix::operator= (const Matrix &other)
{
  m_N = other.N ();
  m_vector.resize (m_N * m_N);
  for (int row = 0; row < m_N; row++) {
    for (int col = 0; col < m_N; col++) {
      set (row, col, other.get (row, col));
    }
  }

  return *this;
}

int Matrix::fold2dIndexes (int row, int col) const
{
  return row * m_N + col;
}

double Matrix::get (int row, int col) const
{
  return m_vector [fold2dIndexes (row, col)];
}

Matrix Matrix::inverse () const
{
  int row, col;
  
  // Compute cofactor matrix
  Matrix cofactor (m_N);
  for (row = 0; row < m_N; row++) {
    double multiplier = 1.0;
    for (col = 0; col < m_N; col++) {
      Matrix min = minorReduced (row, col);
      double element = multiplier * min.determinant ();
      multiplier *= -1.0;
      cofactor.set (row, col, element);
    }
  }

  // Compute adjoint
  Matrix adjoint = cofactor.transpose ();

  double determ = determinant ();

  // Inverse is the adjoint divided by the determinant
  Matrix inv (m_N);
  for (row = 0; row < m_N; row++) {
    for (col = 0; col < m_N; col++) {
      inv.set (row, col, adjoint.get (row, col) / determ);
    }
  }

  return inv;
}

Matrix Matrix::minorReduced (int rowOmit, int colOmit) const
{
  Matrix outMinor (m_N - 1);
  int rowMinor = 0;
  for (int row = 0; row < m_N; row++) {
    
    if (row != rowOmit) {
      
      int colMinor = 0;
      for (int col = 0; col < m_N; col++) {

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

int Matrix::N () const
{
  return m_N;
}

Matrix Matrix::operator* (const Matrix &other) const
{
  Matrix out (m_N);

  for (int row = 0; row < m_N; row++) {
    for (int col = 0; col < m_N; col++) {
      double sum = 0;
      for (int index = 0; index < m_N; index++) {
        sum += get (row, index) * other.get (index, col);
      }
      out.set (row, col, sum);
    }
  }

  return out;
}

void Matrix::set (int row, int col, double value)
{
  m_vector [fold2dIndexes (row, col)] = value;
}

Matrix Matrix::transpose () const
{
  Matrix out (m_N);

  for (int row = 0; row < m_N; row++) {
    for (int col = 0; col < m_N; col++) {
      out.set (col, row, get (row, col));
    }
  }

  return out;
}
