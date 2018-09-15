/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGridRemoval.h"
#include "EngaugeAssert.h"
#include "GridHealer.h"
#include "GridTriangleFill.h"
#include "Logger.h"
#include "Pixels.h"
#include <QFile>
#include <QImage>
#include <qmath.h>
#include <QRgb>
#include <QTextStream>

// Enable large amount of debug spew
#define DETAILED_LOGGING 1
const int DETAILED_CENTER_X = 704;
const int DETAILED_CENTER_Y = 521;
const int DETAILED_RADIUS = 8;

// Derived constants
const int DETAILED_X_MIN = DETAILED_CENTER_X - DETAILED_RADIUS;
const int DETAILED_X_MAX = DETAILED_CENTER_X + DETAILED_RADIUS;
const int DETAILED_Y_MIN = DETAILED_CENTER_Y - DETAILED_RADIUS;
const int DETAILED_Y_MAX = DETAILED_CENTER_Y + DETAILED_RADIUS;

GridHealer::GridHealer(GridLineOrientation gridLineOrientation,
                       const DocumentModelGridRemoval &modelGridRemoval) :
  m_gridLineOrientation (gridLineOrientation),
  m_modelGridRemoval (modelGridRemoval),
  m_gapSeparation (0),
  m_gridLog (gridLineOrientation)
{
}

void GridHealer::addMutualPair (int x0,
                                int y0,
                                int x1,
                                int y1)
{
  m_mutualPairHalvesBelow.push_back (QPoint (x0, y0));
  m_mutualPairHalvesAbove.push_back (QPoint (x1, y1));
}

void GridHealer::applyMutualPairs (const QImage &image)
{
  MutualPairHalves::iterator itrBelow = m_mutualPairHalvesBelow.begin();
  MutualPairHalves::iterator itrAbove = m_mutualPairHalvesAbove.begin();

  while (itrBelow != m_mutualPairHalvesBelow.end() &&
         itrAbove != m_mutualPairHalvesAbove.end()) {

    QPoint xy0 = *(itrBelow++);
    QPoint xy1 = *(itrAbove++);

    // Convert (x,y) pairs to (independent,dependent) pairs
    QPoint id0 (xy0), id1 (xy1);
    if (m_gridLineOrientation == GridLineOrientation::Vertical) {
      id0 = QPoint (xy0.y(), xy0.x());
      id1 = QPoint (xy1.y(), xy1.x());
    }

    // Save (independent,dependent) pairs
    if (Pixels::pixelIsBlack (image, xy0.x(), xy0.y())) {
      m_blackPixelsBelow [id0.x()] = id0.y();
    }

    if (Pixels::pixelIsBlack (image, xy1.x(), xy1.y())) {
      m_blackPixelsAbove [id1.x()] = id1.y();
    }

    m_gapSeparation = qAbs (id1.y() - id0.y());
  }
}

bool GridHealer::blackPixelRegionIsBigEnough (const QImage &image,
                                              int i,
                                              int d) const
{
  // Convert from (independent,dependent) pair to (x,y) pair
  int x = i, y = d;
  if (m_gridLineOrientation == GridLineOrientation::Vertical) {
    x = d;
    y = i;
  }

  Pixels pixels;
  int count = pixels.countBlackPixelsAroundPoint (image,
                                                  x,
                                                  y,
                                                  m_modelGridRemoval.closeDistance());
  return (count >= m_modelGridRemoval.closeDistance ());
}

void GridHealer::doHealingAcrossGaps (QImage &image)
{
  // LOG4CPP_INFO_S is replaced by GridLog
  m_gridLog.showInputPixels(m_blackPixelsBelow,
                            m_blackPixelsAbove);

  // Algorithm requires at least one point in each of the lists
  if (m_blackPixelsBelow.count() > 0 &&
      m_blackPixelsAbove.count() > 0) {

    int xFirst = qMin (m_blackPixelsBelow.firstKey (),
                       m_blackPixelsAbove.firstKey ());
    int xLast = qMax (m_blackPixelsBelow.lastKey (),
                      m_blackPixelsAbove.lastKey ());

    // Right triangle with one edge crossing the gap (separation value) and hypotenuse giving
    // maximum point separation (closest distance) gives the maximum horizontal separation
    int maxHorSep = qSqrt (qPow (m_modelGridRemoval.closeDistance(), 2) -
                           qPow (m_gapSeparation, 2));

    int xBelowEnd = 0; // Used by inner loop to skip to this iterator value

    for (int xBelowStart = xFirst; xBelowStart <= xLast; xBelowStart++) {

      if ((xBelowEnd < xBelowStart) &&
          m_blackPixelsBelow.contains (xBelowStart)) {

        // This could be the start of a new trapezoid. Find where the range on the same side ends
        int xBelowOutOfBounds = xLast + 1; // Value forcing transition to out of range

        for (xBelowEnd = xBelowStart + 1; xBelowEnd <= xBelowOutOfBounds; xBelowEnd++) {

          if (!m_blackPixelsBelow.contains (xBelowEnd) || (xBelowEnd == xBelowOutOfBounds)) {

            doHealingOnBelowRange (image,
                                   xBelowStart,
                                   xBelowEnd,
                                   maxHorSep);

            // Go back to outer loop, which will skip to xBelowEnd
            break;
          }
        }
      }
    }
  }
}

