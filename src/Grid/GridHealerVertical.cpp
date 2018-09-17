/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GridHealerVertical.h"
#include "GridIndependentToDependent.h"
#include "GridLog.h"
#include "Pixels.h"
#include <qmath.h>

GridHealerVertical::GridHealerVertical(GridLog &gridLog,
                                       const DocumentModelGridRemoval &modelGridRemoval) :
  GridHealerAbstractBase (gridLog,
                          modelGridRemoval)
{
}

void GridHealerVertical::applyMutualPairs (const QImage &image)
{
  MutualPairHalves::const_iterator itrBelow = mutualPairHalvesBelow().begin();
  MutualPairHalves::const_iterator itrAbove = mutualPairHalvesAbove().begin();

  while (itrBelow != mutualPairHalvesBelow().end() &&
         itrAbove != mutualPairHalvesAbove().end()) {

    QPoint p0 = *(itrBelow++);
    QPoint p1 = *(itrAbove++);

    // Save (independent,dependent) pairs
    if (Pixels::pixelIsBlack (image, p0.x(), p0.y())) {
      m_blackPixelsBelow [p0.y()] = p0.x();
    }

    if (Pixels::pixelIsBlack (image, p1.x(), p1.y())) {
      m_blackPixelsAbove [p1.y()] = p1.x();
    }

    saveGapSeparation (qAbs (p1.x() - p0.x()));
  }
}

void GridHealerVertical::doHealingAcrossGaps (QImage &image)
{
  // LOG4CPP_INFO_S is replaced by GridLog
  GridIndependentToDependent::const_iterator itrBelow, itrAbove;
  for (itrBelow = m_blackPixelsBelow.begin(); itrBelow != m_blackPixelsBelow.end(); itrBelow++) {
    QPoint p (itrBelow.value(),
              itrBelow.key());
    gridLog().showInputPixel(p,
                             HALFWIDTH_VERTICAL);
  }
  for (itrAbove = m_blackPixelsAbove.begin(); itrAbove != m_blackPixelsAbove.end(); itrAbove++) {
    QPoint p (itrAbove.value(),
              itrAbove.key());
    gridLog().showInputPixel(p,
                             HALFWIDTH_VERTICAL);
  }

  // Algorithm requires at least one point in each of the lists
  if (m_blackPixelsBelow.count() > 0 &&
      m_blackPixelsAbove.count() > 0) {

    int yFirst = qMin (m_blackPixelsBelow.firstKey (),
                       m_blackPixelsAbove.firstKey ());
    int yLast = qMax (m_blackPixelsBelow.lastKey (),
                      m_blackPixelsAbove.lastKey ());

    int yBelowEnd = 0; // Used by inner loop to skip to this iterator value

    for (int yBelowStart = yFirst; yBelowStart <= yLast; yBelowStart++) {

      if ((yBelowEnd < yBelowStart) &&
          m_blackPixelsBelow.contains (yBelowStart)) {

        // This could be the start of a new trapezoid. Find where the range on the same side ends
        int yBelowOutOfBounds = yLast + 1; // Value forcing transition to out of range

        for (yBelowEnd = yBelowStart + 1; yBelowEnd <= yBelowOutOfBounds; yBelowEnd++) {

          if (!m_blackPixelsBelow.contains (yBelowEnd) || (yBelowEnd == yBelowOutOfBounds)) {

            doHealingOnBelowRange (image,
                                   yBelowStart,
                                   yBelowEnd,
                                   maxPointSeparation());

            // Go back to outer loop, which will skip to xBelowEnd
            break;
          }
        }
      }
    }
  }
}

void GridHealerVertical::doHealingOnBelowAndAboveRangePair (QImage &image,
                                                            int yBelowStart,
                                                            int yBelowEnd,
                                                            int yAboveStart,
                                                            int yAboveEnd)
{
  // LOG4CPP_INFO_S is replaced by GridLog

  int x0 = m_blackPixelsBelow [yBelowStart];
  int x1 = m_blackPixelsBelow [yBelowEnd  ];
  int x2 = m_blackPixelsAbove [yAboveEnd  ];
  int x3 = m_blackPixelsAbove [yAboveStart];
  int y0 = yBelowStart;
  int y1 = yBelowEnd;
  int y2 = yAboveEnd;
  int y3 = yAboveStart;

  gridLog().showOutputTrapezoid (QPoint (x0, y0),
                                 QPoint (x1, y1),
                                 QPoint (x2, y2),
                                 QPoint (x3, y3));

  if (pointsAreGood (image, x0, y0, x2, y2)) {

    // Big enough so keep it. Four points that define the trapezoid to be filled in
    fillTrapezoid (image,
                   x0, y0,
                   x1, y1,
                   x2, y2,
                   x3, y3);
  }
}

void GridHealerVertical::doHealingOnBelowRange (QImage &image,
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
