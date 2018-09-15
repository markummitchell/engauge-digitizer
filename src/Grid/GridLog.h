/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_LOG_H
#define GRID_LOG_H

#include "GridIndependentToDependent.h"
#include "GridLineOrientation.h"
#include <QString>
#include <QTextStream>

/// Class that does special logging for GridLog and GridRemoval classes. Output file is appended to
/// since multiple instances of this class are expected to be used each time this application is executed
class GridLog
{
 public:

  /// Single constructor
  GridLog(GridLineOrientation m_gridLineOrientation);
  virtual ~GridLog();

  /// Show pixels that are inputs to GridHealer
  void showInputPixels (const GridIndependentToDependent &blackPixelsBelow,
                        const GridIndependentToDependent &blackPixelsAbove);

  /// Show scan line pixel that is the output of GridHealer
  void showOutputScanLinePixel (int x,
                                int y,
                                double radius);

  /// Show trapezoids that are intermediate results in GridHealer
  void showOutputTrapezoids (int x0,
                             int x1,
                             int x2,
                             int x3,
                             int y0,
                             int y1,
                             int y2,
                             int y3);

private:
  GridLog();

  bool inBounds (int x, int y) const;
  void showInputPixelsSingle (const GridIndependentToDependent &blackPixels);

  const GridLineOrientation m_gridLineOrientation;
  QString m_log;
  QTextStream m_logStr;
};

#endif // GRID_LOG_H
