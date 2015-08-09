#ifndef TEST_GRAPH_COORDS_H
#define TEST_GRAPH_COORDS_H

#include "DocumentModelCoords.h"
#include <QObject>

class CallbackUpdateTransform;

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

  void testAnyColumnsRepeatNo ();
  void testAnyColumnsRepeatYes ();
  void testThreeCollinearPointsNo ();
  void testThreeCollinearPointsYes ();

private:

  DocumentModelCoords m_modelCoords;
  CallbackUpdateTransform *m_callback;
};

#endif // TEST_GRAPH_COORDS_H
