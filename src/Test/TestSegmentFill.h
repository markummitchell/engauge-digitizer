#ifndef TEST_SEGMENT_H
#define TEST_SEGMENT_H

#include <QObject>

/// Unit test of segment fill feature
class TestSegmentFill : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestSegmentFill(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testFindSegments ();

};

#endif // TEST_SEGMENT_H
