/******************************************************************************************************
 * (C) 2019 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GUIDELINE_OFFSET_H
#define GUIDELINE_OFFSET_H

#include <QPointF>

class QGraphicsView;
class Transformation;

/// Calculate offset from edge for new Guidelines
class GuidelineOffset
{
public:
  GuidelineOffset();
  
  /// Compute offset from bottom side and returns point in graph coordinates
  QPointF bottom (const QGraphicsView &view,
                  const Transformation &transformation) const;
  
  /// Compute offset from left side and returns point in graph coordinates
  QPointF left (const QGraphicsView &view,
                const Transformation &transformation) const;
  
  /// Compute offset from right side and returns point in graph coordinates
  QPointF right (const QGraphicsView &view,
                 const Transformation &transformation) const;
  
  /// Compute offset from top side and returns point in graph coordinates
  QPointF top (const QGraphicsView &view,
               const Transformation &transformation) const;

private:

  QPointF bottomTop (const QGraphicsView &view,
                     const Transformation &transformation,
                     bool add) const;
  QPointF leftRight (const QGraphicsView &view,
                     const Transformation &transformation,
                     bool add) const;    
  
};

#endif // GUIDELINE_OFFSET_H
