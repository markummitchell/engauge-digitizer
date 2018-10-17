/* "THE BEER-WARE LICENSE" (Revision 42): Devin Lane wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return. */

#include "EngaugeAssert.h"
#include <iostream>
#include "Logger.h"
#include "SplineAbstract.h"

using namespace std;

SplineAbstract::SplineAbstract()
{
}

SplineAbstract::~SplineAbstract()
{
}

void SplineAbstract::checkTIncrements (const vector<double> &t) const
{
  for (unsigned int i = 1; i < t.size(); i++) {
    double tStep = t[i] - t[i-1];

    // Failure here means the increment is not one, which it should be. The epsilon is much larger than roundoff
    // could produce
    ENGAUGE_ASSERT (qAbs (tStep - 1.0) < 0.0001);
  }
}

void SplineAbstract::computeControlPointsForIntervals ()
{
  int i, n = (int) m_xy.size() - 1;

  for (i = 0; i < n; i++) {
    const SplineCoeff &element = m_elements[i];

    // Derivative at P0 from (1-s)^3*P0+(1-s)^2*s*P1+(1-s)*s^2*P2+s^3*P3 with s=0 evaluates to 3(P1-P0). That
    // derivative must match the derivative of y=a+b*(t-ti)+c*(t-ti)^2+d*(t-ti)^3 with t=ti which evaluates to b.
    // So 3(P1-P0)=b
    SplinePair p1 = m_xy [i] + element.b() /
                    SplinePair (3.0);

    // Derivative at P2 from (1-s)^3*P0+(1-s)^2*s*P1+(1-s)*s^2*P2+s^3*P3 with s=1 evaluates to 3(P3-P2). That
    // derivative must match the derivative of y=a+b*(t-ti)+c*(t-ti)^2+d*(t-ti)^3 with t=ti+1 which evaluates to b+2*c+3*d
    SplinePair p2 = m_xy [i + 1] - (element.b() + SplinePair (2.0) * element.c() + SplinePair (3.0) * element.d()) /
                    SplinePair (3.0);

    m_p1.push_back (p1);
    m_p2.push_back (p2);
  }

  // Debug logging
  for (i = 0; i < (int) m_xy.size () - 1; i++) {
    LOG4CPP_DEBUG_S ((*mainCat)) << "Spline::computeControlPointsForIntervals" << " i=" << i
             << " xy=" << m_xy [i]
             << " elementt=" << m_elements[i].t()
             << " elementa=" << m_elements[i].a()
             << " elementb=" << m_elements[i].b()
             << " elementc=" << m_elements[i].c()
             << " elementd=" << m_elements[i].d()
             << " p1=" << m_p1[i]
             << " p2=" << m_p2[i];
  }
  i = m_xy.size() - 1;
  LOG4CPP_DEBUG_S ((*mainCat)) << "Spline::computeControlPointsForIntervals" << " i=" << i
                << " xy=" << m_xy [i];
}

void SplineAbstract::computeUntranslatedCoefficients (double aTranslated,
                                                      double bTranslated,
                                                      double cTranslated,
                                                      double dTranslated,
                                                      double tI,
                                                      double &aUntranslated,
                                                      double &bUntranslated,
                                                      double &cUntranslated,
                                                      double &dUntranslated) const
{
  // Expanding the equation using t translated as (t-ti) we get the equation using untranslated (t) as follows
  //   xy=d*t^3+
  //      (c-3*d*ti)*t^2+
  //      (b-2*c*ti+3*d*ti^2)*t+
  //      (a-b*ti+c*ti^2-d*ti^3)
  // which matches up with
  //   xy=d*t^3+
  //      c*t^2+
  //      b*t+
  //      a
  // Both equations are given in the header file documentation for this method
  aUntranslated = aTranslated - bTranslated * tI + cTranslated * tI * tI - dTranslated * tI * tI * tI;
  bUntranslated = bTranslated - 2.0 * cTranslated * tI + 3.0 * dTranslated * tI * tI;
  cUntranslated = cTranslated - 3.0 * dTranslated * tI;
  dUntranslated = dTranslated;
}

