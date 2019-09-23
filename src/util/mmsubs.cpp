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
                               double &angleRadians,
                               double &aAligned,
                               double &bAligned)
{
  // Given input describing a parallelogram centered (for simplicity) on the origin,
  // with two adjacent corners at (xTL,yTL) and (xTR,yTR) and two other implicit corners
  // given by symmetry at (-xTL,-yTL) and (-xTR,-yTR), this computes the inscribed ellipse
  // and returns it as an angle rotation of an axis-aligned ellipse with (x/a)^2+(y/b)^2=1,
  // also centered on the origin.
  //
  // Translations to/from the origin must be handled externally since they would
  // dramatically increase the complexity of the code in this function, and they are
  // so easily handled before/after calling this method.
  //
  // Math:
  // The four points each go in a different quadrant. The parallelogram in general
  // can have skew in both horizontal (for top and bottom) and vertical (for left and
  // right) directions
  //   TL | TR
  //   -------
  //   BL | BR
  //
  // Make sure the two supplied corners are not diagonal opposites. The third inequalities
  // ensure both values are not zero

  aAligned = 0.0;
  bAligned = 0.0;
  angleRadians = 0.0;

  bool xChanged = (xTL <= 0 && 0 <= xTR && xTL < xTR) ||
                  (xTL >= 0 && 0 >= xTR && xTL > xTR);
  bool yChanged = (yTL <= 0 && 0 <= yTR && yTL < yTR) ||
                  (yTL >= 0 && 0 >= yTR && yTL > yTR);
  if (xChanged != yChanged) {
    // No input issues since the two points are in adjacent quadrants

    const double REALLY_BIG_RATIO = 100000; // Used to prevent divide by zero errors

    // First we compute the transform that makes all four sides either horizontal or vertical
    //   (p)   (a00 a01) (x)
    //   (q) = (a10 a11) (y)
    // We assume that the transform will result in the top two points (xTL,yTL) and (xTR,yTR) have the
    // same average y value, and the right two points (-xTL,-yTL) and (xTR,yTR) have the same average x.
    // Those average values will be the axes of the new axis aligned ellipse
    aAligned = qAbs ((xTR - xTL) / 2.0);
    bAligned = qAbs ((yTR + yTL) / 2.0);
    // Done if either aAligned or bAligned is much bigger than the other since no rotation is needed.
    // This branch also prevents divide by zero errors later
    if (aAligned < REALLY_BIG_RATIO * bAligned &&
        bAligned < REALLY_BIG_RATIO * aAligned) {
      // The transform would produce an axis-aligned rectangle centered on the origin, from the original points
      //   aligned = a * original
      //
      //   (aAligned)   (a00 a01) (xTL)
      //   (bAligned) = (a10 a11) (yTL)
      //
      //   (aAligned)   (a00 a01) (xTR)
      //   (bAligned) = (a10 a11) (yTR)
      // consolidating
      //   (aAligned aAligned)   (a00 a01) (xTL xTR)
      //   (bAligned bAligned) = (a10 a11) (yTL yTR)
      QTransform left (aAligned,
                       aAligned,
                       bAligned,
                       bAligned,
                       0.0,
                       0.0);
      QTransform right (xTL,
                        xTR,
                        yTL,
                        yTR,
                        0.0,
                        0.0);
      bool invertible;
      QTransform a2x2 = left * right.inverted (&invertible);
      if (invertible) {
        double a00 = a2x2.m11();
        double a01 = a2x2.m12();
        double a10 = a2x2.m21();
        double a11 = a2x2.m22();
        // In the axis aligned frame we have (xA/aAligned)^2 + (yA/bAligned)^2 = 1
        // (a00^2 xo^2 + a01^2 yo^2 + 2 * a00 * a01 * xo * yo) / aAligned^2 +
        // (a10^2 xo^2 + a11^2 yo^2 + 2 * a10 * a11 * xo * yo) / bAligned^2 = 1
        // We need a rotation that removes the xo*yo terms to get a rotated ellipse
        //  (xo)   (cosTheta -sinTheta) (xr)
        //  (yo) = (sinTheta cosTheta ) (yr)
        //
        // xo^2 (a00^2 / aAligned^2 + a10^2 / bAligned^2) +
        // yo^2 (a01^2 / aAligned^2 + a11^2 / bAligned^2) +
        // xo yo (2 a00 a01 / aAligned^2 + 2 a10 a11 / bAligned^2) = 1
        //
        // We define some constants, and then substitute in for xo and yo
        // P0 = a00^2 / aAligned^2 + a10^2 / bAligned^2
        // P1 = a01^2 / aAligned^2 + a11^2 / bAligned^2
        // P2 = 2 a00 a01 / aAligned^2 + 2 a10 a11 / bAligned^2
        double P0 = a00 * a00 / aAligned / aAligned + a10 * a10 / bAligned / bAligned;
        double P1 = a01 * a01 / aAligned / aAligned + a11 * a11 / bAligned / bAligned;
        double P2 = 2 * a00 * a01 / aAligned / aAligned + 2 * a10 * a11 / bAligned / bAligned;
        //
        // (cT^2 xr^2 + sT^2 ry^2 - 2 cT sT xr xy) P0 +
        // (sT^2 xr^2 + cT^2 ry^2 + 2 cT sT xr xy) P1 +
        // (cT sT (xr^2 - yr^2) + xr yr (cT^2 - sT^2)) P2 = 1
        //
        // Grouping like terms
        // xR^2 (P0 cT^2 + P1 sT^2 + P2 cT sT) +
        // yR^2 (P0 sT^2 + P1 cT^2 - P2 cT sT) +
        // xr yr (-2 P0 cT sT + 2 P1 cT sT + P2 (cT^2 - sT^2)) = 1
        //
        // To get an axis aligned ellipse we need to cancel the xr*yr term so
        // 0 = 2 cT sT (P1 - P0) + P2 (cT^2 - sT^2)
        // cT sT = -P2 (cT^2 - sT^2) / (2 P1 - 2 P0)
        // Define P3 = -P2 / (2 P1 - 2 P0)
        // so cT sT = P3 (cT^2 - sT^2)
        // Although it looks like we need to solve a transcendental equation for theta,
        // we can use sin(2T) = 2 sT cT
        //            cos(2T) = cT^2 - sT^2
        // so sin(2T)/2 = P3 cos(2T)
        //    tan(2T) = 2 P3
        if (qAbs (P2) < REALLY_BIG_RATIO * qAbs (P1 - P0)) {
          double P3 = -P2 / 2 / (P1 - P0);
          angleRadians = qAtan (2.0 * P3) / 2.0;
        }
        else {
          angleRadians = PI / 2.0;
        }
      }
    }
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
