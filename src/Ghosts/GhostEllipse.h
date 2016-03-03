/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GHOST_ELLIPSE_H
#define GHOST_ELLIPSE_H

#include <QBrush>
#include <QPen>
#include <QRectF>

/// Ghost for a QGraphicsEllipseItem
class GhostEllipse
{
 public:
  /// Initial constructor
  GhostEllipse(const QRectF &rect,
               const QPen &pen,
               const QBrush &brush);
  ~GhostEllipse();

  /// Copy constructor
  GhostEllipse(const GhostEllipse &other);

  /// Assignment operator
  GhostEllipse &operator=(const GhostEllipse &other);

  /// Get method for brush
  QBrush brush () const;

  /// Get method for pen
  QPen pen () const;

  /// Get method for bounding rectangle
  QRectF rect() const;

 private:
  GhostEllipse();

  QRectF m_rect;
  QPen m_pen;
  QBrush m_brush;
};

#endif // GHOST_ELLIPSE_H
