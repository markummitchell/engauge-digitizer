/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGridRemoval.h"
#include "EngaugeAssert.h"
#include "GridHealerAbstractBase.h"
#include "GridLog.h"
#include "GridTriangleFill.h"
#include "Logger.h"
#include "Pixels.h"
#include <QFile>
#include <QImage>
#include <qmath.h>
#include <QRgb>
#include <QTextStream>

GridHealerAbstractBase::GridHealerAbstractBase(GridLog &gridLog,
                                               const DocumentModelGridRemoval &modelGridRemoval) :
  m_modelGridRemoval (modelGridRemoval),
  m_maxPointSeparation (0),
  m_gridLog (gridLog)
{
}

GridHealerAbstractBase::~GridHealerAbstractBase()
{
}

void GridHealerAbstractBase::addMutualPair (int x0,
                                            int y0,
                                            int x1,
                                            int y1)
{
  m_mutualPairHalvesBelow.push_back (QPoint (x0, y0));
  m_mutualPairHalvesAbove.push_back (QPoint (x1, y1));
}

void GridHealerAbstractBase::fillTrapezoid (QImage &image,
                                            int xBL, int yBL,
                                            int xBR, int yBR,
                                            int xTR, int yTR,
                                            int xTL, int yTL)
{
  // Sanity checks
  if (xBL == 0 || yBL == 0 || xBR == 0 || yBR == 0 || xTR == 0 || yTR == 0 || xTL == 0 || yTL == 0) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealerAbstractBase::fillTrapezoid received undefined corner coordinate "
                                 << "xBL=" << xBL << " yBL=" << yBL << " xBR=" << xBR << " yBR=" << yBR
                                 << "xTR=" << xTR << " yTR=" << yTR << " xTL=" << xTL << " yTL=" << yTL;
  }

  if (!Pixels::pixelIsBlack(image, xBL, yBL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealerAbstractBase::fillTrapezoid has bad bottom left point";
  }
  if (!Pixels::pixelIsBlack(image, xBR, yBR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealerAbstractBase::fillTrapezoid has bad bottom right point";
  }
  if (!Pixels::pixelIsBlack(image, xTR, yTR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealerAbstractBase::fillTrapezoid has bad top right point";
  }
  if (!Pixels::pixelIsBlack(image, xTL, yTL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealerAbstractBase::fillTrapezoid has bad top left point";
  }

  // Any quadrilateral (including this trapezoid) can be considered the union of two triangles
  GridTriangleFill triangleFill;
  triangleFill.fill (m_gridLog,
                     image,
                     QPoint (xBL, yBL),
                     QPoint (xBR, yBR),
                     QPoint (xTR, yTR));
  triangleFill.fill (m_gridLog,
                     image,
                     QPoint (xBL, yBL),
                     QPoint (xTL, yTL),
                     QPoint (xTR, yTR));
}

GridLog &GridHealerAbstractBase::gridLog ()
{
  return m_gridLog;
}

void GridHealerAbstractBase::healed (QImage &image)
{
  applyMutualPairs (image);
  doHealingAcrossGaps (image);
}

double GridHealerAbstractBase::maxPointSeparation () const
{
  return m_maxPointSeparation;
}

DocumentModelGridRemoval &GridHealerAbstractBase::modelGridRemoval()
{
  return m_modelGridRemoval;
}

const MutualPairHalves &GridHealerAbstractBase::mutualPairHalvesAbove () const
{
  return m_mutualPairHalvesAbove;
}

const MutualPairHalves &GridHealerAbstractBase::mutualPairHalvesBelow () const
{
  return m_mutualPairHalvesBelow;
}

int GridHealerAbstractBase::pixelCountInRegionThreshold (const DocumentModelGridRemoval &modelGridRemoval)
{
  // For now we will use the close distance as the minimum pixel count
  return qFloor (modelGridRemoval.closeDistance());
}

bool GridHealerAbstractBase::pointsAreGood (const QImage &image,
                                            int x0,
                                            int y0,
                                            int x1,
                                            int y1) const
{
  Pixels pixels;

  int stopCountAt = pixelCountInRegionThreshold (m_modelGridRemoval);

  // Skip if either endpoint is an unwanted artifact. Look at start point below (since it is connected
  // to the end point below), and the start point above (which is connected to the end point above)
  return ((pixels.countBlackPixelsAroundPoint (image, x0, y0, stopCountAt) >= stopCountAt) &&
          (pixels.countBlackPixelsAroundPoint (image, x1, y1, stopCountAt) >= stopCountAt));
}

void GridHealerAbstractBase::saveGapSeparation (double gapSeparation)
{
  // Right triangle with one edge crossing the gap (separation value) and hypotenuse giving
  // maximum point separation (closest distance) gives the maximum horizontal separation
  m_maxPointSeparation = qFloor (qSqrt (qPow (modelGridRemoval().closeDistance(), 2) -
                                        qPow (gapSeparation, 2)));
}
