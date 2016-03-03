/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GHOST_POLYGON_H
#define GHOST_POLYGON_H

#include <QBrush>
#include <QPen>
#include <QPolygon>

/// Ghost for a QGraphicsPolygonItem
class GhostPolygon
{
 public:
  /// Initial constructor
  GhostPolygon(const QPolygonF &polygon,
               const QPen &pen,
               const QBrush &brush);
  ~GhostPolygon();

  /// Copy constructor
  GhostPolygon(const GhostPolygon &other);

  /// Assignment operator
  GhostPolygon &operator=(const GhostPolygon &other);

  /// Get method for brush
  QBrush brush() const;

  /// Get method for pen
  QPen pen() const;

  /// Get method for polygon
  QPolygonF polygon() const;

 private:
  GhostPolygon();

  QPolygonF m_polygon;
  QPen m_pen;
  QBrush m_brush;
};

#endif // GHOST_POLYGON_H
