/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#include "mmsubs.h"
#include <QImage>
#include <QPointF>
#include <qmath.h>
#include <QTransform>

const double PI = 3.1415926535;

double angleBetweenVectors (const QPointF &v1,
                            const QPointF &v2)
{
  double v1Mag = qSqrt (v1.x() * v1.x() + v1.y() * v1.y());
  double v2Mag = qSqrt (v2.x() * v2.x() + v2.y() * v2.y());

  double angle = 0;
  if ((v1Mag > 0) || (v2Mag > 0)) {

    double cosArg = (v1.x() * v2.x() + v1.y() * v2.y()) / (v1Mag * v2Mag);
    cosArg = qMin (qMax (cosArg, -1.0), 1.0);
    angle = qAcos (cosArg);
  }

  return angle;
}

double angleFromVectorToVector (const QPointF &vFrom,
                                const QPointF &vTo)
{
  double angleFrom = qAtan2 (vFrom.y(), vFrom.x());
  double angleTo   = qAtan2 (vTo.y()  , vTo.x());

  // Rotate both angles to put from vector along x axis. Note that angleFrom-angleFrom is zero,
  // and angleTo-angleFrom is -pi to +pi radians
  double angleSeparation = angleTo - angleFrom;

  while (angleSeparation < -1.0 * PI) {
    angleSeparation += 2.0 * PI;
  }
  while (angleSeparation > PI) {
    angleSeparation -= 2.0 * PI;
  }

  return angleSeparation;
}

