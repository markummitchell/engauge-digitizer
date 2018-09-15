/******************************************************************************************************
 * (C) 2018 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "GridIndependentToDependent.h"
#include "GridLog.h"
#include <QFile>
#include <QTextStream>

// Enable large amount of debug spew
#define DETAILED_LOGGING 1

// Whole image is too much information so only stuff near this center point is included
const int DETAILED_CENTER_X = 704;
const int DETAILED_CENTER_Y = 521;
const int DETAILED_RADIUS = 8;

// Derived constants
const int DETAILED_X_MIN = DETAILED_CENTER_X - DETAILED_RADIUS;
const int DETAILED_X_MAX = DETAILED_CENTER_X + DETAILED_RADIUS;
const int DETAILED_Y_MIN = DETAILED_CENTER_Y - DETAILED_RADIUS;
const int DETAILED_Y_MAX = DETAILED_CENTER_Y + DETAILED_RADIUS;

GridLog::GridLog(GridLineOrientation gridLineOrientation) :
  m_gridLineOrientation (gridLineOrientation),
  m_logStr (&m_log)
{
#ifdef DETAILED_LOGGING
  // Show border around region of interest
  m_logStr << DETAILED_X_MIN << " " << - DETAILED_Y_MIN << "\n";
  m_logStr << DETAILED_X_MAX << " " << - DETAILED_Y_MIN << "\n";
  m_logStr << DETAILED_X_MAX << " " << - DETAILED_Y_MAX << "\n";
  m_logStr << DETAILED_X_MIN << " " << - DETAILED_Y_MAX << "\n";
  m_logStr << DETAILED_X_MIN << " " << - DETAILED_Y_MIN << "\n";
  m_logStr << "\n";
#endif
}

GridLog::~GridLog()
{
#ifdef DETAILED_LOGGING

  // Save the log stream that has been accumulated in memory to the end of the log file
  QFile file ("gnuplot.in");
  QTextStream fileStr (&file);

  file.open (QIODevice::WriteOnly | QIODevice::Append);
  fileStr << m_log;
  file.close ();
#endif
}

bool GridLog::inBounds (int x, int y) const
{
  return
      DETAILED_X_MIN <= x &&
      DETAILED_Y_MIN <= y &&
      x <= DETAILED_X_MAX &&
      y <= DETAILED_Y_MAX;
}

void GridLog::showInputPixels (const GridIndependentToDependent &blackPixelsBelow,
                               const GridIndependentToDependent &blackPixelsAbove)
{
  showInputPixelsSingle (blackPixelsBelow);
  showInputPixelsSingle (blackPixelsAbove);
}

void GridLog::showInputPixelsSingle (const GridIndependentToDependent &blackPixels)
{
  // Trick to discriminate horizontal and vertical pixels is to use different sizes
  double halfWidth = (m_gridLineOrientation == GridLineOrientation::Vertical) ? 0.46 : 0.54;

  GridIndependentToDependent::const_iterator itr;
  for (itr = blackPixels.begin (); itr != blackPixels.end (); itr++) {
    int x = itr.value();
    int y = itr.key();
    if (m_gridLineOrientation == GridLineOrientation::Horizontal) {
      x = itr.key();
      y = itr.value();
    }

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
}

#ifdef DETAILED_LOGGING
void GridLog::showOutputScanLinePixel (int x,
                                       int y,
                                       double radius)
{
  if (inBounds (x, y)) {

    // Draw a diamond
    m_logStr << x          << " " << - (y - radius) << "\n";
    m_logStr << x + radius << " " << - (y         ) << "\n";
    m_logStr << x          << " " << - (y + radius) << "\n";
    m_logStr << x - radius << " " << - (y         ) << "\n";
    m_logStr << x          << " " << - (y - radius) << "\n";
    m_logStr << "\n";
  }
}
#else
void GridLog::showOutputScanLinePixel(int, int, double)
{
}
#endif

#ifdef DETAILED_LOGGING
void GridLog::showOutputTrapezoids (int x0,
                                    int x1,
                                    int x2,
                                    int x3,
                                    int y0,
                                    int y1,
                                    int y2,
                                    int y3)
{
  // Log if any pixel is in the region of interest
  if (inBounds (x0, y0) || inBounds (x1, y1) || inBounds (x2, y2) || inBounds (x3, y3)) {

    m_logStr << x0 << " " << - y0 << "\n";
    m_logStr << x1 << " " << - y1 << "\n";
    m_logStr << x2 << " " << - y2 << "\n";
    m_logStr << x3 << " " << - y3 << "\n";
    m_logStr << x0 << " " << - y0 << "\n";
    m_logStr << "\n";
  }
}
#else
void GridLog::showOutputTrapezoids (int,
                                    int,
                                    int,
                                    int)
{
}
#endif
