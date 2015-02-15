#ifndef GRAPHICS_POINT_ABSTRACT_BASE_H
#define GRAPHICS_POINT_ABSTRACT_BASE_H

#include <QPointF>
#include <QString>

class GraphicsLine;

/// Base class for adding identifiers to graphics items that represent Points. Identifiers are needed
/// to distinguish which nodes are selected from those that are not selected. Each identifier is stored
/// as a data item in QGraphicsItem.
///
/// This abstract base class deals with binding from this point to attached lines.
class GraphicsPointAbstractBase
{
public:
  /// Single constructor.
  GraphicsPointAbstractBase();
  virtual ~GraphicsPointAbstractBase();

  /// Move lines that are attached to this line, since they were bound previously
  void moveAttachedLines (const QPointF &pos);

  /// Bind line to this point, with this point as the line end
  void setLineWithPointAsEnd (GraphicsLine *graphicsLine);

  /// Bind line to this point, with this point as the line start
  void setLineWithPointAsStart (GraphicsLine *graphicsLine);

protected:

  /// Unbind connected lines.
  void reset ();

private:
  void removeOverrideCursor ();

  GraphicsLine *m_lineWithPointAsStart;
  GraphicsLine *m_lineWithPointAsEnd;
};

#endif // GRAPHICS_POINT_ABSTRACT_BASE_H
