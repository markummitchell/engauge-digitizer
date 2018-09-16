/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGridRemoval.h"
#include "EngaugeAssert.h"
#include "GridHealerHorizontal.h"
#include "GridHealerVertical.h"
#include "GridRemoval.h"
#include "Logger.h"
#include "Pixels.h"
#include <QImage>
#include <qmath.h>
#include "Transformation.h"

const double EPSILON = 0.000001;

GridRemoval::GridRemoval (bool isGnuplot) :
  m_gridLog (isGnuplot)
{
}

QPointF GridRemoval::clipX (const QPointF &posUnprojected,
                            double xBoundary,
                            const QPointF &posOther) const
{
  double s = 0;
  if (posOther.x() != posUnprojected.x()) {
    s = (xBoundary - posUnprojected.x()) / (posOther.x() - posUnprojected.x());
  }
  ENGAUGE_ASSERT ((-1.0 * EPSILON < s) && (s < 1.0 + EPSILON));

  return QPointF ((1.0 - s) * posUnprojected.x() + s * posOther.x(),
                  (1.0 - s) * posUnprojected.y() + s * posOther.y());
}

QPointF GridRemoval::clipY (const QPointF &posUnprojected,
                            double yBoundary,
                            const QPointF &posOther) const
{
  double s = 0;
  if (posOther.y() != posUnprojected.y()) {
    s = (yBoundary - posUnprojected.y()) / (posOther.y() - posUnprojected.y());
  }
  ENGAUGE_ASSERT ((-1.0 * EPSILON < s) && (s < 1.0 + EPSILON));

  return QPointF ((1.0 - s) * posUnprojected.x() + s * posOther.x(),
                  (1.0 - s) * posUnprojected.y() + s * posOther.y());
}

QPixmap GridRemoval::remove (const Transformation &transformation,
                             const DocumentModelGridRemoval &modelGridRemoval,
                             const QImage &imageBefore)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridRemoval::remove"
                              << " transformationIsDefined=" << (transformation.transformIsDefined() ? "true" : "false")
                              << " removeDefinedGridLines=" << (modelGridRemoval.removeDefinedGridLines() ? "true" : "false");

  QImage image = imageBefore;

  // Collect GridHealers instances, one per grid line
  GridHealers gridHealers;

  // Make sure grid line removal is wanted, and possible. Otherwise all processing is skipped
  if (modelGridRemoval.removeDefinedGridLines() &&
      transformation.transformIsDefined()) {

    double yGraphMin = modelGridRemoval.startY();
    double yGraphMax = modelGridRemoval.stopY();
    for (int i = 0; i < modelGridRemoval.countX(); i++) {
      double xGraph = modelGridRemoval.startX() + i * modelGridRemoval.stepX();

      // Convert line between graph coordinates (xGraph,yGraphMin) and (xGraph,yGraphMax) to screen coordinates
      QPointF posScreenMin, posScreenMax;
      transformation.transformRawGraphToScreen (QPointF (xGraph,
                                                         yGraphMin),
                                                posScreenMin);
      transformation.transformRawGraphToScreen (QPointF (xGraph,
                                                         yGraphMax),
                                                posScreenMax);

      removeLine (posScreenMin,
                  posScreenMax,
                  image,
                  modelGridRemoval,
                  gridHealers);
    }

    double xGraphMin = modelGridRemoval.startX();
    double xGraphMax = modelGridRemoval.stopX();
    for (int j = 0; j < modelGridRemoval.countY(); j++) {
      double yGraph = modelGridRemoval.startY() + j * modelGridRemoval.stepY();

      // Convert line between graph coordinates (xGraphMin,yGraph) and (xGraphMax,yGraph) to screen coordinates
      QPointF posScreenMin, posScreenMax;
      transformation.transformRawGraphToScreen (QPointF (xGraphMin,
                                                         yGraph),
                                                posScreenMin);
      transformation.transformRawGraphToScreen (QPointF (xGraphMax,
                                                         yGraph),
                                                posScreenMax);

      removeLine (posScreenMin,
                  posScreenMax,
                  image,
                  modelGridRemoval,
                  gridHealers);
    }

    // Heal the broken lines now that all grid lines have been removed and the image has stabilized
    GridHealers::iterator itr;
    for (itr = gridHealers.begin(); itr != gridHealers.end(); itr++) {
      GridHealerAbstractBase *gridHealer = *itr;
      gridHealer->healed (image);
      delete gridHealer;
    }
  }

  return QPixmap::fromImage (image);
}

