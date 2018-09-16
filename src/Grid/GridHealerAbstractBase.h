/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_HEALER_ABSTRACT_BASE_H
#define GRID_HEALER_ABSTRACT_BASE_H

#include "DocumentModelGridRemoval.h"
#include "GridIndependentToDependent.h"
#include <QImage>

class GridLog;
class QImage;
class QTextStream;

// Trick to discriminate horizontal and vertical pixels is to use different sizes
const double HALFWIDTH_HORIZONTAL = 0.46;
const double HALFWIDTH_VERTICAL = 0.54;

/// Save one half of a mutual pair
typedef QList<QPoint> MutualPairHalves;

/// Class that 'heals' the curves after one grid line has been removed. Specifically, gaps that
/// span the pixels in the removed grid line are filled in, when a black pixel on one side of the
/// gap is across from a black pixel on the other side of the pixel
///
/// A range is defined as a continous set of pixels on the same side of the gap
class GridHealerAbstractBase
{
 public:

  /// Single constructor
  GridHealerAbstractBase(GridLog &gridLog,
                         const DocumentModelGridRemoval &modelGridRemoval);
  virtual ~GridHealerAbstractBase();

  /// Add two points on either side of a gap. Later, after removal, the black points will be processed
  void addMutualPair (int x0,
                      int y0,
                      int x1,
                      int y1);

  /// Threshold number of pixels in a region to be considered too-small or big-enough
  static int pixelCountInRegionThreshold (const DocumentModelGridRemoval &modelGridRemoval);

  /// Return healed image after grid removal
  void healed (QImage &image);

 protected:

  /// Apply mutual pair points after all grid removal is done
  virtual void applyMutualPairs (const QImage &image) = 0;

  /// Guts of the algorithm in which sequences of black pixels across the gap from each other
  /// are filled in. Specifically, trapezoids with endpoints separated by no more than the
  /// closest distance are filled in. A greedy algorithm is used which makes each trapezoid as
  /// big as possible
  virtual void doHealingAcrossGaps (QImage &image) = 0;

  /// Fill trapezoid with bottom left, bottom right, top right, and top left points
  void fillTrapezoid (QImage &image,
                      int xBL, int yBL,
                      int xBR, int yBR,
                      int xTR, int yTR,
                      int xTL, int yTL);

  /// Logging get method
  GridLog &gridLog ();

  /// Max point separation get method
  double maxPointSeparation () const;

  /// DocumentModelGridRemoval get method
  DocumentModelGridRemoval &modelGridRemoval();

  /// Mutual pair halves for below grid line
  const MutualPairHalves &mutualPairHalvesAbove () const;

  /// Mutual pair halves for above grid line
  const MutualPairHalves &mutualPairHalvesBelow () const;

  /// Apply blackPixelRegionIsBigEnough to regions around each of two points
  bool pointsAreGood (const QImage &image,
                      int x0,
                      int y0,
                      int x1,
                      int y1) const;

  /// Gap separation set method
  void saveGapSeparation (double gapSeparation);

 private:
  GridHealerAbstractBase();

  /// Determine if the specified black pixel is connected enough other black pixels to be
  /// considered big enough to be a real thing worth connecting to. In images with a large number
  /// of grid lines in either direction (=several dozen) there can be many little artifacts (=black
  /// pixels spread around here and there that should be ignored). If these little artifacts are
  /// not removed before healing then a long line will be drawn to each from the actual curves
  /// (seen as much bigger artifacts), breaking up those curves into smaller segments which
  /// unnecessarily complicates segment fill
  bool blackPixelRegionIsBigEnough (const QImage &image,
                                    int x,
                                    int y) const;

  /// Healing for four points defined by below range endpoints and above range endpoints
  void doHealingOnBelowAndAboveRangePair (QImage &image,
                                          int xBelowStart,
                                          int xBelowEnd,
                                          int xAboveStart,
                                          int xAboveEnd);

  /// Healing for one specific range of continuous below pixels
  void doHealingOnBelowRange (QImage &image,
                              int xBelowStart,
                              int xBelowEnd,
                              int maxHorSep);

  DocumentModelGridRemoval m_modelGridRemoval;

  int m_maxPointSeparation; // Pixel distance between two connected points

  // Store opposing mutual pair points as each grid line is removed, then after all removals are
  // done (when complex vertical/horizontal interactions have finished) we heal
  // across these mutual pairs
  MutualPairHalves m_mutualPairHalvesBelow;
  MutualPairHalves m_mutualPairHalvesAbove;

  GridLog &m_gridLog;
};

#endif // GRID_HEALER_ABSTRACT_BASE_H
