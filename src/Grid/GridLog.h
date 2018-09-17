/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_LOG_H
#define GRID_LOG_H

#include "GridIndependentToDependent.h"
#include <QString>
#include <QTextStream>

/// Class that does special logging for GridLog and GridRemoval classes. Output file is appended to
/// since multiple instances of this class are expected to be used each time this application is executed
class GridLog
{
 public:

  /// Single constructor
  GridLog(bool isGnuplot);
  virtual ~GridLog();

  /// Show pixels that are inputs to GridHealer
  void showInputPixel (const QPoint &p,
                       double halfWidth);

  /// Show scan line pixel that is the output of GridHealer
  void showOutputScanLinePixel (int x,
                                int y,
                                double radius);

  /// Show trapezoids that are intermediate results in GridHealer
  void showOutputTrapezoid (const QPoint &p0,
                            const QPoint &p1,
                            const QPoint &p2,
                            const QPoint &p3);

private:
  GridLog();

  bool inBounds (int x, int y) const;

  bool m_isGnuplot;
  QString m_log;
  QTextStream m_logStr;
};

#endif // GRID_LOG_H
