#include "GhostEllipse.h"

GhostEllipse::GhostEllipse(const QRectF &rect,
                           const QPen &pen,
                           const QBrush &brush) :
  m_rect (rect),
  m_pen (pen),
  m_brush (brush)
{
}

GhostEllipse::GhostEllipse(const GhostEllipse &other) :
  m_rect (other.rect ()),
  m_pen (other.pen()),
  m_brush (other.brush())
{
}

GhostEllipse &GhostEllipse::operator=(const GhostEllipse &other)
{
  m_rect = other.rect();
  m_pen = other.pen();
  m_brush = other.brush();

  return *this;
}

GhostEllipse::~GhostEllipse()
{
}

QBrush GhostEllipse::brush() const
{
  return m_brush;
}

QPen GhostEllipse::pen () const
{
  return m_pen;
}

QRectF GhostEllipse::rect() const
{
  return m_rect;
}
