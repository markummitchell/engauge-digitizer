/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef MM_SUBS_H
#define MM_SUBS_H

#include <QRgb>

class QImage;
class QPointF;

/// Angle between two vectors. Direction is unimportant, so result is between 0 to pi radians
extern double angleBetweenVectors (const QPointF &v1,
                                   const QPointF &v2);

/// Angle between two vectors. Direction is positive when rotation is about +z vector, so result is betwen -pi to pi radians
extern double angleFromVectorToVector (const QPointF &vFrom,
                                       const QPointF &vTo);

/// Get pixel method for any bit depth
extern QRgb pixelRGB (const QImage &image, int x, int y);

/// Get pixel method for one bit depth
extern QRgb pixelRGB1 (const QImage &image1Bit, int x, int y);

/// Get pixel method for 8 bit depth
extern QRgb pixelRGB8 (const QImage &image8Bit, int x, int y);

/// Get pixel method for 32 bit depth
extern QRgb pixelRGB32 (const QImage &image32Bit, int x, int y);

/// Find the projection of a point onto a line segment such that the line through the point and its projection are normal to
/// the original line, subject to one constraint. The constraint is that if the project point is outside the (xStart,yStart)
/// to (xStop,yStop) line segment then it will be moved to (xStart,yStart) or (xStop,yStop), whichever is closer.
/// \param xToProject X/theta coordinate to project
/// \param yToProject Y/radius coordinate to project
/// \param xStart X/theta at start
/// \param yStart Y/radius at start
/// \param xStop X/theta at end
/// \param yStop Y/radius at end
/// \param xProjection X/theta coordinate of point projected onto line, moved to between start and end points if outside
/// \param yProjection Y/radius coordinate of point projected onto line, moved to between start and end points if outside
/// \param projectedDistanceOutsideLine Specifies how far the projected point was moved because of
///                                     this constraint - zero if it was not moved or greater than zero if it was moved.
/// \param distanceToLine Distance between point and close point on the line segment
extern void projectPointOntoLine(double xToProject,
                                 double yToProject,
                                 double xStart,
                                 double yStart,
                                 double xStop,
                                 double yStop,
                                 double *xProjection,
                                 double *yProjection,
                                 double *projectedDistanceOutsideLine,
                                 double *distanceToLine);

/// Set pixel method for any bit depth
extern void setPixelRGB (QImage &image, int x, int y, QRgb q);

/// Set pixel method for one bit depth
extern void setPixelRGB1 (QImage &image1Bit, int x, int y, QRgb q);

/// Set pixel method for 8 bit depth
extern void setPixelRGB8 (QImage &image8Bit, int x, int y, QRgb q);

/// Set pixel method for 32 bit depth
extern void setPixelRGB32 (QImage &image32Bit, int x, int y, QRgb q);

#endif // MM_SUBS_H
