#include "mmsubs.h"
#include <QImage>

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