SplinePair SplineAbstract::findSplinePairForFunctionX (double x,
                                                       int numIterations) const
{
  SplinePair spCurrent;

  double tLow = m_t[0];
  double tHigh = m_t[m_xy.size() - 1];

  // This method implicitly assumes that the x values are monotonically increasing

  // Extrapolation that is performed if x is out of bounds. As a starting point, we assume that the t
  // values and x values behave the same, which is linearly. This assumption works best when user
  // has set the points so the spline line is linear at the endpoints - which is also preferred since
  // higher order polynomials are typically unstable and can "explode" off into unwanted directions
  double x0 = interpolateCoeff (m_t[0]).x();
  double xNm1 = interpolateCoeff (m_t[m_xy.size() - 1]).x();
  if (x < x0) {

    // Extrapolate with x < x(0) < x(N-1) which correspond to s, s0 and sNm1
    double x1 = interpolateCoeff (m_t[1]).x();
    double tStart = (x - x0) / (x1 - x0); // This will be less than zero. x=x0 for t=0 and x=x1 for t=1
    tLow = 2.0 * tStart;
    tHigh = 0.0;

  } else if (xNm1 < x) {

    // Extrapolate with x(0) < x(N-1) < x which correspond to s0, sNm1 and s
    double xNm2 = interpolateCoeff (m_t[m_xy.size() - 2]).x();
    double tStart = tHigh + (x - xNm1) / (xNm1 - xNm2); // This is greater than one. x=xNm2 for t=0 and x=xNm1 for t=1
    tLow = m_xy.size() - 1;
    tHigh = tHigh + 2.0 * (tStart - tLow);

  }

  // Interpolation using bisection search
  double tCurrent = (tHigh + tLow) / 2.0;
  double tDelta = (tHigh - tLow) / 4.0;
  for (int iteration = 0; iteration < numIterations; iteration++) {
    spCurrent = interpolateCoeff (tCurrent);
    if (spCurrent.x() > x) {
      tCurrent -= tDelta;
    } else {
      tCurrent += tDelta;
    }
    tDelta /= 2.0;
  }

  return spCurrent;
}

void SplineAbstract::initialize(const vector<double> &t,
                                const vector<SplinePair> &xy,
                                SplineTCheck splineTCheck)
{
  ENGAUGE_ASSERT (t.size() == xy.size());
  ENGAUGE_ASSERT (xy.size() > 0); // Need at least one point for this class to not fail with a crash

  if (splineTCheck == SPLINE_ENABLE_T_CHECK) {
    // In normal production this check should be performed
    checkTIncrements (t);
  }
  computeCoefficientsForIntervals (t, xy);
  computeControlPointsForIntervals ();
}

SplinePair SplineAbstract::interpolateCoeff (double t) const
{
  ENGAUGE_ASSERT (m_elements.size() != 0);
  
  vector<SplineCoeff>::const_iterator itr;
  itr = lower_bound(m_elements.begin(), m_elements.end(), t);
  if (itr != m_elements.begin()) {
    itr--;
  }   
            
  return itr->eval(t);
}

SplinePair SplineAbstract::interpolateControlPoints (double t) const
{
  ENGAUGE_ASSERT (m_xy.size() != 0);

  for (int i = 0; i < (signed) m_xy.size() - 1; i++) {

    if (m_t[i] <= t && t <= m_t[i+1]) {

      SplinePair s ((t - m_t[i]) / (m_t[i + 1] - m_t[i]));
      SplinePair onems (SplinePair (1.0) - s);
      SplinePair xy = onems * onems * onems * m_xy [i] +
                      SplinePair (3.0) * onems * onems * s * m_p1 [i] +
                      SplinePair (3.0) * onems * s * s * m_p2 [i] +
                      s * s * s * m_xy[i + 1];
      return xy;
    }
  }

  // Input argument is out of bounds
  ENGAUGE_ASSERT (false);
  return m_t[0];
}

SplinePair SplineAbstract::p1 (unsigned int i) const
{
  ENGAUGE_ASSERT (i < (unsigned int) m_p1.size ());

  return m_p1 [i];
}

SplinePair SplineAbstract::p2 (unsigned int i) const
{
  ENGAUGE_ASSERT (i < (unsigned int) m_p2.size ());

  return m_p2 [i];
}

void SplineAbstract::saveElement (const SplineCoeff &coef)
{
  m_elements.push_back (coef);
}

void SplineAbstract::saveT (const vector<double> &t)
{
  m_t = t;
}

void SplineAbstract::saveXy (const vector<SplinePair> &xy)
{
  m_xy = xy;
}
