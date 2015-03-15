/* "THE BEER-WARE LICENSE" (Revision 42): Devin Lane wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return. */

#include "SplineCoeff.h"

SplineCoeff::SplineCoeff(double t,
                         const SplinePair &a,
                         const SplinePair &b,
                         const SplinePair &c,
                         const SplinePair &d) :
  m_t(t),
  m_a(a),
  m_b(b), 
  m_c(c),
  m_d(d) 
{
}
  
bool SplineCoeff::operator<(const SplineCoeff &c) const 
{
  return m_t < c.t();
}

bool SplineCoeff::operator<(double t) const
{
  return m_t < t;
}

SplinePair SplineCoeff::a () const
{
  return m_a;
}

SplinePair SplineCoeff::b () const
{
  return m_b;
}

SplinePair SplineCoeff::c () const
{
  return m_c;
}

SplinePair SplineCoeff::d () const
{
  return m_d;
}

SplinePair SplineCoeff::eval(double t) const
{
  double deltat = t - m_t;
  return m_a + m_b * deltat + m_c * (deltat * deltat) + m_d * (deltat * deltat * deltat);
}

double SplineCoeff::t () const
{
  return m_t;
}
