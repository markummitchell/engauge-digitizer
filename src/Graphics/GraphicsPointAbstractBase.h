#ifndef GRAPHICS_POINT_ABSTRACT_BASE_H
#define GRAPHICS_POINT_ABSTRACT_BASE_H

class GraphicsLine;
class LineStyle;

/// Base class for adding identifiers to graphics items that represent Points. Identifiers are needed
/// to distinguish which nodes are selected from those that are not selected. Each identifier is stored
/// as a data item in QGraphicsItem.
///
/// This abstract base class no longer does anything.
class GraphicsPointAbstractBase
{
public:
  /// Single constructor.
  GraphicsPointAbstractBase();
  virtual ~GraphicsPointAbstractBase();
};

#endif // GRAPHICS_POINT_ABSTRACT_BASE_H
