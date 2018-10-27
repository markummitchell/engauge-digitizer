/******************************************************************************************************
 * (C) 2014 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef CALLBACK_BOUNDING_RECTS_H
#define CALLBACK_BOUNDING_RECTS_H

#include "CallbackSearchReturn.h"
#include "DocumentAxesPointsRequired.h"
#include <QPointF>
#include <QRectF>
#include <QString>
#include "Transformation.h"

class Point;

/// Callback for computing the bounding rectangles of the screen and graph coordinates of the points in the Document.
class CallbackBoundingRects
{
public:
  /// Single constructor
  CallbackBoundingRects(DocumentAxesPointsRequired documentAxesPointsRequired,
                        const Transformation &transformation);

  /// Graph coordinate bounding rectangle's (xmin,ymin) corner. QRectF is not returned since it rounds
  /// off the smaller coordinates to zero when large dynamic ranges appear, and those zeros
  /// break the log scale algorithm
  QPointF boundingRectGraphMin (bool &isEmpty) const;

  /// Graph coordinate bounding rectangle's (xmax,ymax) corner. QRectF is not returned since it rounds
  /// off the smaller coordinates to zero when large dynamic ranges appear, and those zeros
  /// break the log scale algorithm
  QPointF boundingRectGraphMax (bool &isEmpty) const;

  /// Screen coordinate bounding rectangle
  QRectF boundingRectScreen (bool &isEmpty) const;

  /// Callback method.
  CallbackSearchReturn callback (const QString &curveName,
                                 const Point &point);

private:
  CallbackBoundingRects();

  void mergeCoordinateX (const QPointF &pos,
                         QPointF &boundingRectMin,
                         QPointF &boundingRectMax,
                         bool &isEmpty);
  void mergeCoordinateY (const QPointF &pos,
                         QPointF &boundingRectMin,
                         QPointF &boundingRectMax,
                         bool &isEmpty);

  DocumentAxesPointsRequired m_documentAxesPointsRequired;
  bool m_isEmptyGraphX; // Have x graph bounds been initialized
  bool m_isEmptyGraphY; // Have y graph bounds been initialized
  bool m_isEmptyScreenX; // Have x screen bounds been initialized
  bool m_isEmptyScreenY; // Have y screen bounds been initialized
  const Transformation m_transformation;
  QPointF m_boundingRectGraphMin; // Not a QRectF for reasons explained by boundingRectGraphMin
  QPointF m_boundingRectGraphMax; // Not a QRectF for reasons explained by boundingRectGraphMax
  QPointF m_boundingRectScreenMin; // Consistent with m_boundingRectGraphMin
  QPointF m_boundingRectScreenMax; // Consistent with m_boundingRectGraphMax
};

#endif // CALLBACK_BOUNDING_RECTS_H
