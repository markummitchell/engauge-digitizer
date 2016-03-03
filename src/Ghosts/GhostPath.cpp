/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GhostPath.h"

GhostPath::GhostPath(const QPainterPath &path,
                     const QPen &pen,
                     const QBrush &brush) :
  m_path (path),
  m_pen (pen),
  m_brush (brush)
{
}

GhostPath::GhostPath(const GhostPath &other) :
  m_path (other.path ()),
  m_pen (other.pen()),
  m_brush (other.brush ())
{
}

GhostPath &GhostPath::operator=(const GhostPath &other)
{
  m_path = other.path();
  m_pen = other.pen();
  m_brush = other.brush();

  return *this;
}

GhostPath::~GhostPath()
{
}

QBrush GhostPath::brush() const
{
  return m_brush;
}

QPainterPath GhostPath::path() const
{
  return m_path;
}

QPen GhostPath::pen() const
{
  return m_pen;
}
