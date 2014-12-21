#ifndef HIGHLIGHTS_POINT_H
#define HIGHLIGHTS_POINT_H

#include <QColor>
#include <QGraphicsPolygonItem>

class Transformation;

/// Point that is drawn underneath an axis point to temporarily or permanently highlight the local up/down/left/right directions
/// when all axis points have been defined. These highlights are meant to make it apparent when a mistake has happened
/// so the screen-to-graph transformation is currently wrong - since the expected up/down/left/right directions will be awry
///
/// When showing a preview for DlgSettingsAxesHighlights, the QGraphicsItem::setPos method can be called directly. This is because
/// the preview assumes there are no transformation errors, so the transformation is close enough to an identity matrix that we
/// can treat it as one
///
/// When not showing a preview for DlgSettingsAxesHighlights, positioning is entirely handled by this class. This is since the
/// geometry of the point vertices depends on the local transformation (broken or not), otherwise this class will fail to show transformation errors.
class HighlightsPoint : public QGraphicsPolygonItem
{
public:
  /// Single constructor.
  HighlightsPoint();

  /// Set method for line color. The color should be recognizable against the (typically) black axes lines
  void setLineColor (const QColor &lineColor);

  /// Set the position of the center of this point, using the current transformation so the vertices reflect the local up and right vectors.
  void setPos (const QPointF &pos,
               const Transformation &transformation);

};

#endif // HIGHLIGHTS_POINT_H
