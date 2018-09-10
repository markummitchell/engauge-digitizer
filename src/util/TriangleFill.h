/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef TRIANGLE_FILL_H
#define TRIANGLE_FILL_H

#include <QPoint>

class QImage;

/// Class that does raster-line fill of a triangle. Inspired by
/// http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html
class TriangleFill
{
public:
  TriangleFill();

  /// Fill triangle between these three points
  void fill (QImage &image,
             const QPoint &p0,
             const QPoint &p1,
             const QPoint &p2);             

private:

  void drawLine (QImage &image,
                 int x0,
                 int x1,
                 int y);
  void flatBottom (QImage &image,
                   const QPoint &p0,
                   const QPoint &p1,
                   const QPoint &p2); // Assumes p1 and p2 are at bottom at same y level
  void flatTop (QImage &image,
                const QPoint &p0,
                const QPoint &p1,
                const QPoint &p2); // Assumes p0 and p1 are at top at same y level

  QPoint m_p0;
  QPoint m_p1;
  QPoint m_p2;
};

#endif // TRIANGLE_FILL_H
