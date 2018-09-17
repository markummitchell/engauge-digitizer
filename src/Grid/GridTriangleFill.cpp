/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include <algorithm>
#include "GridLog.h"
#include "GridTriangleFill.h"
#include <QImage>
#include <QList>
#include <QPoint>

// Non-member comparison function
static bool compareByY (const QPoint &first,
                        const QPoint &second)
{
  if (first.y() < second.y()) {
    return true;
  } else if (first.y() > second.y()) {
    return false;
  } else {
    // If y values are the same then sort by x values
    return (first.x() < second.x());
  }
}

GridTriangleFill::GridTriangleFill ()
{
}

void GridTriangleFill::drawLine (GridLog &gridLog,
                                 QImage &image,
                                 int x0,
                                 int x1,
                                 int y)
{
  const double RADIUS = 0.1;

  if (x0 > x1) {
    int xTemp = x0;
    x0 = x1;
    x1 = xTemp;

  }

  for (int x = x0; x <= x1; x++) {

    gridLog.showOutputScanLinePixel (x, y, RADIUS);

    image.setPixel (QPoint (x, y),
                    Qt::black);
  }
}

void GridTriangleFill::fill (GridLog &gridLog,
                             QImage &image,
                             const QPoint &p0In,
                             const QPoint &p1In,
                             const QPoint &p2In)
{
  if (p0In.x() > 0 && p0In.y() > 0 &&
      p1In.x() > 0 && p1In.y() > 0 &&
      p2In.x() > 0 && p2In.y() > 0) {

    QPoint p0, p1, p2;

    sortByAscendingY (p0In, p1In, p2In, p0, p1, p2);

    if (p1.y() == p2.y()) {

      // Triangle with flat bottom
      flatBottom (gridLog, image, p0, p1, p2);

    } else if (p0.y() == p1.y()) {

      // Triangle with flat top
      flatTop (gridLog, image, p0, p1, p2);

    } else {

      // General case is handled by splitting the triangle into one flat top piece and
      // one flat bottom piece. Fourth point is at same y value as middle point p1
      double s = (double) (p1.y() - p0.y())/ (double) (p2.y() - p0.y());
      QPoint p3 ((int) (p0.x() + s * (p2.x() - p0.x())),
                 p1.y());
      flatBottom (gridLog, image, p0, p1, p3);
      flatTop (gridLog, image, p1, p3, p2);
    }
  }
}

void GridTriangleFill::flatBottom (GridLog &gridLog,
                                   QImage &image,
                                   const QPoint &p0,
                                   const QPoint &p1,
                                   const QPoint &p2)
{
  // Either neither or both denominators are zero, since p1.y()=p2.y()
  double denom0 = p1.y() - p0.y();
  double denom1 = p2.y() - p0.y();
  if (denom0 == 0 || denom1 == 0) {
    drawLine (gridLog,
              image,
              p0.x(),
              p2.x(),
              p0.y());
  } else {
    double slopeInverse0 = (p1.x() - p0.x()) / denom0;
    double slopeInverse1 = (p2.x() - p0.x()) / denom1;

    // For rounding lower point down and upper point up, thus ensuring thorough coverage
    // (=no gaps between triangles), we order the inverse slopes
    if (slopeInverse0 > slopeInverse1) {
      double temp = slopeInverse0;
      slopeInverse0 = slopeInverse1;
      slopeInverse1 = temp;
    }

    double x0 = p0.x();
    double x1 = p0.x();

    for (int scanLineY = p0.y(); scanLineY <= p1.y(); scanLineY++) {
      drawLine (gridLog,
                image,
                (int) x0,
                (int) x1,
                scanLineY);
      x0 += slopeInverse0;
      x1 += slopeInverse1;
    }
  }
}

void GridTriangleFill::flatTop (GridLog &gridLog,
                                QImage &image,
                                const QPoint &p0,
                                const QPoint &p1,
                                const QPoint &p2)
{
  // Either neither or both denominators are zero, since p0.y()=p1.y()
  double denom0 = p2.y() - p0.y();
  double denom1 = p2.y() - p1.y();
  if (denom0 == 0 || denom1 == 0) {
    drawLine (gridLog,
              image,
              p0.x(),
              p2.x(),
              p0.y());
  } else {
    double slopeInverse0 = (p2.x() - p0.x()) / denom0;
    double slopeInverse1 = (p2.x() - p1.x()) / denom1;

    // For rounding lower point down and upper point up, thus ensuring thorough coverage
    // (=no gaps between triangles), we order the inverse slopes
    if (slopeInverse1 > slopeInverse0) {
      double temp = slopeInverse0;
      slopeInverse0 = slopeInverse1;
      slopeInverse1 = temp;
    }

    double x0 = p2.x();
    double x1 = p2.x();

    for (int scanLineY = p2.y(); scanLineY >= p0.y(); scanLineY--) {
      drawLine (gridLog,
                image,
                (int) x0,
                (int) x1,
                scanLineY);
      x0 -= slopeInverse0;
      x1 -= slopeInverse1;
    }
  }
}

void GridTriangleFill::sortByAscendingY (QPoint p0In,
                                         QPoint p1In,
                                         QPoint p2In,
                                         QPoint &p0,
                                         QPoint &p1,
                                         QPoint &p2) const
{
  // Sort by ascending y value
  QList<QPoint> list;
  list << p0In << p1In << p2In;
  std::sort (list.begin(), list.end(), compareByY);

  p0 = list.front();
  list.pop_front();
  p1 = list.front();
  list.pop_front();
  p2 = list.front();
}
