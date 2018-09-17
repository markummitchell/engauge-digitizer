/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H

#include <QString>
#include <QVector>

/// Indicates if matrix is consistent (i.e. has at least one solution)
enum MatrixConsistent {
  MATRIX_CONSISTENT,
  MATRIX_INCONSISTENT
};

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
  /// \param significantDigits Input value for calculating epsilon threshold for determinants
  ///                          that are so close to zero that matrix should be considered inconsistent.
  /// \param matrixConsistent Output flag indicating success or failure
  Matrix inverse (int significantDigits,
                  MatrixConsistent &matrixConsistent) const;

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
  Matrix inverseCramersRule (MatrixConsistent &matrixConsistent,
                             double epsilonThreshold) const;
  Matrix inverseGaussianElimination (int significantDigits,
                                     MatrixConsistent &matrixConsistent) const;
  unsigned int leadingZeros (int row) const; // Number of leading zeros in the specified zero
  void normalizeRow (int rowToNormalize,
                     int colToNormalize,
                     int significantDigits,
                     MatrixConsistent &matrixConsistent);
  void switchRows (int row1,
                   int row2);

  // Return true if value is sufficiently far from zero that we can divide by it as part of
  // calculating a matrix inverse. The epsilon threshold is proportional to the largest value in the
  // matrix since a good threshold of 1e-8 for matrix elements near 1 should be scaled to
  // 1e-18 for matrix elements near 1e-10
  bool valueFailsEpsilonTest (double value,
                              double epsilonThreshold) const;

  int m_rows; // Height of matrix
  int m_cols; // Width of matrix
  QVector<double> m_vector;
};

#endif // MATRIX_H
