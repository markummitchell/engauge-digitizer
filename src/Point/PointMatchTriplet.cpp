/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "PointMatchTriplet.h"

PointMatchTriplet::PointMatchTriplet(int x,
                                     int y,
                                     double correlation) :
  m_x (x),
  m_y (y),
  m_correlation (correlation)
{
}

double PointMatchTriplet::correlation () const
{
  return m_correlation;
}

bool PointMatchTriplet::operator<(const PointMatchTriplet &other) const
{
  // qSort wants to sort by ascending correlation, but we want to sort by descending correlation. We
  // compensate by comparing correlations numerically and flipping the result

  bool isLess = false;

  if (m_correlation == other.correlation ()) {

    // To reduce jumping around, we prefer points on the left when the correlations are equal
    isLess = (m_x < other.x());

  } else {

    isLess = !(m_correlation < other.correlation ());

  }

  return isLess;
}

QPoint PointMatchTriplet::point() const
{
  return QPoint (m_x,
                 m_y);
}

int PointMatchTriplet::x() const
{
  return m_x;
}

int PointMatchTriplet::y() const
{
  return m_y;
}
