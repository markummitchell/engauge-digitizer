#ifndef TEST_ZOOM_TRANSITION_H
#define TEST_ZOOM_TRANSITION_H

#include <QObject>

/// Unit test of ZoomTransition class
class TestZoomTransition : public QObject
{
  Q_OBJECT
public:
  /// Single constructor.
  explicit TestZoomTransition(QObject *parent = 0);

signals:

private slots:
  void cleanupTestCase ();
  void initTestCase ();

  void testInAtClosestEnum ();
  void testInBeforeClosestFromEnum ();
  void testInBeforeClosestFromFill ();  
  void testOutAtFarthestEnum ();
  void testOutBeforeFarthestFromEnum ();
  void testOutBeforeFarthestFromFill ();  
};

#endif // TEST_ZOOM_TRANSITION_H

