/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "DocumentModelGridRemoval.h"
#include "EngaugeAssert.h"
#include "GridHealer.h"
#include "Logger.h"
#include "Pixels.h"
#include <QImage>
#include <qmath.h>
#include <QRgb>
#include <QTextStream>
#include "TriangleFill.h"

// Enable large amount of debug spew
//#define DETAILED_LOGGING 1

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
  Pixels pixels (image);

  // Convert (x,y) pairs to (independent,dependent) pairs
  int i0 = x0, d0 = y0, i1 = x1, d1 = y1;
  if (m_gridLineOrientation == GridHealer::GridLineOrientation::Vertical) {
    i0 = y0;
    d0 = x0;
    i1 = y1;
    d1 = x1;
  }

  // Save (independent,dependent) pairs
  if (pixels.pixelIsBlack (image, x0, y0)) {
    m_blackPixelsBelow [i0] = d0;
  }
  if (pixels.pixelIsBlack (image, x1, y1)) {
    m_blackPixelsAbove [i1] = d1;
  }
  m_gapSeparation = qAbs (d1 - d0);
}

bool GridHealer::blackPixelRegionIsBigEnough (const QImage &image,
                                              int i,
                                              int d) const
{
  // Convert from (independent,dependent) pair to (x,y) pair
  int x = i, y = d;
  if (m_gridLineOrientation == GridHealer::GridLineOrientation::Vertical) {
    x = d;
    y = i;
  }

  Pixels pixels  (image);
  int count = pixels.countBlackPixelsAroundPoint (x,
                                                  y,
                                                  m_modelGridRemoval.closeDistance());
  return (count >= m_modelGridRemoval.closeDistance ());
}

#ifdef DETAILED_LOGGING
void GridHealer::detailedLogInputs () const
{
  const int FIRST_CHARACTERS = 80;

  // In LOG4CPP_INFO_S we dump out the first few black pixels
  QString below, above;
  QTextStream strBelow (&below), strAbove (&above);
  IndependentToDependent::const_iterator itrBelow, itrAbove;
  QString delimiter;

  // Iterate through values
  for (itrBelow = m_blackPixelsBelow.begin (); itrBelow != m_blackPixelsBelow.end (); itrBelow++) {
    strBelow << delimiter << itrBelow.key();
    delimiter = ", ";
  }
  delimiter = "";
  for (itrAbove = m_blackPixelsAbove.begin (); itrAbove != m_blackPixelsAbove.end (); itrAbove++) {
    strAbove << delimiter << itrAbove.key();
    delimiter = ", ";
  }

  // Indicate some text was dropped if appropriate
  if (below.count() > FIRST_CHARACTERS) {
    below.truncate (FIRST_CHARACTERS);
    below = below + "...";
  }
  if (above.count() > FIRST_CHARACTERS) {
    above.truncate (FIRST_CHARACTERS);
    above = above + "...";
  }

  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::detailedLogInputs "
                              << " below=(" << below.toLatin1().data() << ")"
                              << " above=(" << above.toLatin1().data() << ")";
}
#else
void GridHealer::detailedLogInputs() const
{
}
#endif

#ifdef DETAILED_LOGGING
void GridHealer::detailedLogOutputs (int xBelowStart,
                                     int xBelowEnd,
                                     int xAboveEnd,
                                     int xAboveStart) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::detailedLogOutputs "
                              << xBelowStart << "<=xBelow<=" << xBelowEnd << " "
                              << xAboveStart << "<=xAbove<=" << xAboveEnd;
}
#else
void GridHealer::detailedLogOutputs (int, int, int, int) const
{
}
#endif

void GridHealer::doHealing (QImage &image)
{
  // LOG4CPP_INFO_S is in detailedLogInputs
  detailedLogInputs ();

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
  // LOG4CPP_INFO_S is in detailedLogOutputs
  detailedLogOutputs (xBelowStart,
                      xBelowEnd,
                      xAboveEnd,
                      xAboveStart);

  int x0 = xBelowStart;
  int x1 = xBelowEnd;
  int x2 = xAboveEnd;
  int x3 = xAboveStart;
  int y0 = m_blackPixelsBelow [xBelowStart];
  int y1 = m_blackPixelsBelow [xBelowEnd  ];
  int y2 = m_blackPixelsAbove [xAboveEnd  ];
  int y3 = m_blackPixelsAbove [xAboveStart];

  if (pointsAreGood (image, x0, y0, x3, y3)) {

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
  Pixels pixels (image);

  // Convert input (independent,dependent) pairs to (x,y) pairs
  int xBL = iBL, yBL = dBL, xBR = iBR, yBR = dBR, xTR = iTR, yTR = dTR, xTL = iTL, yTL = dTL;
  if (m_gridLineOrientation == GridHealer::GridLineOrientation::Vertical) {
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

  if (!pixels.pixelIsBlack(image, xBL, yBL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad bottom left point";
  }
  if (!pixels.pixelIsBlack(image, xBR, yBR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad bottom right point";
  }
  if (!pixels.pixelIsBlack(image, xTR, yTR)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad top right point";
  }
  if (!pixels.pixelIsBlack(image, xTL, yTL)) {
    LOG4CPP_ERROR_S ((*mainCat)) << "GridHealer::fillTrapezoid has bad top left point";
  }

  // Any quadrilateral (including this trapezoid) can be considered the union of two triangles. We
  // convert from the (independent,dependent) variable pair to (x,y) pair depending on gridline direction
  // (consistent with addAdjacentPairs()
  TriangleFill triangleFill;
  triangleFill.fill (image,
                     QPoint (xBL, yBL),
                     QPoint (xBR, yBR),
                     QPoint (xTR, yTR));
  triangleFill.fill (image,
                     QPoint (xBL, yBL),
                     QPoint (xTL, yTL),
                     QPoint (xTR, yTR));
}

QImage GridHealer::healed (const QImage &imageAfterGridRemoval)
{
  LOG4CPP_INFO_S ((*mainCat)) << "GridHealer::healed";

  QImage image (imageAfterGridRemoval);

  doHealing (image);

  return image;
}

bool GridHealer::pointsAreGood (const QImage &image,
                                int i0,
                                int d0,
                                int i3,
                                int d3) const
{
  Pixels pixels (image);

  // For now we will use the close distance as the minimum pixel count
  int stopCountAt = m_modelGridRemoval.closeDistance();

  // Convert (independent,dependent) pair to (x,y) pair
  int x0 = i0, y0 = d0, x3 = i3, y3 = d3;
  if (m_gridLineOrientation == GridHealer::GridLineOrientation::Vertical) {
    x0 = d0;
    y0 = i0;
    x3 = d3;
    y3 = i3;
  }

  // Skip if either endpoint is an unwanted artifact. Look at start point below (since it is connected
  // to the end point below), and the start point above (which is connected to the end point above)
  return ((pixels.countBlackPixelsAroundPoint (x0, y0, stopCountAt) >= stopCountAt) &&
          (pixels.countBlackPixelsAroundPoint (x3, y3, stopCountAt) >= stopCountAt));
}