void GridHealer::doHealingOnBelowAndAboveRangePair (QImage &image,
                                                    int xBelowStart,
                                                    int xBelowEnd,
                                                    int xAboveStart,
                                                    int xAboveEnd)
{
  // LOG4CPP_INFO_S is replaced by GridLog

  int x0 = xBelowStart;
  int x1 = xBelowEnd;
  int x2 = xAboveEnd;
  int x3 = xAboveStart;
  int y0 = m_blackPixelsBelow [xBelowStart];
  int y1 = m_blackPixelsBelow [xBelowEnd  ];
  int y2 = m_blackPixelsAbove [xAboveEnd  ];
  int y3 = m_blackPixelsAbove [xAboveStart];

  m_gridLog.showOutputTrapezoids (y0,
                                  y1,
                                  y2,
                                  y3,
                                  x0,
                                  x1,
                                  x2,
                                  x3);

  if (pointsAreGood (image, x0, y0, x2, y2)) {

    // Big enough so keep it. Four points that define the trapezoid to be filled in
    fillTrapezoid (image,
                   x0, y0,
                   x1, y1,
                   x2, y2,
                   x3, y3);
  }
}

void GridHealer::doHealingOnBelowRange (QImage &image,
                                        int xBelowStart,
                                        int xBelowEnd,
                                        int maxHorSep)
{
  // LOG4CPP_INFO_S is replaced by GridLog

  // Below range goes from xBelowStart (inclusive) to xBelowEnd (exclusive). There could
  // be zero, one or more above ranges that overlap within maxHorSep, corresponding
  // to an equal number of trapezoids to be filled in
  //
  // It is important to note that every above point between xBelowStart-maxHorSep to
  // xBelowEnd+maxHorSep is close enough (<close distance) to a point in the below range

  int xAboveOutOfBounds = xBelowEnd + maxHorSep + 1; // Value forcing transition to out of range

  int xAboveEnd = 0; // Used by inner loop to skip to this iterator value

  for (int xAboveStart = xBelowStart - maxHorSep; xAboveStart <= xAboveOutOfBounds; xAboveStart++) {

    if ((xAboveEnd < xAboveStart) &&
        m_blackPixelsAbove.contains (xAboveStart) &&
        (xAboveStart < xAboveOutOfBounds)) {

      for (xAboveEnd = xAboveStart + 1; xAboveEnd <= xAboveOutOfBounds; xAboveEnd++) {

        if (!m_blackPixelsAbove.contains (xAboveEnd) || (xAboveEnd == xAboveOutOfBounds)) {

          int xBelowStartNearEnough = qMax (xBelowStart, xAboveStart - maxHorSep);
          int xBelowEndNearEnough = qMin (xBelowEnd - 1, xAboveEnd + maxHorSep);
          int xAboveEndInclusive = xAboveEnd - 1;

          if (xBelowStartNearEnough <= xBelowEndNearEnough) {

            doHealingOnBelowAndAboveRangePair (image,
                                               xBelowStartNearEnough,
                                               xBelowEndNearEnough,
                                               xAboveStart,
                                               xAboveEndInclusive);

            // Go back to outer loop, which will skip to xAboveEnd
            break;
          }
        }
      }
    }
  }
}

void GridHealer::fillTrapezoid (QImage &image,
                                int iBL, int dBL,
                                int iBR, int dBR,
                                int iTR, int dTR,
                                int iTL, int dTL)
{
  // Convert input (independent,dependent) pairs to (x,y) pairs
  int xBL = iBL, yBL = dBL, xBR = iBR, yBR = dBR, xTR = iTR, yTR = dTR, xTL = iTL, yTL = dTL;
  if (m_gridLineOrientation == GridLineOrientation::Vertical) {
    xBL = dBL;
    yBL = iBL;
    xBR = dBR;
    yBR = iBR;
    xTR = dTR;
    yTR = iTR;
    xTL = dTL;
    yTL = iTL;
  }

  // Sanity checks
  if (xBL == 0 || yBL == 0 || xBR == 0 || yBR == 0 || xTR == 0 || yTR == 0 || xTL == 0 || yTL == 0) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid received undefined corner coordinate "
                                 << "xBL=" << xBL << " yBL=" << yBL << " xBR=" << xBR << " yBR=" << yBR
                                 << "xTR=" << xTR << " yTR=" << yTR << " xTL=" << xTL << " yTL=" << yTL;
  }

  if (!Pixels::pixelIsBlack(image, xBL, yBL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad bottom left point";
  }
  if (!Pixels::pixelIsBlack(image, xBR, yBR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad bottom right point";
  }
  if (!Pixels::pixelIsBlack(image, xTR, yTR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad top right point";
  }
  if (!Pixels::pixelIsBlack(image, xTL, yTL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad top left point";
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

void GridHealer::healed (QImage &image)
{
  applyMutualPairs (image);
  doHealingAcrossGaps (image);
}

int GridHealer::pixelCountInRegionThreshold (const DocumentModelGridRemoval &modelGridRemoval)
{
  // For now we will use the close distance as the minimum pixel count
  return modelGridRemoval.closeDistance();
}

bool GridHealer::pointsAreGood (const QImage &image,
                                int i0,
                                int d0,
                                int i3,
                                int d3) const
{
  Pixels pixels;

  int stopCountAt = pixelCountInRegionThreshold (m_modelGridRemoval);

  // Convert (independent,dependent) pair to (x,y) pair
  int x0 = i0, y0 = d0, x3 = i3, y3 = d3;
  if (m_gridLineOrientation == GridLineOrientation::Vertical) {
    x0 = d0;
    y0 = i0;
    x3 = d3;
    y3 = i3;
  }

  // Skip if either endpoint is an unwanted artifact. Look at start point below (since it is connected
  // to the end point below), and the start point above (which is connected to the end point above)
  return ((pixels.countBlackPixelsAroundPoint (image, x0, y0, stopCountAt) >= stopCountAt) &&
          (pixels.countBlackPixelsAroundPoint (image, x3, y3, stopCountAt) >= stopCountAt));
}
