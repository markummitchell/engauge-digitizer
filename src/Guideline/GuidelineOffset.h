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
  
  /// Compute XT offset for point in center of scene, and returns point in graph coordinates
  QPointF XT (const QGraphicsView &view,
              const Transformation &transformation) const;
  
  /// Compute UR offset for point in center of scene, and returns point in graph coordinates
  QPointF YR (const QGraphicsView &view,
              const Transformation &transformation) const;
};

#endif // GUIDELINE_OFFSET_H
