/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_HEALER_HORIZONTAL_H
#define GRID_HEALER_HORIZONTAL_H

#include "GridHealerAbstractBase.h"
#include "GridIndependentToDependent.h"
#include <QImage>

class DocumentModelGridRemoval;
class GridLog;
class QImage;
class QTextStream;

/// Subclass of GridHealerAbstractBase for horizontal lines
class GridHealerHorizontal : public GridHealerAbstractBase
{
 public:

  /// Single constructor
  GridHealerHorizontal(GridLog &gridLog,
                       const DocumentModelGridRemoval &modelGridRemoval);

  virtual void applyMutualPairs (const QImage &image);
  virtual void doHealingAcrossGaps (QImage &image);

 private:
  GridHealerHorizontal();

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

  /// Pixels on either side of the gap
  GridIndependentToDependent m_blackPixelsBelow; // (x,y) pairs in line parallel to vertical line on -y side
  GridIndependentToDependent m_blackPixelsAbove; // (x,y) pairs in line parallel to vertical line on +y side
};

#endif // GRID_HEALER_HORIZONTAL_H
