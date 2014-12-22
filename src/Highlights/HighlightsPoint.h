#ifndef HIGHLIGHTS_POINT_H
#define HIGHLIGHTS_POINT_H

#include <QColor>
#include <QGraphicsPolygonItem>

class Transformation;

/// Point that is drawn underneath an axis point to temporarily or permanently highlight the local up/down/left/right directions
/// when all axis points have been defined. These highlights are meant to make it apparent when a mistake has happened
/// so the screen-to-graph transformation is currently wrong - since the expected up/down/left/right directions will be awry
class HighlightsPoint : public QGraphicsPolygonItem
{
public:
  /// Constructor for DlgSettingsAxesHighlights, which does not have an explicit transformation. The identity transformation is assumed
  HighlightsPoint();

  /// Constructor for GraphicsScene, which requires the transformation to be defined
  HighlightsPoint(const Transformation &transformation);

  /// Set method for line color. The color should be recognizable against the (typically) black axes lines
  void setLineColor (const QColor &lineColor);
};

#endif // HIGHLIGHTS_POINT_H
