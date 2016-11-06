#ifndef TEST_EXPORT_H
#define TEST_EXPORT_H

#include <QObject>

/// Unit test of Export classes
class TestExport : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestExport(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testLogExtrapolationFunctionsAll ();
};

#endif // TEST_EXPORT_H
