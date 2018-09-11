/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_HEALER_H
#define GRID_HEALER_H

#include <QImage>
#include <QMap>

class DocumentModelGridRemoval;
class QImage;

/// Saved adjacent pairs
typedef QList<QPoint> AdjacentPairHalves;

/// (X,Y) pairs for horizontal lines, and (Y,X) pairs for vertical lines
typedef QMap<int, int> IndependentToDependent;

/// Class that 'heals' the curves after one grid line has been removed. Specifically, gaps that
/// span the pixels in the removed grid line are filled in, when a black pixel on one side of the
/// gap is across from a black pixel on the other side of the pixel
///
/// A range is defined as a continous set of pixels on the same side of the gap
class GridHealer
{
 public:

  /// Orientation of gridline
  enum GridLineOrientation {
    Horizontal,
    Vertical
  };

  /// Single constructor
  GridHealer(GridLineOrientation gridLineOrientation,
             const DocumentModelGridRemoval &modelGridRemoval);

  /// Add two points on either side of a gap, if they are black
  void addAdjacentPoints (const QImage &image,
                          int x0,
                          int y0,
                          int x1,
                          int y1);

  /// Return healed image
  QImage healed (const QImage &imageAfterGridRemoval);

 private:
  GridHealer();

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

  void detailedLogInputs () const;
  void detailedLogOutputs (int xBelowStart,
                           int xBelowEnd,
                           int xAboveEnd,
                           int xAboveStart) const;

  /// Guts of the algorithm in which sequences of black pixels across the gap from each other
  /// are filled in. Specifically, trapezoids with endpoints separated by no more than the
  /// closest distance are filled in. A greedy algorithm is used which makes each trapezoid as
  /// big as possible
  void doHealing (QImage &image);

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

  /// Fill trapezoid with bottom left, bottom right, top right, and top left points
  void fillTrapezoid (QImage &image,
                      int xBL, int yBL,
                      int xBR, int yBR,
                      int xTR, int yTR,
                      int xTL, int yTL);

  /// Apply blackPixelRegionIsBigEnough to regions around each of two points
  bool pointsAreGood (const QImage &image,
                      int i0,
                      int d0,
                      int i3,
                      int d3) const;

  /// Horizontal or vertical?
  GridLineOrientation m_gridLineOrientation;
  
  DocumentModelGridRemoval m_modelGridRemoval;

  /// Pixels on either side of the gap
  IndependentToDependent m_blackPixelsBelow; // Black pixels in -x or -y direction
  IndependentToDependent m_blackPixelsAbove; // Black pixels in +x or +y direction
  int m_gapSeparation; // Pixel distance between vertical point pairs

};

#endif // GRID_HEALER_H
