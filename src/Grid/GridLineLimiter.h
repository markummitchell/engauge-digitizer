/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GRID_LINE_LIMITER_H
#define GRID_LINE_LIMITER_H

#include <QPointF>

class Document;
class DocumentModelCoords;
class DocumentModelGridDisplay;
class MainWindowModel;
class Transformation;

/// Default for maximum number of grid lines
extern const int DEFAULT_MAXIMUM_GRID_LINES;

/// Limit the number of grid lines so a bad combination of start/step/stop value will not lead to extremely
/// long delays when the step size is much too small for the start/stop values
class GridLineLimiter
{
public:
  /// Single constructor
  GridLineLimiter ();

  /// Limit step value for x/theta coordinate. This is a noop if the maximum grid line limit in MainWindowModel is not exceeded
  void limitForXTheta (const Document &document,
                       const Transformation &transformation,
                       const DocumentModelCoords &modelCoords,
                       const MainWindowModel &modelMainWindow,
                       const DocumentModelGridDisplay &modelGrid,
                       double &startX,
                       double &stepX,
                       double &stopX) const;

  /// Limit step value for y/range coordinate. This is a noop if the maximum grid line limit in MainWindowModel is not exceeded
  void limitForYRadius (const Document &document,
                        const Transformation &transformation,
                        const DocumentModelCoords &modelCoords,
                        const MainWindowModel &modelMainWindow,
                        const DocumentModelGridDisplay &modelGrid,
                        double &startY,
                        double &stepY,
                        double &stopY) const;

private:

  void documentBounds (const Document &document,
                       const Transformation &transformation,
                       QPointF &boundingRectMin,
                       QPointF &boundingRectMax) const;

};

#endif // GRID_LINE_LIMITER_H
