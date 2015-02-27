#ifndef MM_SUBS_H
#define MM_SUBS_H

#include <QRgb>

class QImage;

/// Angle, in radians, between two vectors from the same point
extern double angleBetweenVectors (double dx1,
                                   double dy1,
                                   double dx2,
                                   double dy2);

/// Get pixel method for any bit depth
extern QRgb pixelRGB (const QImage &image, int x, int y);

/// Get pixel method for one bit depth
extern QRgb pixelRGB1 (const QImage &image1Bit, int x, int y);

/// Get pixel method for 8 bit depth
extern QRgb pixelRGB8 (const QImage &image8Bit, int x, int y);

/// Get pixel method for 32 bit depth
extern QRgb pixelRGB32 (const QImage &image32Bit, int x, int y);

/// Find the projection of a point onto a line such that the line through the point and its projection are normal to the original line
extern void projectPointOntoLine(double xCenter,
                                 double yCenter,
                                 double xStart,
                                 double yStart,
                                 double xStop,
                                 double yStop,
                                 double *xProjection,
                                 double *yProjection);

/// Set pixel method for any bit depth
extern void setPixelRGB (QImage &image, int x, int y, QRgb q);

/// Set pixel method for one bit depth
extern void setPixelRGB1 (QImage &image1Bit, int x, int y, QRgb q);

/// Set pixel method for 8 bit depth
extern void setPixelRGB8 (QImage &image8Bit, int x, int y, QRgb q);

/// Set pixel method for 32 bit depth
extern void setPixelRGB32 (QImage &image32Bit, int x, int y, QRgb q);

#endif // MM_SUBS_H
