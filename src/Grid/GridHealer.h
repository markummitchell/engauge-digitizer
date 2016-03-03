/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_HEALER_H
#define GRID_HEALER_H

#include <QMap>
#include <QPointF>
#include <QVector>

class DocumentModelGridRemoval;
class QImage;

enum PixelState {
  PIXEL_STATE_BACKGROUND, /// Background pixel in original image
  PIXEL_STATE_FOREGROUND, /// Foreground pixel in original image. May become PIXEL_STATE_REMOVED or PIXEL_STATE_BOUNDARY
  PIXEL_STATE_REMOVED,    /// Pixel removed because it belonged to a grid line
  PIXEL_STATE_ADJACENT,   /// Foreground pixel adjacent to a PIXEL_STATE_REMOVED
  PIXEL_STATE_HEALED,     /// Removed pixel that has been filled so a line crosses the gap from a removed grid line
  NUM_PIXEL_STATES
};

/// Each boundary group has its own number, starting at BOUNDARY_GROUP_FIRST
typedef int BoundaryGroup;

/// Each pixel can either have an enumerated state, or be assigned to a boundary group
typedef int PixelStateOrBoundaryGroup;

/// Map group to an associated point
typedef QMap<BoundaryGroup, QPointF> GroupNumberToPoint;

/// Class that 'heals' the curves after grid lines have been removed. Specifically, gaps that
/// span the pixels in the removed grid lines are filled in, if they are less than some epsilon value
class GridHealer
{
 public:
  /// Single constructor
  GridHealer(const QImage &imageBefore,
             const DocumentModelGridRemoval &modelGridRemoval);

  /// Remember that pixel was erased since it belongs to an grid line. In the image, erasure
  /// correponds to a foreground pixel being changed to the background color
  void erasePixel (int xCol,
                   int yRow);

  /// Heal the broken curve lines by spanning the gaps across the newly-removed grid lines
  void heal (QImage &imageToHeal);

 private:
  GridHealer();

  void connectCloseGroups(QImage &imageToHeal);
  void groupContiguousAdjacentPixels();
  void recursiveSearchForAdjacentPixels (int boundaryGroup,
                                         int row,
                                         int col,
                                         int &centroidCount,
                                         double &rowCentroidSum,
                                         double &colCentroidSum);

  // Mirror of original image
  QVector<QVector<PixelStateOrBoundaryGroup> > m_pixels;

  BoundaryGroup m_boundaryGroupNext;

  /// Hash table that returns centroid coordinates for each group
  GroupNumberToPoint m_groupNumberToCentroid;

  /// Hash table that returns a pixel in each group
  GroupNumberToPoint m_groupNumberToPixel;

  DocumentModelGridRemoval m_modelGridRemoval;
};

#endif // GRID_HEALER_H
