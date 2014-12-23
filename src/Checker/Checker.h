#ifndef CHECKER_H
#define CHECKER_H

#include <QColor>
#include <QGraphicsPolygonItem>
#include <QPolygonF>

class QPolygonF;
class Transformation;

/// L-shaped polygon that is drawn through the three axis points, to temporarily (usually) or permanently (rarely)
/// highlight the local up/down/left/right directions when all axis points have been defined. These checker are 
/// meant to make it apparent when a mistake has happened so the screen-to-graph transformation is 
/// currently wrong - since the expected up/down/left/right directions will be awry
class Checker : public QGraphicsPolygonItem
{
public:
  /// Constructor for DlgSettingsAxesChecker, which does not have an explicit transformation. The identity transformation is assumed
  Checker(const QPolygonF &polygon);

  /// Set method for line color. The color should be recognizable against the (typically) black axes lines
  void setLineColor (const QColor &lineColor);

private:
  Checker();

};

#endif // CHECKER_H
