#ifndef GHOST_PATH_H
#define GHOST_PATH_H

#include <QBrush>
#include <QPainterPath>
#include <QPen>

/// Ghost for a QGraphicsPathItem
class GhostPath
{
 public:
  /// Initial constructor
  GhostPath(const QPainterPath &path,
            const QPen &pen,
            const QBrush &brush);
  ~GhostPath();

  /// Copy constructor
  GhostPath(const GhostPath &other);

  /// Assignment operator
  GhostPath &operator=(const GhostPath &other);

  /// Get method for brush
  QBrush brush() const;

  /// Get method for path
  QPainterPath path() const;

  /// Get method for pen
  QPen pen() const;

 private:
  GhostPath();

  QPainterPath m_path;
  QPen m_pen;
  QBrush m_brush;
};

#endif // GHOST_PATH_H
