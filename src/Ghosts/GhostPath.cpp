#include "GhostPath.h"

GhostPath::GhostPath(const QPainterPath &path, const QPen &pen,
                     const QBrush &brush)
    : m_path(path), m_pen(pen), m_brush(brush) {}

GhostPath::GhostPath(const GhostPath &other)
    : m_path(other.path()), m_pen(other.pen()), m_brush(other.brush()) {}

GhostPath &GhostPath::operator=(const GhostPath &other) {
  m_path = other.path();
  m_pen = other.pen();
  m_brush = other.brush();

  return *this;
}

GhostPath::~GhostPath() {}

QBrush GhostPath::brush() const { return m_brush; }

QPainterPath GhostPath::path() const { return m_path; }

QPen GhostPath::pen() const { return m_pen; }
