#include <math.h>
#include "mmsubs.h"
#include <QImage>
#include <qmath.h>

double angleBetweenVectors (double dx1,
                            double dy1,
                            double dx2,
                            double dy2)
{
  // Vector magnitudes
  double mag1 = sqrt (dx1 * dx1 + dy1 * dy1);
  double mag2 = sqrt (dx2 * dx2 + dy2 * dy2);

  // Dot product = (vec1 dot vec2) / (mag1 * mag2) = cos (angle)
  double cosAngle = (dx1 * dx2 + dy1 * dy2) / mag1 / mag2;
  cosAngle = fmin (cosAngle, 1.0);
  cosAngle = fmax (cosAngle, -1.0);

  return acos (cosAngle);
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

  unsigned int tableIndex = ((bit == 0) ? 0 : 1);
  return image1Bit.color(tableIndex);
}

QRgb pixelRGB8(const QImage &image8Bit, int x, int y)
{
  unsigned int tableIndex = *(image8Bit.scanLine(y) + x);
  return image8Bit.color(tableIndex);
}

QRgb pixelRGB32(const QImage &image32Bit, int x, int y)
{
  unsigned int* p = (unsigned int *) image32Bit.scanLine(y) + x;
  return *p;
}

void projectPointOntoLine(double xCenter,
                          double yCenter,
                          double xStart,
                          double yStart,
                          double xStop,
                          double yStop,
                          double *xProjection,
                          double* yProjection)
{
  if (qAbs (yStart - yStop) < 0.000001) {

    // Special case - line segment is vertical
    *yProjection = yStart;
    double s = (xCenter - xStart) / (xStop - xStart);
    if (s < 0) {
      *xProjection = xStart;
    } else if (s > 1) {
      *xProjection = xStop;
    } else {
      *xProjection = (1.0 - s) * xStart + s * xStop;
    }
  } else {

    // General case - compute slope and intercept of line through (xCenter, yCenter)
    double slope = (xStop - xStart) / (yStart - yStop);
    double yintercept = yCenter - slope * xCenter;

    // Intersect center point line (slope-intercept form) with start-stop line (parametric form x=(1-s)*x1+s*x2, y=(1-s)*y1+s*y2)
    double s = (slope * xStart + yintercept - yStart) /
      (yStop - yStart + slope * (xStart - xStop));

    if (s < 0) {
      *xProjection = xStart;
      *yProjection = yStart;
    } else if (s > 1) {
      *xProjection = xStop;
      *yProjection = yStop;
    } else {
      *xProjection = (1.0 - s) * xStart + s * xStop;
      *yProjection = (1.0 - s) * yStart + s * yStop;
    }
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
      *(image8Bit.scanLine(y) + x) = index;
      return;
    }
  }
}

void setPixelRGB32(QImage &image32Bit, int x, int y, QRgb q)
{
  int* p = (int *)image32Bit.scanLine(y) + x;
  *p = q;
}
