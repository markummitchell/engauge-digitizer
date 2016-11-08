/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>

/// Matrix class that supports arbitrary NxN size
class Matrix
{
public:
  /// Simple constructor with initialization to identity matrix
  Matrix(int N);
  
  /// Copy constructor
  Matrix (const Matrix &other);

  /// Assignment operator
  Matrix &operator= (const Matrix &matrix);

  /// Return the determinant of this matrix
  double determinant () const;
  
  /// Return (row, col) element
  double get (int row, int col) const;

  /// Return the inverse of this matrix
  Matrix inverse () const;

  /// Return minor matrix which is the original with the specified row and column omitted. The name 'minor' is a reserved word
  Matrix minorReduced (int rowOmit, int colOmit) const;
  
  /// Height and width of matrix
  int N () const;
  
  /// Multiplication operator
  Matrix operator* (const Matrix &other) const;

  /// Set (row, col) element
  void set (int row, int col, double value);

  /// Return the transpose of the current matrix
  Matrix transpose () const;
  
private:
  Matrix();

  int fold2dIndexes (int row, int col) const;

  int m_N; // Height and width of matrix
  QVector<double> m_vector;
};

#endif // MATRIX_H
