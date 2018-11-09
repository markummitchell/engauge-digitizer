/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "SplinePair.h"

using namespace std;

SplinePair::SplinePair () :
  m_x (0.0),
  m_y (0.0)
{
}

SplinePair::SplinePair (double scalar) :
  m_x (scalar),
  m_y (scalar)
{
}

SplinePair::SplinePair(double x,
                       double y) :
  m_x (x),
  m_y (y)
{
}

SplinePair &SplinePair::operator=(const SplinePair &other)
{
  m_x = other.x();
  m_y = other.y();

  return *this;
}

SplinePair::SplinePair(const SplinePair &other) :
  m_x (other.x()),
  m_y (other.y())
{
}

SplinePair SplinePair::operator+(const SplinePair &other) const
{
  SplinePair result (m_x + other.x(),
                     m_y + other.y());

  return result;
}

SplinePair SplinePair::operator-(const SplinePair &other) const
{
  SplinePair result (m_x - other.x(),
                     m_y - other.y());

  return result;
}

SplinePair SplinePair::operator*(const SplinePair &other) const
{
  SplinePair result (m_x * other.x(),
                     m_y * other.y());

  return result;
}

SplinePair SplinePair::operator/(const SplinePair &other) const
{
  SplinePair result (m_x / other.x(),
                     m_y / other.y());

  return result;
}

ostream &operator<< (ostream &str, const SplinePair &pair)
{
  str << "(" << pair.x() << "," << pair.y() << ")";

  return str;
}

double SplinePair::x() const
{
  return m_x;
}

double SplinePair::y() const
{
  return m_y;
}
