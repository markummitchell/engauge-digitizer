#ifndef GRAPHICS_POINT_ABSTRACT_BASE_H
#define GRAPHICS_POINT_ABSTRACT_BASE_H

#include <QPointF>
#include <QString>

class GraphicsLine;

/// Base class for adding identifiers to graphics items that represent Points. Identifiers are needed
/// to distinguish which nodes are selected from those that are not selected. Each identifier is stored
/// as a data item in QGraphicsItem.
///
/// The subclasses of this class use multiple inheritance to inherit from one of the subclasses
/// of QGraphicsItem.
///
/// Lines are drawn twice:
/// 1) As nonzero-width lines so user can have thick, and highly visible, points
/// 2) As a 'shadow' with zero-width lines since these always appear even when zooming results in some pixel
///    rows/columns disappearing
/// This dual-line approach is better than using QGraphicsItem::ItemIgnoresTransformations to prevent horrible
/// aliasing problems, since that approach involves complicated transformation matrix manipulations
class GraphicsPointAbstractBase
{
public:
  /// Single constructor.
  GraphicsPointAbstractBase();
  virtual ~GraphicsPointAbstractBase();

  /// Bind line to this point, with this point as the line end
  void setLineWithPointAsEnd (GraphicsLine &graphicsLine);

  /// Bind line to this point, with this point as the line start
  void setLineWithPointAsStart (GraphicsLine &graphicsLine);

protected:

  /// Move lines that are attached to this line, since they were bound previously
  void moveAttachedLines (const QPointF &pos);

private:
  void removeOverrideCursor ();

  GraphicsLine *m_lineWithPointAsStart;
  GraphicsLine *m_lineWithPointAsEnd;
};

#endif // GRAPHICS_POINT_ABSTRACT_BASE_H
