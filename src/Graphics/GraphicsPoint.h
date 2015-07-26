#ifndef GRAPHICS_POINT_H
#define GRAPHICS_POINT_H

#include "GraphicsPointAbstractBase.h"
#include "GraphicsPoint.h"
#include <QColor>
#include <QPointF>

class CurveStyle;
class GraphicsPointEllipse;
class GraphicsPointPolygon;
class PointStyle;
class QColor;
class QGraphicsScene;
class QPolygonF;
class QTextStream;
class QVariant;

/// Graphics item for drawing a circular or polygonal Point. 
///
/// In this class, lines are drawn twice:
/// 1) As nonzero-width lines so user can have thick, and highly visible, points
/// 2) As a 'shadow' with zero-width lines since these always appear even when zooming results in some pixel
///    rows/columns disappearing
/// This dual-line approach is better than using QGraphicsItem::ItemIgnoresTransformations to prevent horrible
/// aliasing problems, since that approach involves complicated transformation matrix manipulations
///
/// Layering is used for the single graphics item contained by this class. External code only has to deal with this
/// single class, and there is no multiple inheritance involved. If inheritance was used, we would have one class
/// based on QGraphicsEllipseItem and another on QGraphicsPolygonItem, so having a single class (for the convenience
/// of the external code) would involve multiple inheritance (of those two classes). With the inheritance approach, 
/// using just the methods supplied by QGraphicsItem would be inadequate.
class GraphicsPoint : public GraphicsPointAbstractBase
{
public:
  /// Constructor of circular point.
  GraphicsPoint(QGraphicsScene &scene,
                const QString &identifier,
                const QPointF &posScreen,
                const QColor &color,
                unsigned int radius,
                double lineWidth);

  /// Constructor of polygon point.
  GraphicsPoint(QGraphicsScene &scene,
                const QString &identifier,
                const QPointF &posScreen,
                const QColor &color,
                const QPolygonF &polygon,
                double lineWidth);

  /// Destructor. This remove the graphics item from the scene
  ~GraphicsPoint ();

  /// Proxy method for QGraphicsItem::data
  QVariant data (int key) const;

  /// Proxy method for QGraphicsItem::pos.
  QPointF pos () const;

  /// Debugging method that supports print method of this class and printStream method of some other class(es)
  void printStream (QString indentation,
                    QTextStream &str,
                    double ordinalKey) const;

  /// Mark point as unwanted, and unbind any bound lines.
  void reset();

  /// Proxy method for QGraphicsItem::setData
  void setData (int key, const QVariant &data);

  /// Update the point style
  void setPointStyle (const PointStyle &pointStyle);

  /// Update the position
  void setPos (const QPointF pos);

  /// Proxy method for QGraphicsItem::setToolTip
  void setToolTip (const QString &toolTip);

  /// Mark point as wanted. Marking as unwanted is done by the reset function
  void setWanted ();

  /// Update point and line styles that comprise the curve style
  void updateCurveStyle (const CurveStyle &curveStyle);

  /// Identify point as wanted//unwanted
  bool wanted () const;

private:
  GraphicsPoint();

  void createPointEllipse (unsigned int radius); // Attributes shared by circle and polygon points are passed through member variables
  void createPointPolygon (const QPolygonF &polygon); // Attributes shared by circle and polygon points are passed through member variables

  QGraphicsScene &m_scene;

  // Ellipse graphics items. Unused if point is polygonal.
  GraphicsPointEllipse *m_graphicsItemEllipse;
  GraphicsPointEllipse *m_shadowZeroWidthEllipse; // Shadow item overlays the superclass instance to ensure visibility

  // Polygon graphics items. Unused if point is elliptical.
  GraphicsPointPolygon *m_graphicsItemPolygon;
  GraphicsPointPolygon *m_shadowZeroWidthPolygon; // Shadow item overlays the superclass instance to ensure visibility

  // Shared attributes
  const QString m_identifier;
  const QPointF m_posScreen;
  const QColor m_color;
  double m_lineWidth;

  // Housekeeping
  bool m_wanted;
};

#endif // GRAPHICS_POINT_H
