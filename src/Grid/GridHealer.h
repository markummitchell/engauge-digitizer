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
class GridHealer
{
 public:
  /// Single constructor
  GridHealer(const DocumentModelGridRemoval &modelGridRemoval);

  /// Add two points on either side of a gap, if they are black
  void addAdjacentPoints (int x0,
                          int y0,
                          int x1,
                          int y1);

  /// Return healed image
  QImage healed (const QImage &imageAfterGridRemoval);

 private:
  GridHealer();

  /// Apply pairs that were saved earlier during grid removal algorithm
  void applyAdjacentPairs (const QImage &image);

  /// Guts of the algorithm in which sequences of black pixels across the gap from each other
  /// are filled in. Specifically, trapezoids with endpoints separated by no more than the
  /// closest distance are filled in. A greedy algorithm is used which makes each trapezoid as
  /// big as possible
  void doHealingHorizontal (QImage &image);
  void doHealingVertical (QImage &image);

  /// Fill trapezoid with bottom left, bottom right, top right, and top left points
  void fillTrapezoid (QImage &image,
                      int xBL, int yBL,
                      int xBR, int yBR,
                      int xTR, int yTR,
                      int xTL, int yTL);

  bool pixelIsBlack (const QImage &image,
                     int x,
                     int y) const;

  DocumentModelGridRemoval m_modelGridRemoval;

  // Adjacent pairs
  AdjacentPairHalves m_pairHalves0;
  AdjacentPairHalves m_pairHalves1;

  // Horizontal lines
  IndependentToDependent m_blackPixelsBelow; // Black pixels just below gap
  IndependentToDependent m_blackPixelsAbove; // Black pixels just above gap
  int m_verticalSeparation; // Pixel distance between vertical point pairs

  // Vertical lines
  IndependentToDependent m_blackPixelsLeft; // Black pixels just to the left of the gap
  IndependentToDependent m_blackPixelsRight; // Black pixels just to the right of the gap
  int m_horizontalSeparation; // Pixel distance between horizontal point pairs
};

#endif // GRID_HEALER_H
