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

  /// Guts of the algorithm in which sequences of black pixels across the gap from each other
  /// are filled in. Specifically, trapezoids with endpoints separated by no more than the
  /// closest distance are filled in. A greedy algorithm is used which makes each trapezoid as
  /// big as possible
  void doHealing (QImage &image);

  /// Fill trapezoid with bottom left, bottom right, top right, and top left points
  void fillTrapezoid (QImage &image,
                      int xBL, int yBL,
                      int xBR, int yBR,
                      int xTR, int yTR,
                      int xTL, int yTL);

  bool pixelIsBlack (const QImage &image,
                     int x,
                     int y) const;

  /// Horizontal or vertical?
  GridLineOrientation m_gridLineOrientation;
  
  DocumentModelGridRemoval m_modelGridRemoval;

  /// Horizontal lines
  IndependentToDependent m_blackPixelsBelow; // Black pixels in -x or -y direction
  IndependentToDependent m_blackPixelsAbove; // Black pixels in +x or +y direction
  int m_gapSeparation; // Pixel distance between vertical point pairs

};

#endif // GRID_HEALER_H