void GridRemoval::removeLine (const QPointF &posMin,
                              const QPointF &posMax,
                              QImage &image,
                              const DocumentModelGridRemoval &modelGridRemoval,
                              GridHealers &gridHealers)
{
  const int HALF_WIDTH = 1;

  double w = image.width() - 1; // Inclusive width = exclusive width - 1
  double h = image.height() - 1; // Inclusive height = exclusive height - 1

  QPointF pos1 = posMin;
  QPointF pos2 = posMax;

  // Throw away all lines that are entirely above or below or left or right to the screen, since
  // they cannot intersect the screen
  bool onLeft   = (pos1.x() < 0 && pos2.x () < 0);
  bool onTop    = (pos1.y() < 0 && pos2.y () < 0);
  bool onRight  = (pos1.x() > w && pos2.x () > w);
  bool onBottom = (pos1.y() > h && pos2.y () > h);
  if (!onLeft && !onTop && !onRight && !onBottom) {

    // Clip to within the four sides
    if (pos1.x() < 0) { pos1 = clipX (pos1, 0, pos2); }
    if (pos2.x() < 0) { pos2 = clipX (pos2, 0, pos1); }
    if (pos1.y() < 0) { pos1 = clipY (pos1, 0, pos2); }
    if (pos2.y() < 0) { pos2 = clipY (pos2, 0, pos1); }
    if (pos1.x() > w) { pos1 = clipX (pos1, w, pos2); }
    if (pos2.x() > w) { pos2 = clipX (pos2, w, pos1); }
    if (pos1.y() > h) { pos1 = clipY (pos1, h, pos2); }
    if (pos2.y() > h) { pos2 = clipY (pos2, h, pos1); }

    // Is line more horizontal or vertical?
    double deltaX = qAbs (pos1.x() - pos2.x());
    double deltaY = qAbs (pos1.y() - pos2.y());
    if (deltaX > deltaY) {

      // More horizontal
      GridHealerAbstractBase *gridHealer = new GridHealerHorizontal (m_gridLog,
                                                         modelGridRemoval);
      gridHealers.push_back (gridHealer);

      int xMin = qMin (pos1.x(), pos2.x());
      int xMax = qMax (pos1.x(), pos2.x());
      int yAtXMin = (pos1.x() < pos2.x() ? pos1.y() : pos2.y());
      int yAtXMax = (pos1.x() < pos2.x() ? pos2.y() : pos1.y());
      for (int x = xMin; x <= xMax; x++) {
        double s = (double) (x - xMin) / (double) (xMax - xMin);
        int yLine = (int) (0.5 + (1.0 - s) * yAtXMin + s * yAtXMax);
        for (int yOffset = -HALF_WIDTH; yOffset <= HALF_WIDTH; yOffset++) {
          int y = yLine + yOffset;
          image.setPixel (x, y, QColor(Qt::white).rgb());
        }
        gridHealer->addMutualPair (x, yLine - HALF_WIDTH - 1, x, yLine + HALF_WIDTH + 1);
      }

    } else {

      // More vertical
      GridHealerAbstractBase *gridHealer = new GridHealerVertical (m_gridLog,
                                                                   modelGridRemoval);
      gridHealers.push_back (gridHealer);

      int yMin = qMin (pos1.y(), pos2.y());
      int yMax = qMax (pos1.y(), pos2.y());
      int xAtYMin = (pos1.y() < pos2.y() ? pos1.x() : pos2.x());
      int xAtYMax = (pos1.y() < pos2.y() ? pos2.x() : pos1.x());
      for (int y = yMin; y <= yMax; y++) {
        double s = (double) (y - yMin) / (double) (yMax - yMin);
        int xLine = (int) (0.5  + (1.0 - s) * xAtYMin + s * xAtYMax);
        for (int xOffset = -HALF_WIDTH; xOffset <= HALF_WIDTH; xOffset++) {
          int x = xLine + xOffset;
          image.setPixel (x, y, QColor(Qt::white).rgb());
        }
        gridHealer->addMutualPair (xLine - HALF_WIDTH - 1, y, xLine + HALF_WIDTH + 1, y);
      }

    }
  }
}

