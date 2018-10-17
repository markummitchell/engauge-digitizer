/* "THE BEER-WARE LICENSE" (Revision 42): Devin Lane wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return. */

#include "EngaugeAssert.h"
#include <iostream>
#include "Logger.h"
#include "SplineSingleValued.h"

using namespace std;

SplineSingleValued::SplineSingleValued(const vector<double> &t,
                                       const vector<SplinePair> &xy,
                                       SplineTCheck splineTCheck) :
  SplineAbstract ()
{
  initialize(t,
             xy,
             splineTCheck);
}

SplineSingleValued::~SplineSingleValued()
{
}

void SplineSingleValued::computeCoefficientsForIntervals (const vector<double> &t,
                                                          const vector<SplinePair> &xy)
{
  // Populate independent variable vector m_t assuming the functions are x(t) and y(x)
  vector<SplinePair> independentVariables (t.size ());
  for (unsigned int i = 0; i < t.size(); i++) {
    independentVariables[i] = SplinePair (t [i],
                                          xy [i].x ());
  }

  saveT (t);
  saveXy (xy);

  if (xy.size() > 1) {

    // There are enough points to compute the coefficients
    int i, j;
    int n = (int) xy.size() - 1;

    vector<SplinePair> b(n), d(n), a(n), c(n+1), l(n+1), u(n+1), z(n+1);
    vector<SplinePair> h(n+1);

    l[0] = SplinePair (1.0);
    u[0] = SplinePair (0.0);
    z[0] = SplinePair (0.0);
    h[0] = independentVariables[1] - independentVariables[0];

    for (i = 1; i < n; i++) {
      h[i] = independentVariables[i+1] - independentVariables[i];
      l[i] = SplinePair (2.0) * (independentVariables[i+1] - independentVariables[i-1]) - h[i-1] * u[i-1];
      u[i] = h[i] / l[i];
      a[i] = (SplinePair (3.0) / h[i]) * (xy[i+1] - xy[i]) - (SplinePair (3.0) / h[i-1]) * (xy[i] - xy[i-1]);
      z[i] = (a[i] - h[i-1] * z[i-1]) / l[i];
    }

    l[n] = SplinePair (1.0);
    z[n] = SplinePair (0.0);
    c[n] = SplinePair (0.0);

    for (j = n - 1; j >= 0; j--) {
      c[j] = z[j] - u[j] * c[j+1];
      b[j] = (xy[j+1] - xy[j]) / (h[j]) - (h[j] * (c[j+1] + SplinePair (2.0) * c[j])) / SplinePair (3.0);
      d[j] = (c[j+1] - c[j]) / (SplinePair (3.0) * h[j]);
    }

    for (i = 0; i < n; i++) {
      saveElement(SplineCoeff(t[i],
                              xy[i],
                              b[i],
                              c[i],
                              d[i]));
    }
  } else {

    // There is only one point so we have to hack a coefficient entry

    saveElement(SplineCoeff(t[0],
                            xy[0],
                            0.0,
                            0.0,
                            0.0));
  }
}
