#ifndef TEST_GRAPH_COORDS_H
#define TEST_GRAPH_COORDS_H

#include <QObject>

/// Unit tests of graph coordinate sanity checking
class TestGraphCoords : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestGraphCoords(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testThreeCollinearPoints ();
  void testThreeGoodPoints ();
  void testTwoPointsSharings ();
  void testTwoPointsSharingScreenCoords ();
};

#endif // TEST_GRAPH_COORDS_H