void ellipseFromParallelogram (double xTL,
                               double yTL,
                               double xTR,
                               double yTR,
                               double xBR,
                               double yBR,
                               double &angleRadians,
                               double &aAligned,
                               double &bAligned)
{
  // Given input describing a parallelogram centered (for simplicity) on the origin,
  // with three successive corners at (xTL,yTL) and (xTR,yTR) and two other implicit corners
  // given by symmetry at (-xTL,-yTL) and (-xTR,-yTR), this computes the inscribed ellipse
  // and returns it as an angle rotation of an axis-aligned ellipse with (x/a)^2+(y/b)^2=1,
  // also centered on the origin. Great reference is arxiv:0808.0297v1 by A Horwitz.
  //
  // Translations to/from the origin must be handled externally since they would
  // dramatically increase the complexity of the code in this function, and they are
  // so easily handled before/after calling this method.
  //
  // Ellipse will go through midpoints of the 4 parallelogram sides. Interestingly,
  // the resulting ellipse will NOT in general be aligned with the axes
  
  double xT = (xTL + xTR) / 2.0;
  double yT = (yTL + yTR) / 2.0;
  double xR = (xTR + xBR) / 2.0;
  double yR = (yTR + yBR) / 2.0;
  //
  // Math:
  // Ellipse equation: A x^2 + B y^2 + 2 C x y + D x + E y + F = 0
  //
  // 6 equations and 6 unknowns (A,B,C,D,E,F)
  // 1) Passes through (xT,yT)
  // 2) Passes through (xR,yR)
  // 3) Slope at top midpoint is the constant mT which comes from y = mT x + bT
  // 4) Slope at right midpoint is the constant mR which comes from y = mR x + bR
  // 5+6) Symmetry through the origin means replacing (x,y) by (-x,-y) should leave the
  //    ellipse equation unchanged.
  //    A x^2 + B y^2 + 2 C x y + D x + E y + F = A (-x)^2 + B (-y)^2 + 2 C (-x) (-y) + D (-x) + E (-y) + F
  //                              D x + E y     =                                       D (-x) + E (-y)
  //    which implies both D and E are zero. This one equation counts as two equations (one for x and one for y)

  // Taking differentials of ellipse equation
  //   dx (A x + C y) + dy (B y + C x) = 0
  //   dy/dx = -(A x + C y) / (B y + C x) = m
  // This gives the following set of 4 equations for 4 unknowns
  //   A xT^2 + B yT^2 + 2 C xT yT + F = 0
  //   A xR^2 + B yR^2 + 2 C xR yR + F = 0
  //   A xT + B mT yT + C (mT xT + yT) = 0
  //   A xR + B mR yR + C (mR xR + yR) = 0
  // but we need to move terms without x and y to the right or else A=B=C=F=0 will be the solution.
  // At this point we realize that scaling is arbitrary, so divide out F
  //   A xT^2 + B yT^2 + 2 C xT yT = -1
  //   A xR^2 + B yR^2 + 2 C xR yR = -1
  //   A xT + B mT yT + C (mT xT + yT) = 0
  // Then we apply Kramers Rule to solve for A, B and C

  double m00 = xT * xT;
  double m01 = yT * yT;
  double m02 = 2.0 * xT * yT;
  double m10 = xR * xR;
  double m11 = yR * yR;
  double m12 = 2.0 * xR * yR;
  double m20 = 0;
  double m21 = 0;
  double m22 = 0;
  // We pick either the top or right side, whichever has the smaller slope to prevent divide by zero error
  //     |mT| = |yTR - yTL| / |xTR - xTL|   versus    |mR| = |yTR - yBR| / |xTR - xBR|
  //            |yTR - yTL| * |xTR - xBR|   versus    |yTR - yBR| * |xTR - xTL|
  if (qAbs (yTR - yTL) * qAbs (xTR - xBR) < qAbs (yTR - yBR) * qAbs (xTR - xTL)) {
    // Top slope is less so we use it
    double mT = (yTR - yTL) / (xTR - xTL);
    //double bT = yTL - mT * xTL;
    m20 = xT;
    m21 = mT * yT;
    m22 = mT * xT + yT;
  } else {
    // Right slope is less so we use it
    double mR = (yTR - yBR) / (xTR - xBR);
    //double bR = yTR - mR * xTR;
    m20 = xR;
    m21 = mR * yR;
    m22 = mR * xR + yR;
  }
  
  QTransform denominator (m00, m01, m02,
                          m10, m11, m12,
                          m20, m21, m22);
  QTransform numeratorA (-1.0, m01, m02,
                         -1.0, m11, m12,
                         0.0 , m21, m22);
  QTransform numeratorB (m00, -1.0, m02,
                         m10, -1.0, m12,
                         m20, 0.0 , m22);                         
  QTransform numeratorC (m00, m01, -1.0,
                         m10, m11, -1.0,
                         m20, m21, 0.0 );
  double A = numeratorA.determinant () / denominator.determinant ();
  double B = numeratorB.determinant () / denominator.determinant ();
  double C = numeratorC.determinant () / denominator.determinant ();
  double F = 1.0;

  // Semimajor and semiminor axes are from equations 1.1 and 1.2 in the arXiv reference, with
  // D and E terms set to zero
  double numerator = 4.0 * F * C * C - 4.0 * A * B * F;
  double denominatorMinus = 2.0 * (A * B - C * C) * (A + B + qSqrt ((B - A) * (B - A) + 4 * C * C));
  double denominatorPlus  = 2.0 * (A * B - C * C) * (A + B - qSqrt ((B - A) * (B - A) + 4 * C * C));
  aAligned = qSqrt (numerator / denominatorMinus);
  bAligned = qSqrt (numerator / denominatorPlus);
  // Angle is from equation 1.3 in the arXiv reference
  if (qAbs (2.0 * C) > 10000.0 * qAbs (A - B)) {
    angleRadians = 90.0;
  } else {
    angleRadians = 0.5 * qAtan (2 * C / (A - B));
  }
}

QRgb pixelRGB(const QImage &image, int x, int y)
{
  switch (image.depth())
  {
    case 1:
      return pixelRGB1(image, x, y);
    case 8:
      return pixelRGB8(image, x, y);
    default:
      return pixelRGB32(image, x, y);
  }
}

QRgb pixelRGB1(const QImage &image1Bit, int x, int y)
{
  unsigned int bit;
  if (image1Bit.format () == QImage::Format_MonoLSB) {
    bit = *(image1Bit.scanLine (y) + (x >> 3)) & (1 << (x & 7));
  } else {
    bit = *(image1Bit.scanLine (y) + (x >> 3)) & (1 << (7 - (x & 7)));
  }

  int tableIndex = ((bit == 0) ? 0 : 1);
  return image1Bit.color(tableIndex);
}

QRgb pixelRGB8(const QImage &image8Bit, int x, int y)
{
  int tableIndex = *(image8Bit.scanLine(y) + x);
  return image8Bit.color(tableIndex);
}

QRgb pixelRGB32(const QImage &image32Bit, int x, int y)
{
  // QImage::scanLine documentation says:
  // 1) Cast return value to QRgb* (which is 32 bit) which hides platform-specific byte orders
  // 2) Scanline data is aligned on 32 bit boundary
  // unsigned int* p = (unsigned int *) image32Bit.scanLine(y) + x;  
  const QRgb *p = reinterpret_cast<const QRgb *> (image32Bit.scanLine(y)) + x;
  return *p;
}

