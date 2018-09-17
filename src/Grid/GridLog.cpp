/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "gnuplot.h"
#include "GridIndependentToDependent.h"
#include "GridLog.h"
#include <iostream>
#include <QFile>
#include <QPoint>
#include <QTextStream>

// Whole image is too much information so only stuff near this center point is included
const int DETAILED_CENTER_X = 704;
const int DETAILED_CENTER_Y = 521;
const int DETAILED_RADIUS = 8;

// Derived constants
const int DETAILED_X_MIN = DETAILED_CENTER_X - DETAILED_RADIUS;
const int DETAILED_X_MAX = DETAILED_CENTER_X + DETAILED_RADIUS;
const int DETAILED_Y_MIN = DETAILED_CENTER_Y - DETAILED_RADIUS;
const int DETAILED_Y_MAX = DETAILED_CENTER_Y + DETAILED_RADIUS;

GridLog::GridLog(bool isGnuplot) :
  m_isGnuplot (isGnuplot),
  m_logStr (&m_log)
{
  if (m_isGnuplot) {

    // Show border around region of interest
    m_logStr << DETAILED_X_MIN << " " << - DETAILED_Y_MIN << "\n";
    m_logStr << DETAILED_X_MAX << " " << - DETAILED_Y_MIN << "\n";
    m_logStr << DETAILED_X_MAX << " " << - DETAILED_Y_MAX << "\n";
    m_logStr << DETAILED_X_MIN << " " << - DETAILED_Y_MAX << "\n";
    m_logStr << DETAILED_X_MIN << " " << - DETAILED_Y_MIN << "\n";
    m_logStr << "\n";
  }
}

GridLog::~GridLog()
{
  if (m_isGnuplot) {

    // Save the log stream that has been accumulated in memory
    QString filename ("grid.gnuplot");
    QFile file (filename);
    QTextStream fileStr (&file);

    std::cout << GNUPLOT_FILE_MESSAGE.toLatin1().data() << filename.toLatin1().data() << "\n";

    file.open (QIODevice::WriteOnly | QIODevice::Append);
    fileStr << m_log;
    file.close ();
  }
}

bool GridLog::inBounds (int x, int y) const
{
  return
      DETAILED_X_MIN < x &&
      DETAILED_Y_MIN < y &&
      x < DETAILED_X_MAX &&
      y < DETAILED_Y_MAX;
}

void GridLog::showInputPixel (const QPoint &p,
                              double halfWidth)
{
  int x = p.x();
  int y = p.y();

  if (DETAILED_X_MIN <= x &&
      DETAILED_Y_MIN <= y &&
      x <= DETAILED_X_MAX &&
      y <= DETAILED_Y_MAX) {

    m_logStr << x - halfWidth << " " << - (y - halfWidth) << "\n";
    m_logStr << x + halfWidth << " " << - (y - halfWidth) << "\n";
    m_logStr << x + halfWidth << " " << - (y + halfWidth) << "\n";
    m_logStr << x - halfWidth << " " << - (y + halfWidth) << "\n";
    m_logStr << x - halfWidth << " " << - (y - halfWidth) << "\n";
    m_logStr << "\n";
  }
}

void GridLog::showOutputScanLinePixel (int x,
                                       int y,
                                       double radius)
{
  if (m_isGnuplot && inBounds (x, y)) {

    // Draw a diamond
    m_logStr << x          << " " << - (y - radius) << "\n";
    m_logStr << x + radius << " " << - (y         ) << "\n";
    m_logStr << x          << " " << - (y + radius) << "\n";
    m_logStr << x - radius << " " << - (y         ) << "\n";
    m_logStr << x          << " " << - (y - radius) << "\n";
    m_logStr << "\n";
  }
}

void GridLog::showOutputTrapezoid (const QPoint &p0,
                                   const QPoint &p1,
                                   const QPoint &p2,
                                   const QPoint &p3)
{
  if (m_isGnuplot) {

    // Log if any pixel is in the region of interest
    if (inBounds (p0.x(), p0.y()) ||
        inBounds (p1.x(), p1.y()) ||
        inBounds (p2.x(), p2.y()) ||
        inBounds (p3.x(), p3.y())) {

      m_logStr << p0.x() << " " << - p0.y() << "\n";
      m_logStr << p1.x() << " " << - p1.y() << "\n";
      m_logStr << p2.x() << " " << - p2.y() << "\n";
      m_logStr << p3.x() << " " << - p3.y() << "\n";
      m_logStr << p0.x() << " " << - p0.y() << "\n";
      m_logStr << "\n";
    }
  }
}
