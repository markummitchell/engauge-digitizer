#include "GhostPolygon.h"

GhostPolygon::GhostPolygon(const QPolygonF &polygon,
                           const QPen &pen,
                           const QBrush &brush) :
  m_polygon (polygon),
  m_pen (pen),
  m_brush (brush)
{
}

GhostPolygon::GhostPolygon(const GhostPolygon &other) :
  m_polygon (other.polygon ()),
  m_pen (other.pen()),
  m_brush (other.brush())
{
}

GhostPolygon &GhostPolygon::operator=(const GhostPolygon &other)
{
  m_polygon = other.polygon();
  m_pen = other.pen();
  m_brush = other.brush();

  return *this;
}

GhostPolygon::~GhostPolygon()
{
}

QBrush GhostPolygon::brush() const
{
  return m_brush;
}

QPen GhostPolygon::pen() const
{
  return m_pen;
}

QPolygonF GhostPolygon::polygon() const
{
  return m_polygon;
}
