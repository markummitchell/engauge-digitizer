#include "SplinePair.h"

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

SplinePair::SplinePair(const SplinePair&other) :
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

double SplinePair::x() const
{
  return m_x;
}

double SplinePair::y() const
{
  return m_y;
}
