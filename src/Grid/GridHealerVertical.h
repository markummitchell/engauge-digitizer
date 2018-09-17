/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_HEALER_VERTICAL_H
#define GRID_HEALER_VERTICAL_H

#include "GridHealerAbstractBase.h"
#include "GridIndependentToDependent.h"
#include <QImage>

class DocumentModelGridRemoval;
class GridLog;
class QImage;
class QTextStream;

/// Subclass of GridHealerAbstractBase for vertical lines
class GridHealerVertical : public GridHealerAbstractBase
{
 public:

  /// Single constructor
  GridHealerVertical(GridLog &gridLog,
                     const DocumentModelGridRemoval &modelGridRemoval);

  virtual void applyMutualPairs (const QImage &image);
  virtual void doHealingAcrossGaps (QImage &image);

 private:
  GridHealerVertical();

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
  GridIndependentToDependent m_blackPixelsBelow; // (y,x) pairs in line parallel to vertical line on -x side
  GridIndependentToDependent m_blackPixelsAbove; // (y,x) pairs in line parallel to vertical line on +x side
};

#endif // GRID_HEALER_VERTICAL_H
