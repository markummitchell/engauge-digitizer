#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "Matrix.h"
#include <QObject>

/// Unit tests of matrix
class TestMatrix : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestMatrix(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testDeterminant ();

private:

};

#endif // TEST_MATRIX_H
