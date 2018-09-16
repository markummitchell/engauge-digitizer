/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_REMOVAL_H
#define GRID_REMOVAL_H

#include "GridLog.h"
#include <QList>
#include <QPixmap>
#include <QPointF>

class DocumentModelGridRemoval;
class GridHealerAbstractBase;
class QImage;
class Transformation;

/// Storage of GridHealer instances
typedef QList<GridHealerAbstractBase*> GridHealers;

/// Strategy class for grid removal
class GridRemoval
{
 public:
  /// Single constructor
  GridRemoval(bool isGnuplot);

  /// Process QImage into QPixmap, removing the grid lines
  QPixmap remove (const Transformation &transformation,
                  const DocumentModelGridRemoval &modelGridRemoval,
                  const QImage &imageBefore);

private:
  GridRemoval();

  /// Clip line by projecting posUnprojected point onto x=xBoundary boundary. Line must pass over the boundary
  QPointF clipX (const QPointF &posUnprojected,
                 double xBoundary,
                 const QPointF &posOther) const;

  /// Clip line by projecting posUnprojected point onto y=yBoundary boundary. Line must pass over the boundary
  QPointF clipY (const QPointF &posUnprojected,
                 double yBoundary,
                 const QPointF &posOther) const;

  void removeLine (const QPointF &pos1,
                   const QPointF &pos2,
                   QImage &image,
                   const DocumentModelGridRemoval &modelGridRemoval,
                   GridHealers &gridHealers);

  GridLog m_gridLog;
};

#endif // GRID_REMOVAL_H