void projectPointOntoLine(double xToProject,
                          double yToProject,
                          double xStart,
                          double yStart,
                          double xStop,
                          double yStop,
                          double *xProjection,
                          double *yProjection,
                          double *projectedDistanceOutsideLine,
                          double *distanceToLine)
{
  double s;
  if (qAbs (yStart - yStop) > qAbs (xStart - xStop)) {

    // More vertical than horizontal. Compute slope and intercept of y=slope*x+yintercept line through (xToProject, yToProject)
    double slope = (xStop - xStart) / (yStart - yStop);
    double yintercept = yToProject - slope * xToProject;

    // Intersect projected point line (slope-intercept form) with start-stop line (parametric form x=(1-s)*x1+s*x2, y=(1-s)*y1+s*y2)
    s = (slope * xStart + yintercept - yStart) /
      (yStop - yStart + slope * (xStart - xStop));

  } else {

    // More horizontal than vertical. Compute slope and intercept of x=slope*y+xintercept line through (xToProject, yToProject)
    double slope = (yStop - yStart) / (xStart - xStop);
    double xintercept = xToProject - slope * yToProject;

    // Intersect projected point line (slope-intercept form) with start-stop line (parametric form x=(1-s)*x1+s*x2, y=(1-s)*y1+s*y2)
    s = (slope * yStart + xintercept - xStart) /
      (xStop - xStart + slope * (yStart - yStop));

  }

  *xProjection = (1.0 - s) * xStart + s * xStop;
  *yProjection = (1.0 - s) * yStart + s * yStop;

  if (s < 0) {

    *projectedDistanceOutsideLine = qSqrt ((*xProjection - xStart) * (*xProjection - xStart) +
                                           (*yProjection - yStart) * (*yProjection - yStart));
    *distanceToLine = qSqrt ((xToProject - xStart) * (xToProject - xStart) +
                             (yToProject - yStart) * (yToProject - yStart));

    // Bring projection point to inside line
    *xProjection = xStart;
    *yProjection = yStart;

  } else if (s > 1) {

    *projectedDistanceOutsideLine = qSqrt ((*xProjection - xStop) * (*xProjection - xStop) +
                                           (*yProjection - yStop) * (*yProjection - yStop));
    *distanceToLine = qSqrt ((xToProject - xStop) * (xToProject - xStop) +
                             (yToProject - yStop) * (yToProject - yStop));

    // Bring projection point to inside line
    *xProjection = xStop;
    *yProjection = yStop;

  } else {

    *distanceToLine = qSqrt ((xToProject - *xProjection) * (xToProject - *xProjection) +
                             (yToProject - *yProjection) * (yToProject - *yProjection));

    // Projected point is aleady inside line
    *projectedDistanceOutsideLine = 0.0;

  }
}

void setPixelRGB(QImage &image, int x, int y, QRgb q)
{
  switch (image.depth())
  {
    case 1:
      setPixelRGB1(image, x, y, q);
      return;
    case 8:
      setPixelRGB8(image, x, y, q);
      return;
    case 32:
      setPixelRGB32(image, x, y, q);
      return;
  }
}

void setPixelRGB1(QImage &image1Bit, int x, int y, QRgb q)
{
  for (int index = 0; index < image1Bit.colorCount(); index++) {
    if (q == image1Bit.color(index))
    {
      if (image1Bit.format () == QImage::Format_MonoLSB)
      {
        *(image1Bit.scanLine (y) + (x >> 3)) &= ~(1 << (x & 7));
        if (index > 0)
          *(image1Bit.scanLine (y) + (x >> 3)) |= index << (x & 7);
      }
      else
      {
        *(image1Bit.scanLine (y) + (x >> 3)) &= ~(1 << (7 - (x & 7)));
        if (index > 0)
          *(image1Bit.scanLine (y) + (x >> 3)) |= index << (7 - (x & 7));
      }
      return;
    }
  }
}

void setPixelRGB8(QImage &image8Bit, int x, int y, QRgb q)
{
  for (int index = 0; index < image8Bit.colorCount(); index++) {
    if (q == image8Bit.color(index))
    {
      *(image8Bit.scanLine(y) + x) = static_cast<uchar> (index);
      return;
    }
  }
}

void setPixelRGB32(QImage &image32Bit, int x, int y, QRgb q)
{
  int* p = (int *)image32Bit.scanLine(y) + x;
  *p = signed (q);
}
