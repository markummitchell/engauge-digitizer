/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGridRemoval.h"
#include "EngaugeAssert.h"
#include "GridHealer.h"
#include "Logger.h"
#include <QImage>
#include <qmath.h>
#include <QRgb>
#include "TriangleFill.h"

GridHealer::GridHealer(GridLineOrientation gridLineOrientation,
                       const DocumentModelGridRemoval &modelGridRemoval) :
  m_gridLineOrientation (gridLineOrientation),
  m_modelGridRemoval (modelGridRemoval),
  m_gapSeparation (0)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::GridHealer";
}

void GridHealer::addAdjacentPoints (const QImage &image,
                                    int x0,
                                    int y0,
                                    int x1,
                                    int y1)
{

  if (m_gridLineOrientation == GridLineOrientation::Horizontal) {

    // Line is horizontal so independent variable is x, and points across the gap have the same x
    ENGAUGE_ASSERT (x0 == x1);
    if (pixelIsBlack (image, x0, y0)) {
      m_blackPixelsBelow [x0] = y0;
    }
    if (pixelIsBlack (image, x1, y1)) {
      m_blackPixelsAbove [x1] = y1;
    }
    m_gapSeparation = qAbs (y1 - y0);
    
  } else if (y0 == y1) {
    
    // Line is vertical so independent variable is y, and points across the gap have the same y
    ENGAUGE_ASSERT (y0 == y1);
    if (pixelIsBlack (image, x0, y0)) {
      m_blackPixelsBelow [y0] = x0;
    }
    if (pixelIsBlack (image, x1, y1)) {
      m_blackPixelsAbove [y1] = x1;
    }
    m_gapSeparation = qAbs (x1 - x0);
    
  } else {
    LOG4CPP_ERROR_S ((*mainCat)) << "Invalid case in GridHealer";
  }
}

void GridHealer::doHealing (QImage &image)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::doHealing "
                              << " countBelow=" << m_blackPixelsBelow.count()
                              << " countAbove=" << m_blackPixelsAbove.count();

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

    int xBelowSkipTo = 0; // Used by inner loop to skip to this iterator value

    for (int xBelowStart = xFirst; xBelowStart <= xLast; xBelowStart++) {
      if ((xBelowSkipTo < xBelowStart) && m_blackPixelsBelow.contains (xBelowStart)) {
        // This could be the start of a new trapezoid. Find where the range on the same side ends
        int xBelowOutOfBounds = xLast + 1; // Value forcing transition to out of range
        for (int xBelowEnd = xBelowStart + 1; xBelowEnd <= xBelowOutOfBounds; xBelowEnd++) {

          if (xBelowSkipTo > xBelowStart) {
            break; // Pop this iteration level
          }

          if ((xBelowSkipTo < xBelowEnd) && (!m_blackPixelsBelow.contains (xBelowEnd) || (xBelowEnd == xBelowOutOfBounds))) {

            // Below range goes from xBelowStart (inclusive) to xBelowEnd (exclusive). There could
            // be zero, one or more above ranges that overlap within maxHorSep, corresponding
            // to an equal number of trapezoids to be filled in
            //
            // It is important to note that every above point between xBelowStart-maxHorSep to
            // xBelowEnd+maxHorSep is close enough (<close distance) to a point in the below range
            bool insideRange = false; // Trivial state machine which targets transitions into/out of ranges
            int xAboveStartForThisRange = 0;
            int xAboveOutOfBounds = xBelowEnd + maxHorSep + 1; // Value forcing transition to out of range
            for (int xAbove = xBelowStart - maxHorSep; xAbove <= xAboveOutOfBounds; xAbove++) {

              bool includePixel = m_blackPixelsAbove.contains (xAbove) && (xAbove < xAboveOutOfBounds);

              if (!insideRange && includePixel) {
                // Transition from outside range to inside range
                insideRange = true;
                xAboveStartForThisRange = xAbove;
              } else if (insideRange && !includePixel) {
                // Transition from inside range to outside range
                insideRange = false;
                int xAboveEndForThisRange = xAbove - 1;
                int xBelowStartForThisRange = qMax (xBelowStart, xAboveStartForThisRange - maxHorSep);
                int xBelowEndForThisRange = qMin (xBelowEnd - 1, xAboveEndForThisRange + maxHorSep);

                if (xBelowStartForThisRange <= xBelowEndForThisRange) {

                  // Four points that define the trapezoid to be filled in
                  fillTrapezoid (image,
                                 xBelowStartForThisRange, m_blackPixelsBelow [xBelowStartForThisRange],
                                 xBelowEndForThisRange,   m_blackPixelsBelow [xBelowEndForThisRange  ],
                                 xAboveEndForThisRange,   m_blackPixelsAbove [xAboveEndForThisRange  ],
                                 xAboveStartForThisRange, m_blackPixelsAbove [xAboveStartForThisRange]);
                }
              }
            }

            // Make outer loop skip already-processed xBelowStart values
            xBelowSkipTo = xBelowEnd + 1;
          }
        }
      }
    }
  }
}

void GridHealer::fillTrapezoid (QImage &image,
                                int xBL, int yBL,
                                int xBR, int yBR,
                                int xTR, int yTR,
                                int xTL, int yTL)
{
  // Sanity checks
  if (xBL == 0 || yBL == 0 || xBR == 0 || yBR == 0 || xTR == 0 || yTR == 0 || xTL == 0 || yTL == 0) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid received undefined corner coordinate "
                                 << "xBL=" << xBL << " yBL=" << yBL << " xBR=" << xBR << " yBR=" << yBR
                                 << "xTR=" << xTR << " yTR=" << yTR << " xTL=" << xTL << " yTL=" << yTL;
  }

  if (!pixelIsBlack(image, xBL, yBL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad bottom left point";
  }
  if (!pixelIsBlack(image, xBR, yBR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad bottom right point";
  }
  if (!pixelIsBlack(image, xTR, yTR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad top right point";
  }
  if (!pixelIsBlack(image, xTL, yTL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad top left point";
  }

  // Any quadrilateral (including this trapezoid) can be considered the union of two triangles. We
  // convert from the (independent,dependent) variable pair to (x,y) pair depending on gridline direction
  // (consistent with addAdjacentPairs()
  TriangleFill triangleFill;
  if (m_gridLineOrientation == GridLineOrientation::Horizontal) {
    triangleFill.fill (image,
                       QPoint (xBL, yBL),
                       QPoint (xBR, yBR),
                       QPoint (xTR, yTR));
    triangleFill.fill (image,
                       QPoint (xBL, yBL),
                       QPoint (xTL, yTL),
                       QPoint (xTR, yTR));
  } else {
    triangleFill.fill (image,
                       QPoint (yBL, xBL),
                       QPoint (yBR, xBR),
                       QPoint (yTR, xTR));
    triangleFill.fill (image,
                       QPoint (yBL, xBL),
                       QPoint (yTL, xTL),
                       QPoint (yTR, xTR));    
  }
}

QImage GridHealer::healed (const QImage &imageAfterGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::healed";

  QImage image (imageAfterGridRemoval);

  doHealing (image);

  return image;
}

bool GridHealer::pixelIsBlack (const QImage &image,
                               int x,
                               int y) const
{
  QRgb rgb = image.pixel (x, y);
  return qGray (rgb) < 128;
}
