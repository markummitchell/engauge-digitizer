/* "THE BEER-WARE LICENSE" (Revision 42): Devin Lane wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, and you
 * think this stuff is worth it, you can buy me a beer in return. */

#include "EngaugeAssert.h"
#include <iostream>
#include "Logger.h"
#include "SplinePair.h"
#include "SplineSingleValued.h"

using namespace std;

SplineSingleValued::SplineSingleValued(const std::vector<double> &t,
                                       const std::vector<SplinePair> &xy,
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
  saveT (t);
  saveXy (xy);

  if (xy.size() > 1) {

    // There are enough points to compute the coefficients
    int i, j;
    int n = (int) xy.size() - 1;

    vector<double> by(n), dy(n), ay(n), cy(n+1), ly(n+1), uy(n+1), zy(n+1);
    vector<double> hy(n+1);

    // y(x) calculations
    ly[0] = 1.0;
    uy[0] = 0.0;
    zy[0] = 0.0;
    hy[0] = xy[1].x() - xy[0].x();

    for (i = 1; i < n; i++) {
      hy[i] = xy[i+1].x() - xy[i].x();
      ly[i] = 2.0 * (xy[i+1].x() - xy[i-1].x()) - hy[i-1] * uy[i-1];
      uy[i] = hy[i] / ly[i];
      ay[i] = (3.0 / hy[i]) * (xy[i+1].y() - xy[i].y()) - (3.0 / hy[i-1]) * (xy[i].y() - xy[i-1].y());
      zy[i] = (ay[i] - hy[i-1] * zy[i-1]) / ly[i];
    }

    ly[n] = 1.0;
    zy[n] = 0.0;
    cy[n] = 0.0;

    for (j = n - 1; j >= 0; j--) {
      cy[j] = zy[j] - uy[j] * cy[j+1];
      by[j] = (xy[j+1].y() - xy[j].y()) / (hy[j]) - (hy[j] * (cy[j+1] + 2.0 * cy[j])) / 3.0;
      dy[j] = (cy[j+1] - cy[j]) / (3.0 * hy[j]);
    }

    // x(t) calculations. To enable combining of cubic y(x) and Nth order x(t) using cubics only
    // we limit N to first order. The boundary conditions on linear equation give
    //   x = (1 - (t - ti)) * xi + (t - ti) * xi+1
    // which is mapped to
    //   x = a + b * (t - ti) + c * (t - ti)^2 + d * (t - ti)^3
    vector<double> bx(n), cx(n), dx(n);
    for (i = 0; i < n; i++) {
      bx[i] = xy[i+1].x() - xy[i].x();
      cx[i] = 0.0;
      dx[i] = 0.0;
    }

    // Combine y(x) and x(t) calculations to get y(t)
    //   x = xi + bx * (t - ti)
    //   y = yi + by * (x - xi) + cy * (x - xi)^2 + dy * (x - xi)^3
    // This is where the linear constraint on x(t) documented above enables a cubic solution for y(t)
    //   y = yi + by * (xi + bx * (t - ti) - xi)
    //          + cy * (xi + bx * (t - ti) - xi)^2
    //          + dy * (xi + bx * (t - ti) - xi)^3
    //   y = yi + by * bx * (t - ti)
    //          + cy * bx^2 * (t - ti)^2
    //          + dy * bx^3 * (t - ti)^3
    for (i = 0; i < n; i++) {
      double byNew = by[i] * bx[i];
      double cyNew = cy[i] * bx[i] * bx[i];
      double dyNew = dy[i] * bx[i] * bx[i] * bx[i];
      by[i] = byNew;
      cy[i] = cyNew;
      dy[i] = dyNew;
    }

    for (i = 0; i < n; i++) {
      saveElement(SplineCoeff(t[i],
                              xy[i],
                              SplinePair (bx[i],
                                          by[i]),
                              SplinePair (cx[i],
                                          cy[i]),
                              SplinePair (dx[i],
                                          dy[i])));
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
