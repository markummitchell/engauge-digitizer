#ifndef GRID_REMOVAL_H
#define GRID_REMOVAL_H

#include <QPixmap>
#include <QPointF>

class DocumentModelGridRemoval;
class GridHealer;
class QImage;
class Transformation;

/// Strategy class for grid removal
class GridRemoval {
public:
  /// Single constructor
  GridRemoval();

  /// Process QImage into QPixmap, removing the grid lines
  QPixmap remove(const Transformation &transformation,
                 const DocumentModelGridRemoval &modelGridRemoval,
                 const QImage &imageBefore);

private:
  /// Clip line by projecting posUnprojected point onto x=xBoundary boundary.
  /// Line must pass over the boundary
  QPointF clipX(const QPointF &posUnprojected, double xBoundary,
                const QPointF &posOther) const;

  /// Clip line by projecting posUnprojected point onto y=yBoundary boundary.
  /// Line must pass over the boundary
  QPointF clipY(const QPointF &posUnprojected, double yBoundary,
                const QPointF &posOther) const;

  void removeLine(const QPointF &pos1, const QPointF &pos2, QImage &image,
                  GridHealer &gridHealer);
};

#endif // GRID_REMOVAL_H
