#ifndef HIGHLIGHTS_POINT_H
#define HIGHLIGHTS_POINT_H

#include <QColor>
#include <QGraphicsPolygonItem>

/// Point that is drawn underneath an axis point to temporarily or permanently highlight the local up/down/left/right directions
/// when all axis points have been defined. These highlights are meant to make it apparent when a mistake has happened
/// so the screen-to-graph transformation is currently wrong - since the expected up/down/left/right directions will be awry
///
/// Positioning is entirely handled by the superclass.
class HighlightsPoint : public QGraphicsPolygonItem
{
public:
  /// Single constructor.
  HighlightsPoint();

  void setLineColor (const QColor &lineColor);

};

#endif // HIGHLIGHTS_POINT_H
