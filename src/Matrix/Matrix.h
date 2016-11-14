/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QVector>

/// Matrix class that supports arbitrary NxN size
class Matrix
{
public:
  /// Simple constructor of square matrix with initialization to identity matrix
  Matrix(int N);

  /// Simple constructor of rectangular matrix with initialization to zero matrix
  Matrix (int rows, int cols);
  
  /// Copy constructor
  Matrix (const Matrix &other);

  /// Assignment operator
  Matrix &operator= (const Matrix &matrix);

  /// Width of matrix
  int cols () const;

  /// Return the determinant of this matrix
  double determinant () const;
  
  /// Return (row, col) element
  double get (int row, int col) const;

  /// Return the inverse of this matrix
  Matrix inverse () const;

  /// Return minor matrix which is the original with the specified row and column omitted. The name 'minor' is a reserved word
  Matrix minorReduced (int rowOmit, int colOmit) const;
  
  /// Multiplication operator with a matrix
  Matrix operator* (const Matrix &other) const;

  /// Multiplication operator with a vector
  QVector<double> operator* (const QVector<double> other) const;

  /// Height of matrix
  int rows () const;

  /// Set (row, col) element
  void set (int row, int col, double value);

  /// Dump matrix to a string
  QString toString () const;

  /// Return the transpose of the current matrix
  Matrix transpose () const;
  
private:
  Matrix();

  void addRowToAnotherWithScaling (int rowFrom,
                                   int rowTo,
                                   double factor);
  int fold2dIndexes (int row, int col) const;
  void initialize (int rows,
                   int cols);
  Matrix inverseCramersRule () const;
  Matrix inverseGaussianElimination () const;
  unsigned int leadingZeros (int row) const; // Number of leading zeros in the specified zero
  void normalizeRow (int rowToNormalize,
                     int colToNormalize);
  void switchRows (int row1,
                   int row2);

  int m_rows; // Height of matrix
  int m_cols; // Width of matrix
  QVector<double> m_vector;
};

#endif // MATRIX_H
