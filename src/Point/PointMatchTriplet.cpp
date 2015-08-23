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
  return other.correlation();
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
