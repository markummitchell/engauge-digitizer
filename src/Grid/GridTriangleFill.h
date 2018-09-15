/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_TRIANGLE_FILL_H
#define GRID_TRIANGLE_FILL_H

#include <QPoint>

class GridLog;
class QImage;

/// Class that does raster-line fill of a triangle, with logging customizations for GridHealer (and therefore
/// not a generic class in util subdirectory). Inspired by
/// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
class GridTriangleFill
{
public:
  GridTriangleFill();

  /// Fill triangle between these three points
  void fill (GridLog &gridLog,
             QImage &image,
             const QPoint &p0,
             const QPoint &p1,
             const QPoint &p2);             

private:

  void drawLine (GridLog &gridLog,
                 QImage &image,
                 int x0,
                 int x1,
                 int y);
  void flatBottom (GridLog &gridLog,
                   QImage &image,
                   const QPoint &p0,
                   const QPoint &p1,
                   const QPoint &p2); // Assumes p1 and p2 are at bottom at same y level
  void flatTop (GridLog &gridLog,
                QImage &image,
                const QPoint &p0,
                const QPoint &p1,
                const QPoint &p2); // Assumes p0 and p1 are at top at same y level
  void sortByAscendingY (QPoint p0In,
                         QPoint p1In,
                         QPoint p2In,
                         QPoint &p0,
                         QPoint &p1,
                         QPoint &p2) const;

  QPoint m_p0;
  QPoint m_p1;
  QPoint m_p2;
};

#endif // GRID_TRIANGLE_FILL_H
